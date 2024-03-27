NAME = cub3d

SRCS = $(addprefix srcs/,$(addsuffix .c, $(S)))
S = main parser

COMPRESS = ar rcs
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g3
SFLAGS = -fsanitize=address
CC = cc

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:srcs/%.c=%.o))
SOBJS = $(addprefix $(OBJS_DIR_S)/,$(SRCS:srcs/%.c=%.o))

BONUS_OBJS = $(addprefix $(OBJS_DIR_BONUS)/,$(BONUS:bonus/%.c=%.o))
OBJS_DIR = objs
OBJS_DIR_S = s_objs

# libft
LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

#mlx
MLX_DIR = ./includes/minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a -lXext -lX11 -lm -lz

# Color codes
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m 
ORANGE = \033[0;33m
NC = \033[0m 

all: $(NAME)

$(OBJS_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR_S)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)$(NAME)$(NC) compiling..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@echo "$(GREEN)$(NAME)$(NC) ready!"

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(LIBFT)
	@echo $(BONUS_NAME)ready!

$(LIBFT):
	@echo "$(ORANGE)libft$(NC)compiling..."
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(ORANGE)libft$(NC)ready!"

s: fclean $(SOBJS) $(LIBFT)
	@echo "$(GREEN)$(NAME)$(NC) compiling..."
	@$(CC) $(CFLAGS) $(SFLAGS) -o $(NAME) $(SOBJS) $(LIBFT) $(rd_ln)
	@echo "$(GREEN)$(NAME)$(NC) ready!"

clean:
	@$(RM) -r $(OBJS_DIR)
	@$(RM) -r $(OBJS_DIR_BONUS)
	@$(RM) -r $(OBJS_DIR_S)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(RED)$(NAME)$(NC)OBJS cleaned!"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(RED)$(NAME)$(NC)cleaned!"

v: 
	make re && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions="supression.supp" ./$(NAME)

fcount:
	@echo "you wrote $(RED)$(shell cat $(SRCS) | wc -l)$(NC)lines of code"

send: fclean
	git add . && git commit -m "auto" && git push

run: all
	./$(NAME) 

re: fclean all

.PHONY: all fclean clean re
