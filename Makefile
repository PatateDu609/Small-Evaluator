NAME			=	$(shell pwd | rev | cut -d'/' -f1 | rev)
CC				=	clang++
OBJS			=	$(SRCS:.cpp=.o)
CFLAGS			=	-Wall -Werror -Wextra -std=c++98 -g
LDFLAGS			=	-fsanitize=address -fsanitize=leak -g

SRCS			=	main.cpp		\
					Lexer.cpp		\
					Evaluator.cpp	\
					Fixed.cpp	\

%.o:			%.cpp
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJS)
				$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)

all:			$(NAME)

clean:
				rm -f $(OBJS)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
# $(shell pwd | rev | cut -d'/' -f1 | rev)
