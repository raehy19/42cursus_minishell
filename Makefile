# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 16:56:23 by rjeong            #+#    #+#              #
#    Updated: 2023/03/30 22:48:21 by yeepark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
BONUS_NAME := minishell_bonus

SRCS_DIR := srcs/
ENV_SRCS_DIR := $(SRCS_DIR)env/
PARSE_SRCS_DIR := $(SRCS_DIR)parse/
BUILTIN_SRCS_DIR := $(SRCS_DIR)builtin/
EXECUTE_SRCS_DIR := $(SRCS_DIR)execute/

BONUS_SRCS_DIR := srcs_bonus/
BONUS_ENV_SRCS_DIR := $(BONUS_SRCS_DIR)env/
BONUS_PARSE_SRCS_DIR := $(BONUS_SRCS_DIR)parse/
BONUS_BUILTIN_SRCS_DIR := $(BONUS_SRCS_DIR)builtin/
BONUS_EXECUTE_SRCS_DIR := $(BONUS_SRCS_DIR)execute/

LIBFT := ./libft/libft.a
LIBFT_DIR := libft

CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP -g
READLINE_FLAG := -lreadline
LDFLAGS := -L/Users/rjeong/goinfre/.brew/opt/readline/lib
CPPFLAGS := -I/Users/rjeong/goinfre/.brew/opt/readline/include
RM := rm -f



all : $(NAME)

bonus : $(BONUS_NAME)



SRCS := \
	main.c \
	global.c \
	error.c \
	free_1.c \
	free_2.c \
	utils.c \
	search.c \
	process.c \
	wildcard.c \
	wildcard_utils.c \
	signal.c \
	terminal.c \

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
	check_token_list.c \
	parse.c \
	parse_token_1.c \
	parse_token_2.c \
	parse_utils_1.c \
	parse_utils_2.c \
	parse_on_excute.c \
	check_env.c \
	utils.c \

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
	fildes.c \
	pipe.c \
	command.c \
	command_utils.c \
	file.c \
	builtin.c \



BONUS_SRCS := \
	main_bonus.c \
	global_bonus.c \
	error_bonus.c \
	free_1_bonus.c \
	free_2_bonus.c \
	utils_bonus.c \
	search_bonus.c \
	process_bonus.c \
	wildcard_bonus.c \
	wildcard_utils_bonus.c \
	signal_bonus.c \
	terminal_bonus.c \

BONUS_ENV_SRCS := \
	init_env_bonus.c \
	make_envp_bonus.c \
	rank_env_bonus.c \
	env_utils_bonus.c \

BONUS_PARSE_SRCS := \
	tokenize_1_bonus.c \
	tokenize_2_bonus.c \
	tokenize_utils_bonus.c \
	token_compress_bonus.c \
	token_compress_utils_bonus.c \
	check_token_list_bonus.c \
	parse_bonus.c \
	parse_token_1_bonus.c \
	parse_token_2_bonus.c \
	parse_utils_1_bonus.c \
	parse_utils_2_bonus.c \
	parse_on_excute_bonus.c \
	check_env_bonus.c \
	utils_bonus.c \

BONUS_BUILTIN_SRCS := \
	echo_bonus.c \
	cd_bonus.c \
	pwd_bonus.c \
	export_bonus.c \
	unset_bonus.c \
	env_bonus.c \
	exit_bonus.c \

BONUS_EXECUTE_SRCS := \
	heredoc_bonus.c \
	redirect_bonus.c \
	redirect_utils_bonus.c \
	fildes_bonus.c \
	pipe_bonus.c \
	command_bonus.c \
	command_utils_bonus.c \
	file_bonus.c \
	builtin_bonus.c \



OBJS := \
	$(addprefix $(SRCS_DIR), $(SRCS:.c=.o)) \
	$(addprefix $(ENV_SRCS_DIR), $(ENV_SRCS:.c=.o)) \
	$(addprefix $(PARSE_SRCS_DIR), $(PARSE_SRCS:.c=.o)) \
	$(addprefix $(BUILTIN_SRCS_DIR), $(BUILTIN_SRCS:.c=.o)) \
	$(addprefix $(EXECUTE_SRCS_DIR), $(EXECUTE_SRCS:.c=.o)) \

BONUS_OBJS := \
	$(addprefix $(BONUS_SRCS_DIR), $(BONUS_SRCS:.c=.o)) \
	$(addprefix $(BONUS_ENV_SRCS_DIR), $(BONUS_ENV_SRCS:.c=.o)) \
	$(addprefix $(BONUS_PARSE_SRCS_DIR), $(BONUS_PARSE_SRCS:.c=.o)) \
	$(addprefix $(BONUS_BUILTIN_SRCS_DIR), $(BONUS_BUILTIN_SRCS:.c=.o)) \
	$(addprefix $(BONUS_EXECUTE_SRCS_DIR), $(BONUS_EXECUTE_SRCS:.c=.o)) \



DEPS := \
	$(addprefix $(SRCS_DIR), $(SRCS:.c=.d)) \
	$(addprefix $(ENV_SRCS_DIR), $(ENV_SRCS:.c=.d)) \
	$(addprefix $(PARSE_SRCS_DIR), $(PARSE_SRCS:.c=.d)) \
	$(addprefix $(BUILTIN_SRCS_DIR), $(BUILTIN_SRCS:.c=.d)) \
	$(addprefix $(EXECUTE_SRCS_DIR), $(EXECUTE_SRCS:.c=.d)) \

BONUS_DEPS := \
	$(addprefix $(BONUS_SRCS_DIR), $(BONUS_SRCS:.c=.d)) \
	$(addprefix $(BONUS_ENV_SRCS_DIR), $(BONUS_ENV_SRCS:.c=.d)) \
	$(addprefix $(BONUS_PARSE_SRCS_DIR), $(BONUS_PARSE_SRCS:.c=.d)) \
	$(addprefix $(BONUS_BUILTIN_SRCS_DIR), $(BONUS_BUILTIN_SRCS:.c=.d)) \
	$(addprefix $(BONUS_EXECUTE_SRCS_DIR), $(BONUS_EXECUTE_SRCS:.c=.d)) \

-include $(DEPS) $(BONUS_DEPS)



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
	$(CC) $^ -o $@ $(READLINE_FLAG) $(CPPFLAGS) $(LDFLAGS) 

$(BONUS_NAME) : $(LIBFT) $(BONUS_OBJS)
	$(CC) $^ -o $@ $(READLINE_FLAG) $(CPPFLAGS) $(LDFLAGS)
	cp $(BONUS_NAME) $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(CPPFLAGS) 

.PHONY : all bonus clean fclean re
