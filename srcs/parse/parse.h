/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:52:25 by rjeong            #+#    #+#             */
/*   Updated: 2023/02/24 20:52:26 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "../../minishell.h"

typedef enum e_token_type
{
	T_LEFT_PARENTHESIS,
	T_RIGHT_PARENTHESIS,
	T_AND,
	T_OR,
	T_PIPE,
	T_REDIRECTING_INPUT,
	T_HERE_DOCUMENT,
	T_REDIRECTING_OUTPUT,
	T_APPENDING_REDIRECTED_OUTPUT,
	T_STRING,
}	t_token_type;

typedef struct s_token_node	t_token_node;

typedef struct s_token_node
{
	t_token_type	type;
	char			*string;
	t_token_node	*next;
}	t_token_node;

t_token_node	*new_token(t_token_type type, char *str);

#endif