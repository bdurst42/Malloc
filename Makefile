ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc

CFLAGS = -Wall -Wextra -Werror -D_REENTRANT

MFLAGS =

INCLUDE_DIR = ./includes

DIR_OBJ = ./obj/

SRC_DIR = ./srcs/

MAIN =

LIEN = libft_malloc.so

FILES = malloc.c \
		free.c \
		realloc.c \
		show_alloc_mem.c \
		show_alloc_mem_ex.c \
		print_fcts.c \
		calloc.c \
		malloc_debug.c \
		reallocf.c \
		thread_fcts.c \
		valloc.c \
		split_fill_block.c

OBJS = $(patsubst %.c, $(DIR_OBJ)%.o, $(FILES)) $(patsubst %.c, $(DIR_OBJ)%.o, $(MAIN))

DEP_OBJ = src_msg \
		  $(OBJS)

RM = /bin/rm -rf

all: $(NAME)

debug: CFLAGS += -g3 -D DEBUG_PRINT
debug: all

$(NAME): mkdirobj $(DEP_OBJ)
		@ $(shell ln -s $(NAME) $(LIEN))
		@ /bin/echo -n "Archiving object in $(NAME):"
		@ $(CC) -shared -o $(NAME) $(OBJS) $(MFLAGS) libft/libft.a
		@ echo " \033[32mAll done!\033[0m"

$(DIR_OBJ)%.o: $(SRC_DIR)%.c
	@ /bin/echo -n "    $(notdir $@)"
	@ $(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE_DIR) -I ./libft/includes
	@ echo " \033[32mOK\033[0m"

mkdirobj:
	@ mkdir -p $(DIR_OBJ)

clean:
	@ /bin/echo -n "Removing object files:"
	@ $(RM) $(DIR_OBJ)
	@ echo " \033[32mdone\033[0m"

fclean: clean
	@ /bin/echo -n "Removing library:"
	@ $(RM) $(NAME)
	@ $(RM) $(LIEN)
	@ echo " \033[32mdone\033[0m"

re: fclean all

src_msg:
	@ echo " src functions:"

.PHONY : all clean fclean re
