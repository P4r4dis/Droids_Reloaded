G++			=	g++
##############################################
BIN_PATH	=	./bin
SRC_PATH	=	./source
TST_PATH	=	./test
INC_PATH	=	./include

NAME		=	Ex0
TEST_NAME 	= 	test_$(NAME)
##############################################

INCFLAGS	+=	-I $(INC_PATH)

CPPFLAGS	+= -Wall -Wextra -Werror $(INCFLAGS) -W -std=c++23


SRCS		=	$(SRC_PATH)/Droid.cpp \
				$(BIN_PATH)/main.cpp

SRC_TEST	=	$(TST_PATH)/$(NAME)_test.cpp

OBJS		=	$(SRCS:.cpp=.o)

CLEAN		=	clean
FCLEAN		=	fclean


all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(G++) $(OBJS) -o $(NAME) $(CPPFLAGS)

RM			=	rm -rf

clean		:
				$(RM) $(OBJS)
				@$(MAKE) $(CLEAN) -C $(TST_PATH)

fclean		:	clean
				$(RM) $(NAME) $(TEST_NAME)
				@$(MAKE) $(FCLEAN) -C $(TST_PATH)

re			: 	fclean all

tests_run	:	fclean
				@$(MAKE) -C $(TST_PATH)
				$(TST_PATH)/$(TEST_NAME)

.PHONY		: 	all clean fclean re tests_run