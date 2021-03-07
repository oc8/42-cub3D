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

NAME		= cub3D
LOBJS		= main.o \
parsing/parsing.o \
parsing/parsing_map.o \
parsing/parsing_plan.o \
parsing/parsing_plan_x.o \
parsing/parsing_plan_y.o \
display/edit_screen.o \
display/raycasting.o \
display/sprite.o \
display/mlx.o \
display/textures.o \
utils/utils.o \
move/key.o \
move/move.o \
close.o
LSRCS		= ${SRCS:.o=.c}
INCLUDES	= ./inc/cub3D.h
CC			= clang
RM			= rm -rf
FLAGS		= -Wall -Wextra -Werror -Ofast#  -g3 -fsanitize=address
CFLAGS		= -I./inc -I./libft/ -I./minilibx -I./mlx
AR			= ar
ARFLAGS		= rcs
PATH_SRCS	= srcs
PATH_OBJS	= objs
SRCS	= $(addprefix $(PATH_SRCS)/,$(LSRCS))
OBJS	= $(addprefix $(PATH_OBJS)/,$(LOBJS))

$(NAME):	compilation $(OBJS)
			$(CC) $(FLAGS) -L./libft -lft -L./minilibx -lmlx -o $@ $(OBJS)
			printf "$(ERASE)$(GREEN)⤖ $(CYAN)$(NAME) : $(GREEN)ok$(END)\n"

no_flag:	compilation $(OBJS)

compilation	:
			make -C ./minilibx/
			make -C ./Libft/
			cp ./Libft/libft.a ./
			cp ./minilibx/libmlx.dylib ./
			printf "$(ERASE)$(GREEN)⤖ $(CYAN)mlx : $(GREEN)ok$(END)\n"

$(PATH_OBJS)/%.o:		$(PATH_SRCS)/%.c $(INCLUDES)
			@mkdir -p $(PATH_OBJS) $(PATH_OBJS)/parsing $(PATH_OBJS)/display $(PATH_OBJS)/utils $(PATH_OBJS)/move
			@$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@
			@printf "$(ERASE)$(CYAN)⤖ $(NAME) : $(RED)[$<]"

all:		$(NAME)

clean:		
			$(RM) $(PATH_OBJS)
			printf "$(ERASE)$(GREEN)⤖ $(CYAN)$(NAME) : $(GREEN)clean$(END)\n"
			make fclean -C ./Libft/

fclean:		clean
			$(RM) $(NAME)

re:			fclean all
			make -C ./Libft/

.PHONY:		all clean fclean re no_flag
.SILENT:	fclean clean re $(NAME) no_flag compilation all










# SRCS	=	main.o \
# parsing.o \
# parsing_map.o \
# parsing_plan.o \
# parsing_plan_x.o \
# parsing_plan_y.o \
# edit_screen.o \
# raycasting.o \
# sprite.o \
# utils.o

# OBJS = ${SRCS:.c=.o}

# LIBFT = ./libft/libft.a
# LIBMLX = libmlx.dylib

# INC		= inc/cub3D.h
# NAME	= cub3D
# CC		= clang
# RM		= rm -f
# CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -g3 -I./includes -L. -lmlx -L./libft -lft

# $(NAME) :	$(OBJS) $(INC) $(LIBFT) $(LIBMLX)
# 	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# $(OBJS) :	$(INC)

# .c.o:
# 	$(CC) -c $< -o $@

# $(LIBFT) :
# 	@$(MAKE) all -C ./libft 

# $(LIBMLX) : 
# 	@$(MAKE) all -C ./minilibx
# 	mv ./minilibx/libmlx.dylib .

# all :		$(NAME)

# clean :
# 	$(RM) $(OBJS)
# 	@$(MAKE) clean -C ./libft
# 	@$(MAKE) clean -C ./minilibx

# fclean : 	clean
# 	$(RM) $(NAME)
# 	$(RM) $(LIBFT)
# 	$(RM) $(LIBMLX)

# re :		fclean all

# .PHONY :	all clean fclean re $(LIBFT) $(LIBMLX)