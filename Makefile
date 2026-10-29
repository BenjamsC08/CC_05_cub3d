CC = cc
FLAGS = -Wall -Wextra -Werror -g3
NAME = cub3D
SRCS = srcs/parser/parse_line.c srcs/parser/parse_map.c srcs/parser/parse_map_utils.c srcs/parser/parse_utils.c srcs/parser/parse_base.c srcs/render/camera.c srcs/render/maps/draw_minimap.c srcs/render/maps/minimap_utils.c srcs/render/maps/draw_map.c srcs/render/raycast/ray_dda.c srcs/render/raycast/ray_dda_utils.c srcs/render/raycast/raycast.c srcs/render/raycast/raycast_utils.c srcs/render/textures/doors_dda.c srcs/render/textures/doors_render.c srcs/render/textures/loading_textures.c srcs/render/textures/textures.c srcs/render/textures/textures_utils.c srcs/render/textures/open_door.c srcs/render/render.c srcs/timer/timer.c srcs/utils/draw/colors.c srcs/utils/draw/pixel_put.c srcs/utils/draw/str_put.c srcs/utils/draw/printing_utils.c srcs/utils/gameplay/collisions.c srcs/utils/gameplay/gameplay.c srcs/utils/gameplay/moves.c srcs/utils/gameplay/time.c srcs/utils/gameplay/rotation.c srcs/utils/gameplay/win_loose.c srcs/utils/shape/ASCII/mapping_alpha1.c srcs/utils/shape/ASCII/mapping_alpha2.c srcs/utils/shape/ASCII/mapping_num.c srcs/utils/shape/ASCII/mapping_special.c srcs/utils/shape/rect.c srcs/utils/shape/text.c srcs/utils/time_utils.c srcs/utils/key_hook.c srcs/utils/history/score_history.c srcs/utils/history/score_history_utils.c srcs/init.c srcs/main.c srcs/destroy.c
OBJ = $(SRCS:.c=.o)
LIB_PATH = -Lmlx_linux -Llibft -L/usr/lib
LIB_NAME = -lmlx_Linux -lft -lXext -lX11 -lm -lz
INCLUDE_PATH = -I/usr/include -Imlx_linux -Ilibft/includes -Iincludes

VALID = \033[1;32m
NOTVALID = \033[1;31m
LOADING = \033[1;33m
INFOS = \033[1;36m
RESET = \033[0m

MLX_LINK = https://cdn.intra.42.fr/document/document/34997/minilibx-linux.tgz
LIBFT_LINK = https://github.com/BenjamsC08/Libft.git

all: MLX libft/libft.a $(NAME)

DL_MLX:
	@if [ ! -d "mlx_linux" ]; then \
        printf "$(VALID)⇩ Downloading and extracting minilibx...\n$(LOADING)"; \
        wget $(MLX_LINK)  >> /dev/null; \
        tar -xf minilibx-linux.tgz; \
        mv minilibx-linux mlx_linux; \
		printf "$(RESET)";\
    else \
        echo "✅ $(VALID)mlx-linux already downloaded.$(RESET)"; \
    fi

MLX: DL_MLX
	@printf "$(VALID)⇩ Make MLX\n$(RESET)";
	@$(MAKE) -C mlx_linux > /dev/null 2>&1

DL_LIBFT:
	@if [ ! -d "libft" -o ! -f "libft/Makefile" ]; then \
		printf "$(VALID)⇩ Downloading libft from ($(LIBFT_LINK))\n$(LOADING)"; \
		git clone $(LIBFT_LINK) libft >> /dev/null; \
		printf "$(RESET)"; \
	else \
		echo "✅ $(VALID)libft already downloaded.$(RESET)"; \
	fi

libft/libft.a: DL_LIBFT
	@printf "$(VALID)⇩ Make Libft\n$(RESET)";
	@$(MAKE) -C libft > /dev/null 2>&1

%.o: %.c
	@$(CC) $(FLAGS) $(INCLUDE_PATH) -MMD -O3 -c $< -o $@
$(NAME): $(OBJ)
	@echo "$(INFOS)Flags:$(FLAGS)\ninclude:$(INCLUDE_PATH)\nObj:$(OBJ)\nlib:$(LIB_NAME)$(RESET)\n";
	$(CC) $(FLAGS) $(OBJ) $(LIB_PATH) $(LIB_NAME) $(INCLUDE_PATH) -o $(NAME)

clean_mlx:
	@printf "$(NOTVALID)Cleanning MLX \n$(RESET)";
	@rm -rf minilibx-linux.tgz

clean: clean_mlx
	@printf "$(NOTVALID)Cleanning LIBFT \n$(RESET)";
	@if [ -f "libft/Makefile" ]; then \
		$(MAKE) -C libft clean > /dev/null 2>&1;\
	fi
	@printf "$(NOTVALID)Remove *.o and *.d \n$(RESET)";
	@rm -rf $(OBJ) $(OBJ:.o=.d)

fclean: clean
	@printf "$(NOTVALID)Remove CUB3D && libft.a\n$(RESET)";
	@rm -rf $(NAME) libft/libft.a

aclean: fclean
	@printf "$(NOTVALID)Remove mlx_linux repertory\n$(RESET)";
	@rm -rf mlx_linux libft

re : fclean all

rr: aclean all

listC:
	@LIST=$$(find -wholename "./srcs/*.c" | cut -c 3- | tr '\n' ' '); \
	printf "🗅 $(INFOS)copy all C sources files into clipboard :\n$(RESET)$$LIST\n"; \
	echo -n $$LIST | xclip -selection clipboard

listNb:
	@echo "Number of .c files :" 
	@find -wholename "./srcs/*.c" | wc -l

norm:
	@norminette ./srcs ./includes ./libft

-include $(OBJ:.o=.d)
