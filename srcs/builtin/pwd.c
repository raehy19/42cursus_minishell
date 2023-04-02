/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:41 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/01 23:05:16 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	ft_pwd(t_node *node)
{
	char	*buf;
	t_env	*pwd;

	(void)node;
	buf = getcwd(0, 4096);
	if (!buf)
	{
		pwd = find_env("PWD");
		if (pwd)
			buf = ft_strdup(pwd->value);
	}
	if (!buf)
	{
		g_global.err_num = FAIL_MALLOC;
		handle_error();
		return ;
	}
	printf("%s\n", buf);
	free(buf);
	g_global.exit_status = 0;
}
