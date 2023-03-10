# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 17:19:28 by rjeong            #+#    #+#              #
#    Updated: 2023/03/10 15:23:27 by yeepark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
BONUS := libft.a
CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP
RM := rm -f
AR := ar
ARFLAG := crs

all : $(NAME)

SRCS := \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_isspace.c \
	ft_isnumber.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_strncmp.c \
	ft_strcmp.c \
	ft_stridx.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_strndup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c

OBJS := $(SRCS:.c=.o)

DEPS := $(SRCS:.c=.d)

-include $(DEPS)

$(NAME) : $(OBJS)
	$(AR) $(ARFLAG) $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)
	$(RM) $(DEPS)

fclean : clean
	$(RM) $(NAME)

re : fclean
	make all

.PHONY : all clean fclean re
