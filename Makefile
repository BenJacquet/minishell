# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 11:50:11 by chgilber          #+#    #+#              #
#    Updated: 2020/10/28 19:55:35 by chgilber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =		srcs/cd.c\
			srcs/check.c\
			srcs/cmd_conversion.c\
			srcs/echo.c\
			srcs/end.c\
			srcs/env_conversion_list.c\
			srcs/env_conversion_tab.c\
			srcs/env_display.c\
			srcs/env_export.c\
			srcs/env_unset.c\
			srcs/fork.c\
			srcs/freelance.c\
			srcs/ft_splitmini.c\
			srcs/get_dir.c\
			srcs/get_execs.c\
			srcs/GNL/get_next_line_utils.c\
			srcs/GNL/get_next_line.c\
			srcs/ifjoin.c\
			srcs/io_manager.c\
			srcs/joinjoin.c\
			srcs/joinquote.c\
			srcs/joinquotev2.c\
			srcs/joinquotecount.c\
			srcs/list.c\
			srcs/main.c\
			srcs/maininit.c\
			srcs/noquote.c\
			srcs/parse_cmd.c\
			srcs/pipepars.c\
			srcs/pipes.c\
			srcs/realloc.c\
			srcs/redirectioned.c\
			srcs/redirections_1.c\
			srcs/redirections_2.c\
			srcs/run_exec.c\
			srcs/tab.c\
			srcs/token.c\
			srcs/update.c\
			srcs/utils.c\

SRCSLIB =	srcs/libft/ft_split.c\
			srcs/libft/ft_strlen.c\
			srcs/libft/ft_strncmp.c\
			srcs/libft/ft_abs.c

INCLUDES = .

LIBFT = srcs/libft/libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

# Text format
_DEF = $'\033[0m
_END = $'\033[0m
_GRAS = $'\033[1m
_SOUL = $'\033[4m
_CLIG = $'\033[5m
_SURL = $'\033[7m

# Colors
_BLACK = $'\033[30m
_RED = $'\033[31m
_GREEN = $'\033[32m
_YELLOW = $'\033[33m
_BLUE = $'\033[34m
_PURPLE = $'\033[35m
_CYAN = $'\033[36m
_GREY = $'\033[37m

# Background
_IBLACK = $'\033[40m
_IRED = $'\033[41m
_IGREEN = $'\033[42m
_IYELLOW = $'\033[43m
_IBLUE = $'\033[44m
_IPURPLE = $'\033[45m
_ICYAN = $'\033[46m
_IGREY = $'\033[47m

OBJS = $(SRCS:.c=.o)
OBJS_LIB = $(SRCSLIB:.c=.o)

all : $(NAME)

-include $(DPDCS)

$(NAME) : $(OBJS)
	@echo "$(_END)$(_GREEN) [OK]\t"
	@make bonus -C srcs/libft
	@gcc $(CFLAGS) -o $@ $(OBJS) $(LIBFT)
	@echo "$(_END)$(_GREEN)[Minishell-Done]"

%.o : %.c
	@echo "$(_END)$(_GREEN) [OK]\t"
	@$(CC) $(CFLAGS) -I $(INCLUDES) -o ${<:.c=.o} -c $<

clean :
	@rm -f $(OBJS)
	@make clean -C srcs/libft

fclean : clean
	@rm -f $(NAME)
	@make fclean -C srcs/libft

re : fclean all

.PHONY : all re fclean clean bonus
