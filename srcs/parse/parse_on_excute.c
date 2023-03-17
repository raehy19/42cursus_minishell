/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_on_excute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:52:29 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/12 04:35:52 by rjeong           ###   ########.fr       */
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

char	*ft_combine_lump(t_linked_str *head)
{
	t_linked_str	*temp;
	char			*res;
	char			*temp_str;

	res = head->str;
	temp = head;
	while (temp->next)
	{
		temp_str = ft_strjoin(res, temp->next->str);
		free(res);
		free(temp->next->str);
		res = temp_str;
		temp = temp->next;
	}
	return (res);
}

int	ft_count_arg(t_linked_arg *head)
{
	int	i;

	i = 0;
	while (head && head->next)
	{
		head = head->next;
		++i;
	}
	return (i);
}

char	**ft_combine_arg(t_linked_arg *head, int *arg_cnt)
{
	char	**res;
	int		i;

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
		head = head->next;
	}
	*(res + i) = NULL;
	return res;
}

//
//void	tokenize_env(char *str, int *idx, t_token_node **lst)
//{
//	int		i;
//	char	*env_name;
//	t_env	*env;
//
//	i = 0;
//	while (is_env_allowed_char(*(str + *idx + i + 1)))
//		++i;
//	env_name = ft_strndup((str + *idx + 1), i);
//	if (!env_name)
//		g_global.err_num = FAIL_MALLOC;
//	env = find_env(env_name);
//	if (env)
//		lst_add_back_token(lst,lst_new_token(T_STRING, ft_strdup(env->value)));
//	free(env_name);
//	*idx += i + 1;
//}
