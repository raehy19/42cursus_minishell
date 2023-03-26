/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 19:38:48 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/24 15:41:29 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
}

void	free_node(t_node *node)
{
	if (node->type == COMMAND)
		free_command_node(node);
	if (node->type == REDIRECT)
		free_redirect_node(node);
	free(node);
}

void	free_cmd_arg_linked(t_linked_arg *linked_arg_list)
{
	t_linked_arg	*temp;
	t_linked_arg	*next;

	temp = linked_arg_list;
	while (temp)
	{
		next = temp->next;
		free_link_str(temp->arg_str);
		free(temp);
		temp = next;
	}
}

void	free_link_str(t_link_str *link_str_list)
{
	t_link_str	*temp;
	t_link_str	*next;

	temp = link_str_list;
	while (temp)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
}

void	free_token_list(t_token **token_list)
{
	t_token	*temp;

	temp = token_shift(token_list);
	while (temp)
	{
		free(temp->str);
		free_link_str(temp->link_str);
		free(temp);
		temp = token_shift(token_list);
	}
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
