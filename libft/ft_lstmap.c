/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 12:20:44 by rjeong            #+#    #+#             */
/*   Updated: 2022/07/14 17:45:55 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstmap_mem_free(t_list **head, void (*del)(void *), void *content)
{
	if (content)
		del(content);
	ft_lstclear(head, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*temp_read;
	t_list	*temp_write;
	void	*temp_content;

	if (!lst)
		return (NULL);
	temp_read = lst;
	temp_content = f(temp_read->content);
	temp_write = ft_lstnew(temp_content);
	if (!temp_write || !temp_content)
		return (ft_lstmap_mem_free(&temp_write, del, temp_content));
	head = temp_write;
	while (temp_read->next)
	{
		temp_read = temp_read->next;
		temp_content = f(temp_read->content);
		temp_write->next = ft_lstnew(temp_content);
		if (!(temp_write->next) || !temp_content)
			return (ft_lstmap_mem_free(&head, del, temp_content));
		temp_write = temp_write->next;
	}
	return (head);
}
