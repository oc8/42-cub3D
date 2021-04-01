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
parsing/criteria.o \
parsing/map_pars.o \
parsing/plan_pars.o \
parsing/plan_x_pars.o \
parsing/plan_y_pars.o \
parsing/is_open.o \
parsing/malloc_map.o \
parsing/utils_pars.o \
display/edit_screen.o \
display/time.o \
display/sprite.o \
display/put_pixels.o \
display/mlx.o \
nearest/nearest.o \
raycasting/sprite_ray.o \
raycasting/utils_ray.o \
raycasting/wall_ray.o \
raycasting/others_ray.o \
texture/wall_texture.o \
texture/sprite_texture.o \
texture/skybox.o \
texture/skybox_2.o \
texture/others_texture.o \
utils/utils.o \
utils/utils_2.o \
utils/save.o \
move/loop.o \
move/key.o \
move/mouse.o \
move/sprite_move.o \
move/utils_move.o \
move/utils_move_2.o \
move/jump.o \
close.o
LSRCS		= ${SRCS:.o=.c}
INCLUDES	= ./inc/cub3d.h
CC			= clang
RM			= rm -rf
FLAGS		= -Wall -Wextra -Werror -Ofast
# FLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address
# FLAGS		= -Wall -Wextra -Werror -g #(lldb)
CFLAGS		= -I./inc -I./libft/ -I./minilibx -I./mlx
AR			= ar
ARFLAGS		= rcs
PATH_SRCS	= srcs
PATH_OBJS	= objs
SRCS		= $(addprefix $(PATH_SRCS)/,$(LSRCS))
OBJS		= $(addprefix $(PATH_OBJS)/,$(LOBJS))

$(NAME):	compilation $(OBJS)
			$(CC) $(FLAGS) -L./libft -lft -L./minilibx -lmlx -o $@ $(OBJS)
			printf "$(ERASE)$(GREEN)⤖ $(CYAN)$(NAME) : $(GREEN)ok$(END)\n"

no_flag:	compilation $(OBJS)

compilation	:
			make -C ./minilibx/
			make -C ./Libft/
			cp ./minilibx/libmlx.dylib ./
			printf "$(ERASE)$(GREEN)⤖ $(CYAN)mlx : $(GREEN)ok$(END)\n"

$(PATH_OBJS)/%.o:		$(PATH_SRCS)/%.c $(INCLUDES) libft/libft.a
			@mkdir -p $(PATH_OBJS) $(PATH_OBJS)/parsing $(PATH_OBJS)/display $(PATH_OBJS)/utils $(PATH_OBJS)/move $(PATH_OBJS)/nearest $(PATH_OBJS)/raycasting $(PATH_OBJS)/texture
			@$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@
			@printf "$(ERASE)$(CYAN)⤖ $(NAME) : $(RED)[$<]"

all:		$(NAME)

bonus:		$(NAME)

clean:		
			$(RM) $(PATH_OBJS)
			printf "$(ERASE)$(GREEN)⤖ $(CYAN)$(NAME) : $(GREEN)clean$(END)\n"
			make fclean -C ./Libft/

fclean:		clean
			$(RM) $(NAME)
			$(RM) save.bmp

re:			fclean all
			make -C ./Libft/

.PHONY:		all clean fclean re no_flag
.SILENT:	fclean clean re $(NAME) no_flag compilation all