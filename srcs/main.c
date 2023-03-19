/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:57:24 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/19 15:46:31 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_global	g_global;

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_token_node	*token_node;

	(void)argc;
	(void)argv;
	init_global(envp);
	while (1)
	{
		g_global.err_num = NaE;
		init_standard_fildes();
		input = readline("\033[34mminishell-1.0$ \033[0m");

	//	printf("input command : %s\n", input); //debug

		// parsing

		// parse debug
		token_node = ft_tokenize(input);

		t_token_node *temp = compress_tokens(&token_node);
		t_node *tree = ft_parse(&temp);
		
		// executing
		search_heredoc(tree);
		search_tree(tree);

		add_history(input);
		free(input);
	}
	return (0);
}
