NAME = push_swap
BONUS_NAME = checker

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCDIR = src
INCDIR = includes

SRCS = $(SRCDIR)/main.c \
       $(SRCDIR)/algorithms/small_sort.c \
       $(SRCDIR)/algorithms/compress.c \
       $(SRCDIR)/algorithms/turk_helpers.c \
       $(SRCDIR)/algorithms/turk_algorithm.c \
       $(SRCDIR)/algorithms/turk_cost.c \
       $(SRCDIR)/algorithms/turk_rotate.c \
       $(SRCDIR)/algorithms/turk_execute.c \
       $(SRCDIR)/parser/input_check.c \
       $(SRCDIR)/parser/overflow_check.c \
       $(SRCDIR)/parser/list_parser.c \
       $(SRCDIR)/operations/list_rotate.c \
       $(SRCDIR)/operations/list_push.c \
       $(SRCDIR)/operations/list_reverse_rotate.c \
       $(SRCDIR)/operations/list_swap.c \
       $(SRCDIR)/stack/list_init.c \
       $(SRCDIR)/stack/list_operations.c \
       $(SRCDIR)/stack/list_utils.c \
       $(SRCDIR)/stack/list_search.c \
       $(SRCDIR)/stack/list_free.c \
       $(SRCDIR)/utils/utils.c

BONUS_SRCS = $(SRCDIR)/checker_bonus.c \
             $(SRCDIR)/checker/input_reader_bonus.c \
             $(SRCDIR)/checker/operation_executor_bonus.c \
             $(SRCDIR)/parser/input_check.c \
             $(SRCDIR)/parser/overflow_check.c \
             $(SRCDIR)/parser/list_parser.c \
             $(SRCDIR)/operations/list_rotate.c \
             $(SRCDIR)/operations/list_push.c \
             $(SRCDIR)/operations/list_reverse_rotate.c \
             $(SRCDIR)/operations/list_swap.c \
             $(SRCDIR)/stack/list_init.c \
             $(SRCDIR)/stack/list_operations.c \
             $(SRCDIR)/stack/list_utils.c \
             $(SRCDIR)/stack/list_search.c \
             $(SRCDIR)/stack/list_free.c \
             $(SRCDIR)/utils/utils.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

test: $(NAME)
	./test_push_swap.sh

.PHONY: all bonus clean fclean re test
