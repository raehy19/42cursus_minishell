/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:07:12 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/02 13:51:32 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

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

char	*make_newfile(DIR *dir_info, char *filename, int *cnt)
{
	char			*new_file;
	struct dirent	*dir_entry;

	new_file = 0;
	dir_entry = readdir(dir_info);
	while (g_global.err_num == NaE && *cnt <= 1 && dir_entry)
	{
		if (ft_strncmp(dir_entry->d_name, ".", 1)
			&& is_wildcard_format(dir_entry->d_name, filename))
		{
			free(new_file);
			new_file = 0;
			new_file = ft_strdup(dir_entry->d_name);
			(*cnt)++;
		}
		dir_entry = readdir(dir_info);
		if (*cnt >= 1 && !new_file)
			g_global.err_num = FAIL_MALLOC;
	}
	return (new_file);
}

void	handle_wildcard_error(t_node *node, char *new_file, int cnt)
{
	char	*error_message;

	if (cnt == 1)
	{
		free(node->redirect_filename);
		node->redirect_filename = new_file;
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
	free(new_file);
	print_redirect_error(node->redirect_filename, error_message);
}
