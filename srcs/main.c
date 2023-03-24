/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:57:24 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/24 21:40:38 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_global	g_global;

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		g_global.exit_status = 1;
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

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
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
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
