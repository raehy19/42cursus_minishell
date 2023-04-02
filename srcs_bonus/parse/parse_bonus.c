/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:10:53 by rjeong            #+#    #+#             */
/*   Updated: 2023/04/01 20:27:16 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

extern t_global	g_global;

t_node	*make_tree(t_token **token_list)
{
	t_node	*tree;

	if (!(*token_list))
		return (NULL);
	tree = new_node(LOGICAL, ROOT);
	parse_token_list(&tree, token_list);
	if (!tree->left && !tree->right)
	{
		free(tree);
		tree = NULL;
	}
	return (tree);
}

void	parse(char *input, t_parsed *parsed)
{
	t_token	*token_list;
	t_token	*compressed_list;

	token_list = ft_tokenize(input);
	if (g_global.err_num == SYNTAX_ERR)
	{
		g_global.exit_status = 258;
		printf("Syntax error !\n");
		free_token_list(&token_list);
		return ;
	}
	compressed_list = compress_tokens(&token_list);
	if (check_token_list(&compressed_list))
	{
		g_global.exit_status = 258;
		printf("Syntax error !\n");
		free_token_list(&token_list);
		free_token_list(&compressed_list);
		return ;
	}
	parsed->tree = make_tree(&compressed_list);
}
