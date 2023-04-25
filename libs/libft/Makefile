NAME = libft.a

LIB_PATH = ./include/
LIB = libft.h
LIBRARIES := $(addprefix $(LIB_PATH), $(LIB))

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_PATH = ./src/
SRC =	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_freethis.c \
		ft_putnbr_base_fd.c \
		ft_atoll.c
SOURCES := $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH = ./obj/
OBJ		= $(SRC:.c=.o)
OBJECTS = $(addprefix $(OBJ_PATH), $(OBJ))

all: $(NAME)

$(NAME): $(SOURCES) $(LIBRARIES)
	@ $(CC) $(CFLAGS) -c $(SOURCES) -I $(LIB_PATH)
	@ ar -rc $(NAME) $(OBJ)
	@ mkdir -p obj
	@ mv $(OBJ) $(OBJ_PATH)
	@ echo "Library created sucessfully!"

clean:
	@ rm -f $(OBJECTS)
	@ rm -rf $(OBJ_PATH)
	@ echo "Object files removed sucessfully!"

fclean: clean
	@ rm -f $(NAME)
	@ echo "Library removed sucessfully!"

re: fclean all

.PHONY: all clean fclean re
