/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_on_excute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:52:29 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/26 12:44:10 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

char	*ft_combine_lump(t_link_str **head)
{
	t_link_str		*next;
	char			*res;
	char			*temp_str;

	if (!(*head))
		return (NULL);
	res = (*head)->str;
	if (ft_strlen(res) != 0
		&& ((*head)->str_type != T_SINGLE_QUOTE))
		check_env(&res);
	while ((*head)->next)
	{
		if (ft_strlen((*head)->next->str) == 0)
		{
			free((*head)->next->str);
			(*head)->next->str = NULL;
			next = (*head)->next;
			free((*head));
			(*head) = next;
			continue;
		}
		if ((*head)->next->str_type != T_SINGLE_QUOTE)
			check_env(&((*head)->next->str));
		temp_str = ft_strjoin(res, (*head)->next->str);
		free(res);
		free((*head)->next->str);
		(*head)->next->str = NULL;
		res = temp_str;
		next = (*head)->next;
		free((*head));
		(*head) = next;
	}
	free((*head));
	*head = NULL;
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

char	**ft_combine_arg(t_linked_arg **head, int *arg_cnt)
{
	t_linked_arg	*temp;
	char			**res;
	int				i;

	*arg_cnt = ft_count_arg(*head);
	if (*arg_cnt == 0)
		return (NULL);
	res = (char **) malloc(sizeof(char *) * (*arg_cnt + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < *arg_cnt)
	{
		// combine arg lump 로 변경해야함
		*(res + i) = ft_combine_lump(&(*head)->arg_str);
		// ???
		if (res+i)
		{
			// check whitespace split ?
		}
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
	*(res + i) = NULL;
	return (res);
}
