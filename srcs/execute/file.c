/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:32:08 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/26 16:44:06 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_directory(mode_t st_mode)
{
	return ((st_mode & S_IFMT) == S_IFDIR);
}

int	is_regular_file(mode_t st_mode)
{
	return ((st_mode & S_IFMT) == S_IFREG);
}
