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

SRCS		= main.c \
parsing.c \
parsing_map.c \
parsing_plan.c \
parsing_plan_x.c \
parsing_plan_y.c \
edit_screen.c \
raycasting.c \
sprite.c \
utils.c
OBJS		= main.o \
parsing.o \
parsing_map.o \
parsing_plan.o \
parsing_plan_x.o \
parsing_plan_y.o \
edit_screen.o \
raycasting.o \
sprite.o \
utils.o
NAME		= Cub3D
INCLUDES	= inc/cub3D.h
CC			= clang
RM			= rm -f
FLAGS		= -Wall -Wextra -Werror  # -fsanitize=address -g3
CFLAGS		= -I./includes -I./libft/ -I./minilibx -I./mlx
AR			= ar
ARFLAGS		= rcs
PATH_SRCS	= $(addprefix srcs/,$(SRCS))
PATH_OBJS	= $(addprefix srcs/,$(OBJS))

$(NAME):	compilation $(PATH_OBJS)
			$(CC) -L./libft -lft -L./minilibx -lmlx -o $@ $(PATH_OBJS)
			printf "$(ERASE)$(CYAN)> $(NAME) : $(RED)ok$(END)\n"

no_flag:	compilation $(PATH_OBJS)

compilation	:
			make -C ./minilibx/
			make -C ./Libft/
			cp ./Libft/libft.a ./
			cp ./minilibx/libmlx.dylib ./
			printf "$(ERASE)$(CYAN)> mlx : $(RED)ok$(END)\n"

%.o:		%.c $(INCLUDES)
			$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@
			printf "$(ERASE)$(CYAN)> $(NAME) : $(RED)[$<]"

all:		$(NAME)

clean:		
			$(RM) $(PATH_OBJS) $(BONUS)
			printf "$(ERASE)$(CYAN)> $(NAME) : $(RED)clean$(END)\n"
			make fclean -C ./Libft/

fclean:		clean
			$(RM) $(NAME)

re:			fclean all
			make -C ./Libft/

.PHONY:		all clean fclean re no_flag
.SILENT:	fclean clean $(PATH_OBJS) re $(NAME) no_flag compilation all
