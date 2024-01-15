##
## EPITECH PROJECT, 2024
## Self Project
## File description:
## Makefile
##

NAME			:=	libgc.a
CC				:=	gcc
RM				:=	rm -rf
UNIT_TESTS		:=	unit_tests
CPPFLAGS		:=	-Wall -Wextra -Werror -pedantic --coverage
TESTS_SRCS		:=	$(shell find tests/ -name 'tests_*.c')
TESTS_OBJS		:=	$(TESTS_SRCS:.c=.o)
SRCS			:=	$(shell find . ! -path tests/ ! -name main.c -name '*.c')
OBJS			:=	$(SRCS:.c=.o)

all: $(NAME) tests_run

$(NAME):	$(OBJS)
	@ar rcs $(NAME) $(OBJS)

tests_run: $(TESTS_OBJS) $(NAME)
	@$(CC) $(CPPFLAGS) $(TESTS_OBJS) -o $(UNIT_TESTS) -lcriterion -L. -lgc
	@./$(UNIT_TESTS)
	@gcovr -e tests/ .

clean:
	@$(RM) $(shell find . -name '*.gcda') \
		$(shell find . -name '*.gcno') \
		$(TESTS_OBJS) \
		$(OBJS)

fclean: clean
	@$(RM) $(UNIT_TESTS) $(NAME)

re: fclean all

.PHONY: all tests_run clean fclean re
