/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_on_excute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:52:29 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/24 15:46:37 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

int	is_env_allowed_char(const char c)
{
	if (ft_isalnum(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

void	make_env_linked_str(char *str, int *idx, t_linked_str **lst)
{
	int		i;
	char	*env_name;
	t_env	*env;

	i = 0;
	while(is_env_allowed_char(*(str + *idx + i + 1)))
		++i;
	env_name = ft_strndup((str + *idx + 1), i);
	if (!env_name)
		g_global.err_num = FAIL_MALLOC;
	env = find_env(env_name);
	if (env)
		lst_add_back_linked_str(lst, new_linked_str(T_SINGLE_QUOTE,
			strndup(str + *idx, i)));
	*idx += i + 1;
}

void	check_env(char **str)
{
	int				idx;
	int				i;
	t_linked_str	*temp;

	idx = 0;
	i = 0;
	temp = NULL;
	while (*((*str) + idx + i))
	{
		if (*((*str) + idx + i) == '$')
		{
			if (!((*str) + idx + i + 1)
				|| !is_env_allowed_char(*(((*str) + idx + i +  1))))
			{
				g_global.err_num = SYNTAX_ERR;
				return ;
			}
			if ((*(((*str) + idx + i + 1))) == '?')
			{
				lst_add_back_linked_str(&temp,
						new_linked_str(T_SINGLE_QUOTE,
							ft_itoa(g_global.exit_status)));
				idx += i;
				i = 0;
			}
			else
			{
				lst_add_back_linked_str(&temp,
					new_linked_str(T_SINGLE_QUOTE, strndup((*str + idx), i)));
				make_env_linked_str(*str, &idx, &temp);
			}
		}
		++i;
	}
	lst_add_back_linked_str(&temp,
		new_linked_str(T_SINGLE_QUOTE, strndup((*str + idx), i)));
	free(*str);
	*str = ft_combine_lump(temp);
}

char	*ft_combine_lump(t_linked_str *head)
{
	t_linked_str	*temp;
	char			*res;
	char			*temp_str;

	res = head->str;
	temp = head;
	if (temp->str_type == T_DOUBLE_QUOTE || temp->str_type == T_STRING)
		check_env(&(temp->str));
	while (temp->next)
	{
		if (temp->str_type == T_DOUBLE_QUOTE || temp->str_type == T_STRING)
			check_env(&(temp->str));
		temp_str = ft_strjoin(res, temp->next->str);
		free(res);
		free(temp->next->str);
		res = temp_str;
		temp = temp->next;
	}
	free(temp);
	return (res);
}

int	ft_count_arg(t_linked_arg *head)
{
	int	i;

	if (!head)
		return (0);
	i = 1;
	while (head && head->next)
	{
		head = head->next;
		++i;
	}
	return (i);
}

char	**ft_combine_arg(t_linked_arg *head, int *arg_cnt)
{
	t_linked_arg	*temp;
	char			**res;
	int				i;

	*arg_cnt = ft_count_arg(head);
	if (*arg_cnt == 0)
		return (NULL);
	res = (char **) malloc(sizeof(char *) * (*arg_cnt + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < *arg_cnt)
	{
		*(res + i) = ft_combine_lump(head->arg_str);
		temp = head;
		head = head->next;
		free(temp);
	}
	*(res + i) = NULL;
	return (res);
}
