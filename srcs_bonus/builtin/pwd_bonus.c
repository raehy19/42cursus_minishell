/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:41 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/02 13:50:58 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

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
