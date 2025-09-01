# Noms
NAME = Cub3d
OBJ_DIR = obj

# Repertorys
SRCS_DIR = src/
INCS_DIR = include/

# Libraries
MLX_DIR = minilibx-linux/
MLX = $(MLX_DIR)libmlx_Linux.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

# Libft
LIBFT_DIR = full_libft
LIBFT = $(LIBFT_DIR)/libftfull.a
LIBFT_URL = https://github.com/Obergod/full_libft.git

# Compilation
CC = gcc
WFLAGS = -g3
CFLAGS  = $(WFLAGS) -I$(INCS_DIR) -I$(LIBFT_DIR)/include -I$(MLX_DIR) -g3 -O3
DEPFLAGS = -MMD -MP

# Affichage
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m
CLEAR = \033[2K\r


# Sources
COMMON_SRC = parsing/parsing.c parsing/check_map.c parsing/check_textures.c parsing/inits.c

COMMON_SRCS = $(addprefix $(SRCS_DIR), $(COMMON_SRC))
OBJ_FILES = $(patsubst $(SRCS_DIR)%.c,$(OBJ_DIR)/%.o,$(COMMON_SRCS))
DEP_FILES = $(OBJ_FILES:.o=.d)

all: $(NAME)

# Inclusion des dépendances
-include $(DEP_FILES)

libft: $(LIBFT)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	@printf "$(YELLOW)Initialisation libft$(RESET)"
	@for i in 1 2 3; do printf "."; sleep 0.2; done
	@printf " $(GREEN)OK$(RESET)\n"
	@cd $(LIBFT_DIR) 2>/dev/null || (printf "$(YELLOW)Clonage libft$(RESET)" && for i in 1 2 3; do printf "."; sleep 0.2; done && git clone --quiet $(LIBFT_URL) $(LIBFT_DIR) && printf " $(GREEN)OK$(RESET)\n")
	@printf "$(YELLOW)Compilation libft$(RESET)"
	@for i in 1 2 3; do printf "."; sleep 0.2; done
	@printf " $(GREEN)OK$(RESET)\n"
	@$(MAKE) -s -C $(LIBFT_DIR)

$(OBJ_DIR):
	@printf "$(CYAN)Création dossier obj$(RESET)"
	@mkdir -p $(OBJ_DIR)
	@printf " $(GREEN)OK$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	@printf "$(YELLOW)Compilation $<...$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@
	@printf "$(CLEAR)$(GREEN)✓ Compiled $<$(RESET)\n"

$(NAME): libft $(MLX) $(OBJ_FILES)
	@printf "$(YELLOW)Linking...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@printf "$(CLEAR)$(GREEN)✓ $(NAME) created!$(RESET)\n"

clean:
	@printf "$(YELLOW)cleaning up obj...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@printf "$(CLEAR)$(GREEN)✓ Objects cleaned!$(RESET)\n"

fclean: clean
	@printf "$(YELLOW) Deleteing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@printf "$(CLEAR)$(GREEN)✓ $(NAME) delete!$(RESET)\n"

re: fclean all

MLX_MAC_DIR = minilibx_opengl_20191021/

macos: MLX_DIR = $(MLX_MAC_DIR)
macos: MLX = $(MLX_DIR)libmlx.a
macos: MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
macos: CFLAGS := $(filter-out -I$(MLX_DIR), $(CFLAGS)) -I$(MLX_DIR) -DGL_SILENCE_DEPRECATION
macos: $(MLX_MAC_DIR)libmlx.a $(OBJ_FILES)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(MAKE) -s -C $(LIBFT_DIR)
	@printf "$(YELLOW)Linking for macos...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@printf "$(CLEAR)$(GREEN)✓ $(NAME) created for macOS!$(RESET)\n"


$(MLX_MAC_DIR)libmlx.a:
	@printf "$(YELLOW)Compilation mlx macos$(RESET)"
	@for i in 1 2 3; do printf "."; sleep 0.2; done
	@printf " $(GREEN)OK$(RESET)\n"
	@$(MAKE) -s -C $(MLX_MAC_DIR)

.PHONY: all macos clean fclean re
