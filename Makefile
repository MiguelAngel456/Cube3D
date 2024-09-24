LIBFT_PATH = libft
SRC_PATH = src
HEADER_PATH = include

NAME = cub3D

SCRS = $(SRC_PATH)/main.c

OBJS = $(SCRS:.c=.o)

HEADER = $(HEADER_PATH)/cube3D.h

CC = $(shell which cc clang gcc | head -n 1)

CFLAGS = -Wall -Werror -Wextra
LIB_FLAGS = -Llibft -lft -LMLX42/build -lmlx42 -Iinclude -ldl -lglfw -pthread -lm
EXEC-NAME-FLAG = -o

RM = rm -rf

GIT_SUBMODULES = git submodule init && git submodule update

all: make-library $(NAME)

make-library:
	$(GIT_SUBMODULES)
	$(MAKE) -C $(LIBFT_PATH)
	cd MLX42 && cmake -B build && cmake --build build -j4

make-library-debug:
	$(MAKE) -C $(LIBFT_PATH) debug

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) $(EXEC-NAME-FLAG) $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT_PATH)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

debug: CFLAGS += -g
debug: make-library-debug $(NAME)