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

		printf("input command : %s\n", input); //debug

		// parsing

		// parse debug
		t_token_node *temp = ft_tokenize(input);
		while (temp != NULL)
		{
			printf("token type :  ");
			if (temp->type == 0)
				printf("whitespace\n");
			else if (temp->type == 1)
				printf("left parenthesis : (\n");
			else if (temp->type == 2)
				printf("right parenthesis : )\n");
			else if (temp->type == 3)
				printf("and : &&\n");
			else if (temp->type == 4)
				printf("or : ||\n");
			else if (temp->type == 5)
				printf("pipe : |\n");
			else if (temp->type == 6)
				printf("redirecting input : <\n");
			else if (temp->type == 7)
				printf("here document : <<\n");
			else if (temp->type == 8)
				printf("redirecting output : >\n");
			else if (temp->type == 9)
				printf("appending redirecting output : >>\n");
			else if (temp->type == 10)
				printf("string\n");
			printf("token str  :  %s\n\n", temp->string);
			temp = temp->next;
		}

		// executing
//		search_heredoc(node);
//		search_tree(node);


		free(input);
	}
	return (0);
}
