# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 16:56:23 by rjeong            #+#    #+#              #
#    Updated: 2023/02/25 09:55:43 by yeepark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
BONUS_NAME := minishell_bonus

SRCS_DIR := srcs/
PARSE_SRCS_DIR := $(SRCS_DIR)parse/
# need to change bonus_srcs/
BONUS_SRCS_DIR := srcs/

LIBFT := ./libft/libft.a
LIBFT_DIR := libft

CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP
READLINE_FLAG := -lreadline
RM := rm -f

all : $(NAME)

SRCS := \
	main.c \
	envp.c \
	env_utils.c \
	env_utils2.c \

PARSE_SRCS := \
	tokenize.c \
	tokenize_utils.c \

BONUS_SRCS := \
	main.c \

OBJS := $(addprefix $(SRCS_DIR), $(SRCS:.c=.o)) $(addprefix $(PARSE_SRCS_DIR), $(PARSE_SRCS:.c=.o))

DEPS := $(addprefix $(SRCS_DIR), $(SRCS:.c=.d)) $(addprefix $(PARSE_SRCS_DIR), $(PARSE_SRCS:.c=.d))

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
