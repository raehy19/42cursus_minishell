/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:11:32 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/10 14:39:49 by yeepark          ###   ########.fr       */
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
		g_global.errno = FAIL_MALLOC;
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
		g_global.errno = FAIL_MALLOC;
		return (0);
	}
	ft_strlcpy(command_path, path, ft_strlen(path) + 1);
	ft_strlcat(command_path, "/", ft_strlen(path) + 2);
	ft_strlcat(command_path, command, size + 1);
	return (command_path);
}

void	free_two_dim(char **array)
{
	int	idx;

	idx = 0;
	while (array[idx])
	{
		free(array[idx]);
		idx++;
	}
	free(array);
}

char	*find_command_path(t_node *node)
{
	int		idx;
	int		is_accessible;
	char	*command_path;
	char	**path;

	idx = -1;
	is_accessible = 0;
	command_path = 0;
	if (access(node->command_arg[0], X_OK) == 0)
		return (node->command_arg[0]);
	path = get_path();
	if (!path)
		return (0);
	while (!is_accessible && path[++idx])
	{
		free(command_path);
		command_path = make_command_path(path[idx], node->command_arg[0]);
		is_accessible = (access(command_path, X_OK) == 0);
	}
	free_two_dim(path);
	if (is_accessible)
		return (command_path);
	free(command_path);
	return (0);
}
