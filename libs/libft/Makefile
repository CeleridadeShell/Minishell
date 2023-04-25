NAME = libft.a

LIB = libft.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror

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
		ft_putnbr_fd.c

BONUS =	ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c

ADD =	ft_freethis.c \
		ft_putnbr_base_fd.c

OBJ		= $(SRC:.c=.o)

BOBJ	= $(BONUS:.c=.o)

ADDOBJ	= $(ADD:.c=.o)

full: $(NAME) bonus add

all: $(NAME)

$(NAME): $(SRC) $(LIB)
	$(CC) $(CFLAGS) -c $(SRC) -I .
	ar -rc $(NAME) $(OBJ)

bonus: $(BONUS) $(LIB)
	$(CC) $(CFLAGS) -c $(BONUS) -I .
	ar -rc $(NAME) $(BOBJ)

add: $(ADD) $(LIB)
	$(CC) $(CFLAGS) -c $(ADD) -I .
	ar -rc $(NAME) $(ADDOBJ)

clean:
	rm -f $(OBJ) $(BOBJ) $(ADDOBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: full all bonus add clean fclean re bonus
