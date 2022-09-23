NAME = fractol

FLAGS = -Wall -Wextra -Werror

CC = cc

MAKE_IN_DIRECTORY = make -C

LIBFT_PATH = ./libft

MLX_PATH = ./mlx

MAKE_LIBFT = $(MAKE_IN_DIRECTORY) $(LIBFT_PATH)

MAKE_MLX = $(MAKE_IN_DIRECTORY) $(MLX_PATH)

LIBFT = ./libft/libft.a

MLX = ./mlx/libmlx.a

SRC_DIR = ./src/

SRCS = fractol.c

FUNCS = $(addprefix $(SRC_DIR), $(SRCS))

RM = rm -f

FLAGS_MLX = -Lmlx -lmlx -framework OpenGL -framework AppKit

all:		$(NAME)

$(NAME):	$(LIBFT) $(MLX)
			@$(CC) $(FLAGS) $(FLAGS_MLX) -g $(FUNCS) $(LIBFT) -o $(NAME)
			@echo "\033[32m 💯 | Fract'ol created."

$(LIBFT):
			@$(MAKE_LIBFT)

$(MLX):
			@$(MAKE_MLX)
clean: 
			@$(MAKE_IN_DIRECTORY) $(MLX_PATH) clean 

fclean: 	clean
			@$(MAKE_IN_DIRECTORY) $(LIBFT_PATH) fclean 
			@$(RM) $(NAME)
			@echo "\033[33m 🌪️  | Fract'ol all cleaned."

re:			fclean all

.PHONY:		all clean fclean re
