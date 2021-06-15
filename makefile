NAME = ft_ssl

CC = gcc
FLAGS = -Wall -Wextra -Werror -Ofast

INCLUDES = includes

OBJ_PATH = obj

SRCS =	main.c \
		parser.c \
		display.c \
		md5.c \
		algo_md5.c \
		print_md5.c \
		sha256.c \
		parse_md.c \
		base64.c
SRCS_PATH = srcs/ft_ssl
SRCS_OBJ = $(addprefix $(OBJ_PATH)/, $(SRCS:.c=.o))

LIB_PATH = srcs/libft
LIB = $(LIB_PATH)/libft.a

all:
	@make $(LIB)
	@make $(NAME)

$(NAME) :	$(LIB) $(SRCS_OBJ) 
			$(CC) -o $(NAME) $^ $(FLAGS)

$(LIB)	:
			make -j -C $(LIB_PATH)

$(OBJ_PATH)/%.o: $(SRCS_PATH)/%.c $(INCLUDES)/ft_ssl.h
					@mkdir -p $(OBJ_PATH)
					$(CC) -o $@ -c $< -I $(INCLUDES) -I $(LIB_PATH)/includes $(FLAGS)

norme:
	@norminette srcs/**/*.c srcs/**/**/*.c includes | grep Error -B 1 > norm.out
	@echo "--" >> norm.out
	@norminette srcs/**/*.c srcs/**/**/*.c includes | grep Warning -B 1 >> norm.out

clean :
			make -C $(LIB_PATH) clean
			rm -f $(SRCS_OBJ)

fclean :	clean
			rm -f $(NAME)

re : 	
			make fclean 
			make all

.PHONY : all clean fclean re
