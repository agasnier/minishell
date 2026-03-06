NAME = libftprintf.a
CC = cc
CFLAGS = -Werror -Wall -Wextra

SRCS = ft_printf.c \
	ft_orchestror.c \
	ft_struct.c \
	ft_format_char.c \
	ft_format_num.c \
	ft_format_hex.c \
	ft_apply_sign.c \
	ft_apply_precision.c \
	ft_apply_hash.c \
	ft_apply_width.c 
	
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft/

LIBFT = $(LIBFT_DIR)libft.a


all: $(NAME)

bonus: all

$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus




