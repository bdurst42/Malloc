NAME = libft.a 
CC = gcc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra
SRC =	src/ft_print.c \
		src/ft_print_utils.c \
		src/ft_ftoi.c \
		src/ft_atoi.c \
		src/ft_testnu.c \
		src/ft_bzero.c \
		src/ft_isalnum.c \
		src/ft_isalpha.c \
		src/ft_isascii.c \
		src/ft_isdigit.c \
		src/ft_isnu.c \
		src/ft_isprint.c \
		src/ft_iswhite.c \
		src/ft_memccpy.c \
		src/ft_memchr.c \
		src/ft_memcmp.c \
		src/ft_memcpy.c \
		src/ft_memset.c \
		src/ft_putchar.c \
		src/ft_putchar_fd.c \
		src/ft_putendl.c \
		src/ft_putendl_fd.c \
		src/ft_putnbr.c \
		src/ft_putnbr_fd.c \
		src/ft_putstr.c \
		src/ft_putstr_fd.c \
		src/ft_strcat.c \
		src/ft_strchr.c \
		src/ft_strclr.c \
		src/ft_strcmp.c \
		src/ft_strcpy.c \
		src/ft_strequ.c \
		src/ft_striter.c \
		src/ft_striteri.c \
		src/ft_strlcat.c \
		src/ft_strlen.c \
		src/ft_strncat.c \
		src/ft_strncmp.c \
		src/ft_strncpy.c \
		src/ft_strnequ.c \
		src/ft_strnstr.c \
		src/ft_strrchr.c \
		src/ft_strstr.c \
		src/ft_tolower.c \
		src/ft_toupper.c

OBJ = $(SRC:.c=.o)
all: CFLAGS += -O2
all: $(NAME)

debug: CFLAGS += -g3
debug: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ) 
	ranlib $(NAME)

%.o: %.c
	$(CC) -I includes -o $@ -c $< $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all 

.PHONY: re fclean clean all
