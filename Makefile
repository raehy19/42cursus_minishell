# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 16:56:23 by rjeong            #+#    #+#              #
#    Updated: 2023/03/11 15:22:25 by yeepark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
BONUS_NAME := minishell_bonus

SRCS_DIR := srcs/
ENV_SRCS_DIR := $(SRCS_DIR)env/
PARSE_SRCS_DIR := $(SRCS_DIR)parse/
BUILTIN_SRCS_DIR := $(SRCS_DIR)builtin/
EXECUTE_SRCS_DIR := $(SRCS_DIR)execute/
# need to change bonus_srcs/
BONUS_SRCS_DIR := srcs/

LIBFT := ./libft/libft.a
LIBFT_DIR := libft

CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP -g
READLINE_FLAG := -lreadline
RM := rm -f

all : $(NAME)

SRCS := \
	main.c \
	envp.c \
	search.c \
	error.c \
	process.c \

ENV_SRCS := \
	init_env.c \
	make_envp.c \
	rank_env.c \
	env_utils.c \

PARSE_SRCS := \
	tokenize_1.c \
	tokenize_2.c \
	tokenize_utils.c \
	token_compress.c \
	token_compress_utils.c \
	parse.c \
	parse_utils.c \

BUILTIN_SRCS := \
	echo.c \
	cd.c \
	pwd.c \
	export.c \
	unset.c \
	env.c \
	exit.c \

EXECUTE_SRCS := \
	heredoc.c \
	redirect.c \
	redirect_utils.c \
	command.c \
	command_utils.c \
	single_builtin.c \

BONUS_SRCS := \
	main.c \

OBJS := \
	$(addprefix $(SRCS_DIR), $(SRCS:.c=.o)) \
	$(addprefix $(ENV_SRCS_DIR), $(ENV_SRCS:.c=.o)) \
	$(addprefix $(PARSE_SRCS_DIR), $(PARSE_SRCS:.c=.o)) \
	$(addprefix $(BUILTIN_SRCS_DIR), $(BUILTIN_SRCS:.c=.o)) \
	$(addprefix $(EXECUTE_SRCS_DIR), $(EXECUTE_SRCS:.c=.o)) \

DEPS := \
	$(addprefix $(SRCS_DIR), $(SRCS:.c=.d)) \
	$(addprefix $(ENV_SRCS_DIR), $(ENV_SRCS:.c=.d)) \
	$(addprefix $(PARSE_SRCS_DIR), $(PARSE_SRCS:.c=.d)) \
	$(addprefix $(BUILTIN_SRCS_DIR), $(BUILTIN_SRCS:.c=.d)) \
	$(addprefix $(EXECUTE_SRCS_DIR), $(EXECUTE_SRCS:.c=.d)) \

BONUS_OBJS := $(addprefix $(BONUS_SRCS_DIR), $(BONUS_SRCS:.c=.o))

BONUS_DEPS := $(addprefix $(BONUS_SRCS_DIR), $(BONUS_SRCS:.c=.d))

-include $(DEPS) $(PARSE_DEPS) $(BONUS_DEPS)

clean :
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(BONUS_OBJS)
	$(RM) $(BONUS_DEPS)

fclean : clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)

re : fclean
	make all

$(LIBFT) :
	make -C $(LIBFT_DIR) all

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $^ -o $@ $(READLINE_FLAG)

$(BONUS_NAME) : $(BONUS_OBJS)
	$(CC) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : all bonus clean fclean re
