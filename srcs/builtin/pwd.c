/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:41 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/16 21:09:03 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(0, 4096);
	printf("%s\n", buf);
	free(buf);
	g_global.exit_status = 0;
	exit(g_global.exit_status);
}
