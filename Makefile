G++						=	g++
###############################################
EX0_PATH 				= 	./Ex0_Droids
EX0_SRC_PATH			=	./Ex0_Droids/src
EX0_TST_PATH			=	./Ex0_Droids/test
EX0_INC_PATH			=	./Ex0_Droids/include
NAME_EX0				=	Ex0
# EX0_SRC					=	$(EX0_SRC_PATH)/.cpp

EX0_SRC_TEST			=	$(EX0_TST_PATH)/$(NAME_EX0)_test.cpp
TEST_NAME_EX0 			= 	test_$(NAME_EX0)

#################################################
EX1_PATH 				= 	./Ex1_DroidMemory
EX1_SRC_PATH			=	./Ex1_DroidMemory/src
EX1_TST_PATH			=	./Ex1_DroidMemory/test
EX1_INC_PATH			=	./Ex1_DroidMemory/include
NAME_EX1				=	Ex1
# EX0_SRC					=	$(EX0_SRC_PATH)/.cpp

EX1_SRC_TEST			=	$(EX1_TST_PATH)/$(NAME_EX1)_test.cpp
TEST_NAME_EX1 			= 	test_$(NAME_EX1)

#################################################

# OBJS					=	$(SRCS:.cpp=.o)
CLEAN					=	clean
FCLEAN					=	fclean
RM						=	rm -rf

clean					:	
							$(RM) $(OBJS)
							@$(MAKE) $(CLEAN) -C $(EX0_TST_PATH)
							@$(MAKE) $(CLEAN) -C $(EX1_TST_PATH)


fclean					:	clean
							$(RM) $(NAME) $(TEST_NAME_EX0)
							@$(MAKE) $(FCLEAN) -C $(EX0_TST_PATH)
							@$(MAKE) $(FCLEAN) -C $(EX0_PATH)
							@$(MAKE) $(FCLEAN) -C $(EX1_TST_PATH)
							@$(MAKE) $(FCLEAN) -C $(EX1_PATH)

re						: 	fclean all

Ex0 					: 	fclean
							@$(MAKE) -C $(EX0_PATH)
							$(EX0_PATH)/$(NAME_EX0)

Ex1 					: 	fclean
							@$(MAKE) -C $(EX1_PATH)
							$(EX1_PATH)/$(NAME_EX1)

test_run_Ex0			:	fclean
							@$(MAKE) -C $(EX0_TST_PATH)
							$(EX0_TST_PATH)/$(TEST_NAME_EX0)
							gcovr --exclude-unreachable-branches --exclude-throw-branches -r . --txt --html-details coverage.html

test_run_Ex1			:	fclean
							@$(MAKE) -C $(EX0_TST_PATH)
							$(EX0_TST_PATH)/$(TEST_NAME_EX0)
							gcovr --exclude-unreachable-branches --exclude-throw-branches -r . --txt --html-details coverage.html

tests_run				:	fclean
							@$(MAKE) tests_run_Ex0
							@echo "Press Enter to continue to the next test (Ex1)..."
							@read dummy
							@$(MAKE) tests_run_Ex1
							@echo "Press Enter to continue to the next test (Ex2)..."
							@read dummy
# @$(MAKE) tests_run_Ex1
# @echo "Press Enter to continue to the next test (Ex2)..."
# @read dummy
# @$(MAKE) tests_run_Ex2
# @echo "Press Enter to continue to the next test (Ex3)..."
# @read dummy
# @$(MAKE) tests_run_Ex3
# @echo "Press Enter to continue to the next test (Ex4)..."
# @read dummy
# @$(MAKE) tests_run_Ex4

.PHONY					: 	all clean fclean re \
							tests_run \
							Ex0 tests_run_Ex0