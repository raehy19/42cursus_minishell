/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:57:24 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/26 20:24:00 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_global	g_global;

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_parsed		parsed;

	(void)argc;
	(void)argv;
	init_global(envp);
	while (1)
	{
		parsed = (t_parsed) {NULL, NULL, NULL};
		g_global.err_num = NaE;
		init_standard_fildes();
		handle_signal();
		unset_comtrol_character();
		input = readline("\033[34mminishell-1.0$ \033[0m");
		if (input == NULL)
		{
			printf("exit\n");
			exit(g_global.exit_status);
		}
		// parsing

		parse(input, &parsed);

		add_history(input);
		free(input);
		input = 0;

		if (!parsed.tree)
			continue;

		// executing
		search_heredoc(parsed.tree);
		search_tree(parsed.tree);

		free_token_list(&parsed.token_list);
		free_token_list(&parsed.compressed_list);
		free_tree(parsed.tree);
		
	//	system("leaks --list minishell");
	}
	return (0);
}
