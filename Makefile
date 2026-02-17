NAME = minishell

CC		= cc
CFLAGS	= -Werror -Wall -Wextra

MANDA_DIR		= src
OBJ_DIR			= obj
INC_DIR			= include
LIBFT_DIR		= libft

LIBFT		= $(LIBFT_DIR)/libft.a
INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR)
LFLAGS		= -L$(LIBFT_DIR) -lft -lreadline

FILES =	main.c \
		test.c \
		env/env_init.c \
		env/env_utils.c \
		env/env_path.c \
		parsing/lexer.c \
		parsing/parser.c \
		utils/free.c \
		exec/exec_path.c \

SRCS = $(addprefix $(MANDA_DIR)/, $(FILES))

OBJS = $(SRCS:$(MANDA_DIR)/%.c=$(OBJ_DIR)/%.o)

HEADERS = $(INC_DIR)/minishell.h

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Compilation de la Libft..."
	@make -C $(LIBFT_DIR) > /dev/null
	@echo "Compilation de la Libft OK"

$(NAME): $(OBJS) $(LIBFT)
	@echo "Compilation minishell..."
	@$(CC) $(OBJS) $(LFLAGS) -o $(NAME)
	@echo "Compilation minishell OK."

$(OBJ_DIR)/%.o: $(MANDA_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR) > /dev/null

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR) > /dev/null

re: fclean all

.PHONY: all clean fclean re