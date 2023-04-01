/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:57:24 by rjeong            #+#    #+#             */
/*   Updated: 2023/04/01 19:52:23 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_global	g_global;

void	set_main(t_parsed *parsed)
{
	*parsed = (t_parsed){NULL, NULL, NULL};
	g_global.err_num = NaE;
	init_standard_fildes();
	handle_signal();
	unset_comtrol_character();
}

void	free_all(t_parsed *parsed, char **input)
{
	free_token_list(&parsed->token_list);
	free_token_list(&parsed->compressed_list);
	free_tree(parsed->tree);
	free(*input);
	*input = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_parsed		parsed;

	(void)argc;
	(void)argv;
	init_global(envp);
	while (1)
	{
		set_main(&parsed);
		input = readline("minishell-1.0$ ");
		if (input == NULL)
		{
			printf("exit\n");
			exit(g_global.exit_status);
		}
		parse(input, &parsed);
		if (!parsed.tree)
			continue ;
		add_history(input);
		search_heredoc(parsed.tree);
		search_tree(parsed.tree);
		free_all(&parsed, &input);
//		system("leaks --list minishell");
	}
	return (0);
}
