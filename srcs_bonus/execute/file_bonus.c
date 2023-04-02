/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:32:08 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/02 13:51:09 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

int	is_directory(mode_t st_mode)
{
	return ((st_mode & S_IFMT) == S_IFDIR);
}

int	is_regular_file(mode_t st_mode)
{
	return ((st_mode & S_IFMT) == S_IFREG);
}
