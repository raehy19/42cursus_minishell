/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:11:32 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/24 18:58:19 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

char	**get_path(void)
{
	t_env	*path_env;
	char	**path;

	path_env = find_env("PATH");
	if (!path_env)
		return (0);
	path = ft_split(path_env->value, ':');
	if (!path)
		g_global.err_num = FAIL_MALLOC;
	return (path);
}

char	*make_command_path(char *path, char *command)
{
	int		size;
	char	*command_path;

	size = ft_strlen(path) + ft_strlen(command) + 1;
	command_path = malloc(sizeof(char) * (size + 1));
	if (!command_path)
	{
		g_global.err_num = FAIL_MALLOC;
		return (0);
	}
	ft_strlcpy(command_path, path, ft_strlen(path) + 1);
	ft_strlcat(command_path, "/", ft_strlen(path) + 2);
	ft_strlcat(command_path, command, size + 1);
	return (command_path);
}

int	is_regular_file(mode_t st_mode)
{
	return ((st_mode & S_IFMT));
}

int	handle_special_case(t_node *node, char **command_path)
{
	struct stat	stat_info;

	if (!ft_strcmp(node->command_arg[0], ""))
	{
		*command_path = 0;
		return (1);
	}
	if (access(node->command_arg[0], F_OK | X_OK) != 0)
		return (0);
	if (stat(node->command_arg[0], &stat_info) == -1)
	{
		g_global.err_num = FAIL_STAT;
		handle_error();
	}
	if (is_regular_file(stat_info.st_mode))
	{
		*command_path = node->command_arg[0];
		return (1);
	}
	return (0);
}

char	*find_command_path(t_node *node)
{
	int		idx;
	int		is_executable;
	char	*command_path;
	char	**path;

	idx = -1;
	is_executable = 0;
	command_path = 0;
	if (handle_special_case(node, &command_path))
		return (command_path);
	path = get_path();
	if (!path)
		return (0);
	while (!is_executable && path[++idx])
	{
		free(command_path);
		command_path = make_command_path(path[idx], node->command_arg[0]);
		is_executable = (access(command_path, X_OK) == 0);
	}
	free_two_dim(path);
	if (is_executable)
		return (command_path);
	free(command_path);
	return (0);
}
