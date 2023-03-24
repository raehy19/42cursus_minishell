/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:27:57 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/24 16:07:39 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

int	check_front_back(char *name, char *format, char **formats)
{
	int	idx;
	int	len;
	int	format_len;
	int	is_format;

	idx = 0;
	is_format = 1;
	format_len = ft_strlen(format);
	if (is_wildcard(format[0]) && is_wildcard(format[format_len - 1]))
		return (1);
	len = ft_strlen(formats[0]);
	if (!is_wildcard(format[0]))
		is_format = !ft_strncmp(name, formats[0], len);
	if (!is_format || is_wildcard(format[format_len - 1]))
		return (is_format);
	while (formats[idx])
		idx++;
	idx--;
	len = ft_strlen(formats[idx]);
	is_format = !ft_strncmp(name + (ft_strlen(name) - len), formats[idx], len);
	return (is_format);
}

int	is_wildcard_format(char *name, char *format)
{
	int		idx;
	char	**formats;

	idx = -1;
	if (is_wildcard(format[0]) && !format[1])
		return (1);
	formats = ft_split(format, '*');
	if (!formats)
	{
		g_global.err_num = FAIL_MALLOC;
		handle_error();
	}
	if (!check_front_back(name, format, formats))
		return (free_two_dim(formats));
	while (name && formats[++idx])
		name = ft_strnstr(name, formats[idx], ft_strlen(name));
	free_two_dim(formats);
	return (name != 0);
}

void	handle_directory(t_list **command_lst, char *format)
{
	DIR				*dir_info;
	struct dirent	*dir_entry;

	dir_info = opendir(".");
	if (!dir_info) 
	{
		g_global.err_num = FAIL_OPEN_DIR;
		handle_error();
	}
	dir_entry = readdir(dir_info);
	while (dir_entry)
	{
		if (is_wildcard_format(dir_entry->d_name, format))
			add_new_list(command_lst, dir_entry->d_name);
		dir_entry = readdir(dir_info);
	}
	closedir(dir_info);
}

void	handle_wildcard(t_node *node)
{
	int		idx;
	t_list	*command_lst;

	idx = 0;
	command_lst = 0;
	while (node->command_arg[idx])
	{
		if (ft_strchr(node->command_arg[idx], '*'))
			handle_directory(&command_lst, node->command_arg[idx]);
		else
			add_new_list(&command_lst, node->command_arg[idx]);
		idx++;
	}
	free_two_dim(node->command_arg);
	node->command_arg = make_command_arg(command_lst);
	ft_lstclear(&command_lst, free);
}
