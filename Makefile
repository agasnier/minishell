NAME = minishell

CC = cc
CFLAGS = -Werror -Wall -Wextra
LFLAGS = -lreadline


MANDA_DIR = src
OBJ_DIR = obj

INC_MANDA_DIR = include

SRCS =	$(MANDA_DIR)/main.c \

OBJS = $(SRCS:$(MANDA_DIR)/%.c=$(OBJ_DIR)/%.o)

HEADERS = $(INC_MANDA_DIR)/minishell.h

all: $(NAME)

$(NAME): $(OBJS) 
	@echo "Compilation minishell..."
	@$(CC) $(OBJS) $(LFLAGS) -o $(NAME)
	@echo "Compilation minishell OK."

$(OBJ_DIR)/%.o: $(MANDA_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_MANDA_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

