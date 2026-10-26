NAME        = codexion

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread
INC_DIR     = includes
INCLUDES    = -I$(INC_DIR)

SRC_DIR     = src
OBJ_DIR     = obj

SRCS        = main.c \
			  parser.c

OBJS        = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
HEADERS     = $(INC_DIR)/codexion.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re