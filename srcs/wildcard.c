/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:27:57 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/01 17:00:12 by yeepark          ###   ########.fr       */
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

int	handle_directory(t_list **command_lst, char *format)
{
	int				cnt;
	DIR				*dir_info;
	struct dirent	*dir_entry;

	cnt = 0;
	dir_info = opendir(".");
	if (!dir_info)
	{
		g_global.err_num = FAIL_OPEN_DIR;
		handle_error();
	}
	dir_entry = readdir(dir_info);
	while (dir_entry)
	{
		if (ft_strncmp(dir_entry->d_name, ".", 1)
		&& is_wildcard_format(dir_entry->d_name, format))
		{
			add_new_list(command_lst, dir_entry->d_name);
			cnt++;
		}
		dir_entry = readdir(dir_info);
	}
	closedir(dir_info);
	return (cnt);
}

int	handle_command_wildcard(t_node *node)
{
	int		idx;
	int		cnt;
	t_list	*command_lst;

	idx = 0;
	cnt = 1;
	command_lst = 0;
	while (cnt && node->command_arg[idx])
	{
		if (ft_strchr(node->command_arg[idx], '*'))
			cnt = handle_directory(&command_lst, node->command_arg[idx]);
		else
			add_new_list(&command_lst, node->command_arg[idx]);
		idx++;
	}
	if (cnt == 0)
	{
		g_global.exit_status = 1;
		print_command_error(node, idx - 1, "No such file or directory");
	}
	free_two_dim(node->command_arg);
	node->command_arg = make_command_arg(command_lst);
	ft_lstclear(&command_lst, free);
	return (cnt);
}

int	handle_redirect_wildcard(t_node *node)
{
	int				cnt;
	DIR				*dir_info;
	struct dirent	*dir_entry;
	char			*new_filename;

	if (!ft_strchr(node->redirect_filename, '*'))
		return (1);
	cnt = 0;
	dir_info = opendir(".");
	if (!dir_info)
	{
		g_global.err_num = FAIL_OPEN_DIR;
		handle_error();
	}
	dir_entry = readdir(dir_info);
	new_filename = 0;
	while (cnt <= 1 && dir_entry)
	{
		if (ft_strncmp(dir_entry->d_name, ".", 1)
		&& is_wildcard_format(dir_entry->d_name, node->redirect_filename))
		{
			free(new_filename);
			new_filename = ft_strdup(dir_entry->d_name);
			cnt++;
		}
		dir_entry = readdir(dir_info);
	}
	closedir(dir_info);
	handle_wildcard_error(node, new_filename, cnt);
	return (cnt);
}
