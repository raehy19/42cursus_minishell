/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:57:24 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/22 21:53:22 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_global	g_global;

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_token	*token_node;

	(void)argc;
	(void)argv;
	init_global(envp);
	while (1)
	{
		g_global.err_num = NaE;
		init_standard_fildes();
		input = readline("\033[34mminishell-1.0$ \033[0m");
		if (input == NULL)
			exit(g_global.exit_status);
		//	printf("input command : %s\n", input); //debug

		// parsing

		// parse debug
		token_node = ft_tokenize(input);

		t_token *temp = compress_tokens(&token_node);
		t_node *tree = parse(&temp);
		if (!tree)
			continue;
		
		// executing
		search_heredoc(tree);
		search_tree(tree);

		free_tree(tree);
		
		add_history(input);
		free(input);
		input = 0;
	//	system("leaks --list minishell");
	}
	return (0);
}
