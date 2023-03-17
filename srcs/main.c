/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:57:24 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/17 12:53:32 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_global	g_global;

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token_node	*token_node;

	(void)argc;
	(void)argv;
	if (init_envp(envp))
		return (clear_env()); 
	while (1)
	{
		input = readline("\033[34mminishell-1.0$ \033[0m");

		printf("input command : %s\n", input); //debug

		// parsing

		// parse debug
		token_node = ft_tokenize(input);

		t_token_node *temp = compress_tokens(&token_node);
		t_node *tree = ft_parse(&temp);

		(void )tree;
		while (temp != NULL)
		{
			printf("\ntoken type :  ");
			if (temp->type == T_WHITESPACE)
				printf("whitespace\n");
			else if (temp->type == T_LEFT_PARENTHESIS)
				printf("(\n");
			else if (temp->type == T_RIGHT_PARENTHESIS)
				printf(")\n");
			else if (temp->type == T_AND)
				printf("&&\n");
			else if (temp->type == T_OR)
				printf("||\n");
			else if (temp->type == T_PIPE)
				printf("|\n");
			else if (temp->type == T_REDIRECTING_INPUT)
				printf("<\n");
			else if (temp->type == T_HERE_DOCUMENT)
				printf("<<\n");
			else if (temp->type == T_REDIRECTING_OUTPUT)
				printf(">\n");
			else if (temp->type == T_APPENDING_REDIRECTED_OUTPUT)
				printf(">>\n");
			else if (temp->type == T_SINGLE_QUOTE)
				printf("single quote\n");
			else if (temp->type == T_DOUBLE_QUOTE)
				printf("double quote\n");
			else if (temp->type == T_STRING)
				printf("str\n");
			else if (temp->type == T_LUMP_STR)
				printf("compressed str\n");
			if (temp->str)
				printf("token str  :  %s\n", temp->str);
			temp = temp->next;
		}

		// executing
		search_heredoc(tree);
		search_tree(tree);


		free(input);
	}
	return (0);
}
