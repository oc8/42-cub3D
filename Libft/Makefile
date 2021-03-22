# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 17:35:36 by odroz-ba          #+#    #+#              #
#    Updated: 2021/03/22 18:40:35 by odroz-ba         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

ERASE	= \033[2K\r
GREY	= \033[30m
RED		= \033[31m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m
PINK	= \033[35m
CYAN	= \033[36m
WHITE	= \033[37m
END		= \033[0m
BOLD	= \033[1m
UNDER	= \033[4m
SUR		= \033[7m

OBJS	= ft_isalnum.o \
ft_isprint.o \
ft_memchr.o \
ft_memset.o \
ft_putstr_fd.o \
ft_strjoin.o \
ft_strmapi.o \
ft_strtrim.o \
ft_atoi.o \
ft_isalpha.o \
ft_itoa.o \
ft_memcmp.o \
ft_putchar_fd.o \
ft_split.o \
ft_strlcat.o \
ft_strncmp.o \
ft_substr.o \
ft_bzero.o \
ft_isascii.o \
ft_memcpy.o \
ft_putendl_fd.o \
ft_strchr.o \
ft_strlcpy.o \
ft_strnstr.o \
ft_tolower.o \
ft_calloc.o \
ft_isdigit.o \
ft_memccpy.o \
ft_memmove.o \
ft_putnbr_fd.o \
ft_strdup.o \
ft_strlen.o \
ft_strrchr.o \
ft_toupper.o \
ft_lstadd_back.o \
ft_lstadd_front.o \
ft_lstclear.o \
ft_lstdelone.o \
ft_lstiter.o \
ft_lstlast.o \
ft_lstmap.o \
ft_lstnew.o \
ft_lstsize.o \
get_next_line.o \
ft_cmp_float.o
INCLUDES	= libft.h
NAME		= libft.a
CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -Ofast -I .
AR			= ar
ARFLAGS		= rcs

$(NAME):	$(OBJS)
			$(AR) $(ARFLAGS) $(NAME) $?
			printf "$(ERASE)$(GREEN)⤖ $(CYAN)$(NAME) : $(GREEN)ok$(END)\n"

%.o:		%.c $(INCLUDES)
			$(CC) $(CFLAGS) -c $< -o $@
			printf "$(ERASE)$(CYAN)⤖ $(NAME) : $(RED)[$<]"

all:		$(NAME)

clean:		
			$(RM) $(OBJS) $(BONUS)

fclean:		clean
			$(RM) $(NAME)
			printf "$(ERASE)$(GREEN)⤖ $(CYAN)$(NAME) : $(GREEN)clean$(END)\n"

re:			fclean all

.PHONY:		all clean fclean re
.SILENT:	fclean clean $(OBJS) re $(NAME) all
