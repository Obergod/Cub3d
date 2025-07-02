# Noms
NAME = Cub3d
OBJ_DIR = obj

# Repertorys
SRCS_DIR = src/
INCS_DIR = includes/

# Libft
LIBFT_DIR = full_libft
LIBFT = $(LIBFT_DIR)/libftfull.a
LIBFT_URL = https://github.com/Obergod/full_libft.git

# Compilation
CC = gcc
WFLAGS = -Wall -Werror -Wextra
CFLAGS  = $(WFLAGS) -I$(INCS_DIR) -I$(LIBFT_DIR)/include -O3
DEPFLAGS = -MMD -MP

# Affichage
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m
CLEAR = \033[2K\r


# Sources
COMMON_SRC = parsing/parsing.c

COMMON_SRCS = $(addprefix $(SRCS_DIR), $(COMMON_SRC))
OBJ_FILES = $(patsubst $(SRCS_DIR)%.c,$(OBJ_DIR)/%.o,$(COMMON_SRCS))
DEP_FILES = $(OBJ_FILES:.o=.d)

all: $(NAME)

# Inclusion des dépendances
-include $(DEP_FILES)

libft: $(LIBFT)

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

$(NAME): libft $(OBJ_FILES)
	@printf "$(YELLOW)Linking...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME)
	@printf "$(CLEAR)$(GREEN)✓ $(NAME) created!$(RESET)\n"

clean:
	@printf "$(YELLOW)cleaning up obj...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@printf "$(CLEAR)$(GREEN)✓ Objects cleaned!$(RESET)\n"

fclean: clean
	@printf "$(YELLOW) Deleteing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@printf "$(CLEAR)$(GREEN)✓ $(NAME) delete!$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
