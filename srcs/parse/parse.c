/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:10:53 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/24 15:46:26 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

t_node	*parse(t_token **token_list)
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
