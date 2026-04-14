# Colors
RESET  = \033[0m
BOLD   = \033[1m
GREEN  = \033[32m
BLUE   = \033[34m

NAME := minishell
CC := cc

DEP_DIR := dep/
OBJ_DIR := obj/
LIBFT_DIR := libft/

SRCS = main.c
OBJS := $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))
DEPS := $(patsubst %.c, $(DEP_DIR)%.d, $(SRCS)) 
LIBFT := $(addprefix $(LIBFT_DIR), libft.a)

CFLAGS_OBJS = -Wall -Wextra -Werror -g -c $< -o $@ -I$(LIBFT_DIR)
CFLAGS_NAME = -Wall -Wextra -Werror -g -o $@ $(OBJS) $(LIBFT)
DEP_FLAGS = -MMD -MP -MT $@ -MF $(DEP_DIR)$*.d

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) 
	@echo 
	@echo "$(GREEN)==$(BOLD)$(BLUE)Executable$(GREEN)==$(RESET)"
	$(CC) $(CFLAGS_NAME)

$(LIBFT): FORCE
	@echo "$(GREEN)==$(BOLD)$(BLUE)Libft/Objs$(GREEN)==$(RESET)"
	$(MAKE) --no-print-directory -sC $(LIBFT_DIR)

FORCE:
	@echo "$(GREEN)======================================$(RESET)"
	@echo "$(BOLD)$(BLUE)       Compile Project          $(RESET)"
	@echo "$(GREEN)======================================$(RESET)"

test:
	@$(MAKE) -s all
	@cc tests/base_test.c -Ilibft -Llibft -lft -lcriterion -o test
	@echo "$(GREEN)======================================$(RESET)"
	@echo "$(BOLD)$(BLUE)       Tester run          $(RESET)"
	@echo "$(GREEN)======================================$(RESET)"
	./test
	@$(MAKE) -s fclean
	@rm -rf test
	

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR) $(DEP_DIR)
	$(CC) $(CFLAGS_OBJS) $(DEP_FLAGS)

$(DEP_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

localclean:
	@echo "$(GREEN)======================================$(RESET)"
	@echo "$(BOLD)$(BLUE)       LOCAL CLEANING          $(RESET)"
	@echo "$(GREEN)======================================$(RESET)"
	rm -rf $(OBJ_DIR)
	rm -rf $(DEP_DIR)
	@echo 

clean: localclean
	@echo "$(GREEN)======================================$(RESET)"
	@echo "$(BOLD)$(BLUE)       CLEANING          $(RESET)"
	@echo "$(GREEN)======================================$(RESET)"
	$(MAKE) --no-print-directory -sC $(LIBFT_DIR) clean
	@echo 

fclean: localclean
	@echo "$(GREEN)======================================$(RESET)"
	@echo "$(BOLD)$(BLUE)       FCLEANING          $(RESET)"
	@echo "$(GREEN)======================================$(RESET)"
	rm -rf $(NAME)
	$(MAKE) --no-print-directory -sC $(LIBFT_DIR) fclean
	@echo 

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re FORCE test
