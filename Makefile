NAME = fractol

NAME_BONUS = fractol_bonus

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

SRCS = errors.c utils.c render.c fractol.c

SRCS_BONUS = errors_bonus.c utils_bonus.c render_bonus.c fractol_bonus.c

FUNCS = $(addprefix $(SRC_DIR), $(SRCS))

FUNCS_BONUS = $(addprefix $(SRC_DIR), $(SRCS_BONUS))

RM = rm -f

FLAGS_MLX = -Lmlx -lmlx -framework OpenGL -framework AppKit

all:		$(NAME)

$(NAME):	${FUNCS} $(LIBFT) $(MLX)
			@$(CC) $(FLAGS) $(FLAGS_MLX) $(FUNCS) $(LIBFT) -o $(NAME)
			@echo "\033[32m 💯 | Fract'ol created."

bonus: ${NAME_BONUS}

${NAME_BONUS}:	${FUNCS_BONUS} ${LIBFT} ${MLX}
				@${CC} ${FLAGS} ${FLAGS_MLX} ${FUNCS_BONUS} ${LIBFT} -o ${NAME_BONUS}
				@echo "\033[32m ✨ | Bonus created."

$(LIBFT):
			@$(MAKE_LIBFT)

$(MLX):
			@$(MAKE_MLX)
clean: 
			@$(MAKE_IN_DIRECTORY) $(MLX_PATH) clean 

fclean: 	clean
			@$(MAKE_IN_DIRECTORY) $(LIBFT_PATH) fclean 
			@$(RM) $(NAME)
			@$(RM) $(NAME_BONUS)
			@echo "\033[33m 🌪️  | Fract'ol all cleaned."

re:			fclean all

.PHONY:		all clean fclean re bonus
