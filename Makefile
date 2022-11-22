NAME	=	tests

SRC		=	main.cpp

COMP	=	c++

WWW		=	-Wall -Wextra -Werror

STD		=	-std=c++98

OBJS	=	$(SRC:.cpp=.o)

%.o: %.cpp
	$(COMP) $(WWW) $(STD) -o $@ -c $<

$(NAME): $(OBJS)
	$(COMP) $(OBJS) -o $@

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re