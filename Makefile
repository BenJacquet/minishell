# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 11:50:11 by chgilber          #+#    #+#              #
#    Updated: 2020/08/06 15:56:05 by jabenjam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell

SRCS =		get_dir.c end.c cd.c \
			parse_env.c env_conversion.c\
			GNL/get_next_line.c GNL/get_next_line_utils.c \
			main.c
SRCSLIB =	libft/ft_split.c libft/ft_strlen.c libft/ft_strncmp.c

INCLUDES = .

LIBFT = ./libft/libft.a

CC = gcc

CFLAGS = -Wall -Wextra

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
bonus : $(NAME_BONUS)

-include $(DPDCS)

$(NAME) : $(OBJS)
	@echo "$(_END)$(_GREEN) [OK]\t"
	@make -C libft
	@make bonus -C libft
	@echo "$(_END)$(_GREEN)[Done]"
	gcc $(CFLAGS) -L libft -lft -o $@ $(OBJS) $(LMINX)

%.o : %.c
	@echo "$(_END)$(_GREEN) [OK]\t"
	$(CC) $(CFLAGS) -I $(INCLUDES) -o ${<:.c=.o} -c $<

re : 
	@make fclean
	@make all

fclean : clean
	@rm -f $(NAME) 
	@make fclean -C libft

clean :
	@rm -f $(OBJS) 
	@make clean -C libft


.PHONY : all re fclean clean bonus
