/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 19:38:48 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/02 13:51:25 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	free_two_dim(char **array)
{
	int	idx;

	idx = 0;
	if (!array)
		return (0);
	while (array[idx])
	{
		free(array[idx]);
		idx++;
	}
	free(array);
	return (0);
}

void	free_command_node(t_node *node)
{
	free(node->command_path);
	free_two_dim(node->command_arg);
	free_cmd_arg_linked(node->cmd_arg_linked_str);
}

void	free_redirect_node(t_node *node)
{
	free(node->redirect_filename);
	if (node->redirect_type == HERE_DOCUMENT)
		close_fildes(node->in_fd);
	free_link_str(&node->redirect_linked_str);
}

void	free_node(t_node *node)
{
	if (node->type == COMMAND)
		free_command_node(node);
	if (node->type == REDIRECT)
		free_redirect_node(node);
	free(node);
}

void	free_tree(t_node *node)
{
	if (node->pre_redirect)
		free_tree(node->pre_redirect);
	if (node->left)
		free_tree(node->left);
	if (node->right)
		free_tree(node->right);
	free_node(node);
}
