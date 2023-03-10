/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:41 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/11 17:06:50 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(0, 4096);
	if (!buf)
	{
		g_global.err_num = FAIL_MALLOC;
		handle_error();
	}
	printf("%s\n", buf);
	free(buf);
	g_global.exit_status = 0;
	exit_by_global();
}
