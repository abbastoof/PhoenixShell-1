# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 12:54:55 by atoof             #+#    #+#              #
#    Updated: 2023/06/01 13:47:43 by mtoof            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC_DIR = src/
BUILT_IN_DIR = src/built-in/
LEXER_D = src/lexer/
UTILS_D = src/utils/
SRC_UTILS = ft_realloc.c ft_strcmp.c ft_strnjoin.c helper.c
SRC = main.c commands.c  env_init.c signals.c
SRC_BUILT = cd.c echo.c env.c exit.c export.c pwd.c unset.c
SRC_LEX = lexer.c lexer_helper.c var_finder.c dollar_sign.c
SRCS = $(addprefix $(SRC_DIR), $(SRC)) $(addprefix $(BUILT_IN_DIR), $(SRC_BUILT)) \
		$(addprefix $(LEXER_D), $(SRC_LEX)) $(addprefix $(UTILS_D), $(SRC_UTILS))
HEADER_DIR = header/
HEADER = minishell.h
OBJ_DIR = obj/
OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)
LIBFT = ./libft/libft.a
FLAGS = -Wall -Werror -Wextra
EXTRA_FLAGS = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

# ANSI escape sequences for text formatting
BOLD = \033[1m
GREEN = \033[0;32m
YELLOW = \033[0;33m
CYAN = \033[0;36m
NC = \033[0m

vpath %.c $(SRC_DIR) $(BUILT_IN_DIR) $(LEXER_D) $(UTILS_D)
vpath %.h $(HEADER_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	@if [ -f $(NAME) ] && [ "$(OBJS)" -ot "$(NAME)" ]; then \
		echo "$(GREEN)$(BOLD)$(NAME) is already up-to-date!$(NC)"; \
	else \
		echo "$(YELLOW)$(BOLD)Compiling $(NAME)...$(NC)"; \
		make -C ./libft; \
		cc $(FLAGS) $(EXTRA_FLAGS) $(OBJS) -I$(HEADER_DIR) $(LIBFT) -o $@ ; \
		echo "$(GREEN)$(BOLD)$(NAME) successfully compiled!$(NC)"; \
	fi

$(OBJ_DIR)%.o: %.c $(HEADER_DIR)$(HEADER)
	@echo "$(YELLOW)$(BOLD)Compiling $<...$(NC)"
	@mkdir -p $(@D)
	@cc $(FLAGS) -I$(HEADER_DIR) -c -o $@ $<

clean:
	@echo "$(CYAN)$(BOLD)Cleaning object files...$(NC)"
	@make clean -C ./libft
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(CYAN)$(BOLD)Cleaning $(NAME)...$(NC)"
	@make fclean -C ./libft
	@/bin/rm -f $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME) successfully cleaned!$(NC)"

re: fclean all

