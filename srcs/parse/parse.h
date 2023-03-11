/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:52:25 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/11 14:34:54 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../../minishell.h"

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
	T_WHITESPACE,
	T_SINGLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_STRING,
}	t_token_type;

typedef struct s_token_node	t_token_node;

typedef struct s_token_node
{
	t_token_type	type;
	char			*string;
	t_token_node	*next;
}	t_token_node;

t_token_node	*lst_new_token(t_token_type type, char *str);
t_token_node	*lst_last_token(t_token_node *lst);
void			lst_add_back_token(t_token_node **lst, t_token_node *new);
int				is_string_char(char c);

void			tokenize_whitespace(char *str, int *idx, t_token_node **lst);
void			tokenize_parenthesis(char *str, int *idx, t_token_node **lst);
void			tokenize_and_or_pipe(char *str, int *idx, t_token_node **lst);
void			tokenize_arrows(char *str, int *idx, t_token_node **lst);
void			tokenize_single_quote(char *str, int *idx, t_token_node **lst);
void			tokenize_double_quote(char *str, int *idx, t_token_node **lst);
void			tokenize_string(char *str, int *idx, t_token_node **lst);

t_token_node	*ft_tokenize(char *input);

#endif