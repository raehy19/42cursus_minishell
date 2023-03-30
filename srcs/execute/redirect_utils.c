/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:43:24 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/30 22:50:07 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_in(t_redirect_type type)
{
	return (type == REDIRECTING_INPUT || type == HERE_DOCUMENT);
}

int	is_out(t_redirect_type type)
{
	return (type == REDIRECTING_OUTPUT
		|| type == APPENDING_REDIRECTED_OUTPUT);
}
