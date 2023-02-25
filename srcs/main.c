/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:57:24 by rjeong            #+#    #+#             */
/*   Updated: 2023/02/25 20:53:19 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_global	g_global;

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	if (init_envp(envp))
		return (clear_env()); 
	while (1)
	{
		input = readline("\033[34mminishell-1.0$ \033[0m");

		// parsing

		// executing
//		search_heredoc(node);
//		search_tree(node);

		printf("input command : %s\n", input); //debug

		free(input);
	}
	return (0);
}
