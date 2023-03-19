/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:57:24 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/19 14:49:57 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_global	g_global;

void	init(char **envp, int dup_stdfildes[2])
{
	init_builtin_functions();
	if (init_envp(envp))
		exit(clear_env());
	dup_stdfildes[0] = dup(STDIN_FILENO);
	dup_stdfildes[1] = dup(STDOUT_FILENO);
	if (dup_stdfildes[0] == -1 || dup_stdfildes[0] == -1)
	{
		g_global.err_num = FAIL_DUPLICATE_FILDES;
		handle_error();
	}
}

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_token_node	*token_node;
	int				dup_stdfildes[2];

	(void)argc;
	(void)argv;
	init(envp, dup_stdfildes);
	while (1)
	{
		g_global.err_num = NaE;
		duplicate_fildes(dup_stdfildes[0], STDIN_FILENO);
		duplicate_fildes(dup_stdfildes[1], STDOUT_FILENO);
		
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
