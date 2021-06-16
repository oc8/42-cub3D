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
LST_SRCS	= main.c \
parsing/parsing.c \
parsing/criteria.c \
parsing/map_pars.c \
parsing/plan_pars.c \
parsing/plan_x_pars.c \
parsing/plan_y_pars.c \
parsing/is_open.c \
parsing/malloc_map.c \
parsing/utils_pars.c \
display/edit_screen.c \
display/time.c \
display/sprite.c \
display/put_pixels.c \
display/mlx.c \
nearest/nearest.c \
raycasting/sprite_ray.c \
raycasting/utils_ray.c \
raycasting/wall_ray.c \
raycasting/others_ray.c \
texture/wall_texture.c \
texture/sprite_texture.c \
texture/skybox.c \
texture/skybox_2.c \
texture/others_texture.c \
utils/utils.c \
utils/utils_2.c \
utils/save.c \
move/loop.c \
move/key.c \
move/mouse.c \
move/sprite_move.c \
move/utils_move.c \
move/utils_move_2.c \
move/jump.c \
close.c
CC			= clang
RM			= rm -rf
# FLAGS		= -Ofast
FLAGS		= -Wall -Wextra -Werror -Ofast
# FLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address
# FLAGS		= -Wall -Wextra -Werror -g #(lldb)
CFLAGS		= -Iinc -Ilibft/ -Iminilibx -Imlx 
AR			= ar
ARFLAGS		= rcs
SRCS_DIR	= srcs
OBJS_DIR	= objs
OBJS		= $(LST_SRCS:%.c=$(OBJS_DIR)/%.o)
MKDIR		= mkdir -p

$(OBJS_DIR):
			$(MKDIR) $@

$(NAME):	$(OBJS_DIR) compilation $(OBJS)
			$(CC) $(FLAGS) -Iinc -L./libft -lft -L./minilibx -lmlx  $(OBJS) -o $@
			printf "$(ERASE)$(GREEN)⤖ $(CYAN)$(NAME) : $(GREEN)ok$(END)\n"

compilation	:
			make -C ./minilibx/
			make -C ./Libft/
			cp ./minilibx/libmlx.dylib ./
			printf "$(ERASE)$(GREEN)⤖ $(CYAN)mlx : $(GREEN)ok$(END)\n"

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c inc/*.h
			$(MKDIR) $(dir $@)
			@$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@
			@printf "$(ERASE)$(CYAN)⤖ $(NAME) : $(RED)[$<]"

all:		$(NAME)

bonus:		$(NAME)

clean:		
			$(RM) $(OBJS_DIR)
			printf "$(ERASE)$(GREEN)⤖ $(CYAN)$(NAME) : $(GREEN)clean$(END)\n"
			make fclean -C ./Libft/

fclean:		clean
			$(RM) $(NAME)
			$(RM) save.bmp
			$(RM) ./libmlx.dylib
			@make clean -C ./minilibx

re:			clean all
			make -C ./Libft/

.PHONY:		all clean fclean re
.SILENT:	fclean clean re $(NAME) compilation all $(OBJS) $(OBJS_DIR)