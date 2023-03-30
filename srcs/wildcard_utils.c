/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:07:12 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/30 23:06:54 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

int	is_wildcard(char c)
{
	return (c == '*');
}

void	add_new_list(t_list **command_lst, char *name)
{
	t_list	*new;
	char	*dup_name;

	new = 0;
	dup_name = ft_strdup(name);
	if (dup_name)
		new = ft_lstnew((void *)dup_name);
	if (!dup_name || !new)
	{
		g_global.err_num = FAIL_MALLOC;
		handle_error();
	}
	ft_lstadd_back(command_lst, new);
}

char	**make_command_arg(t_list *command_lst)
{
	int		idx;
	int		is_error;
	char	**command_arg;

	idx = 0;
	is_error = 0;
	command_arg = malloc(sizeof(char *) * (ft_lstsize(command_lst) + 1));
	if (!command_arg)
		return (0);
	while (!is_error && command_lst)
	{
		command_arg[idx] = ft_strdup((char *)command_lst->content);
		is_error = (command_arg[idx++] == NULL);
		command_lst = command_lst->next;
	}
	if (is_error)
		g_global.err_num = FAIL_MALLOC;
	command_arg[idx] = 0;
	if (g_global.err_num != NaE)
	{
		free_two_dim(command_arg);
		handle_error();
	}
	return (command_arg);
}

void	handle_wildcard_error(t_node *node, char *new_filename, int cnt)
{
	char	*error_message;

	if (cnt == 1)
	{
		free(node->redirect_filename);
		node->redirect_filename = new_filename;
		return ;
	}
	if (cnt)
	{
		g_global.err_num = AMBIGUOUS_REDIRECT;
		error_message = "ambiguous redirect\n";
	}
	if (!cnt)
	{
		g_global.err_num = NO_SUCH_FILE;
		error_message = "No such file or directory\n";
	}
	free(new_filename);
	print_redirect_error(node->redirect_filename, error_message);
}
