/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:41 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/17 17:53:37 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	ft_pwd(t_node *node)
{
	char	*buf;

	(void)node;
	buf = getcwd(0, 4096);
	if (!buf)
	{
		g_global.err_num = FAIL_MALLOC;
		handle_error();
	}
	printf("%s\n", buf);
	free(buf);
	g_global.exit_status = 0;
}
