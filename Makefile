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
SRCS_DIR := src/
HEADER_DIR := headers/

SRCS_main := main.c
SRCS_david := parsing.c tokenize.c
SRCS_kian := env.c cleanup.c new_variables.c hash_search.c 
SRCS := $(SRCS_main) $(SRCS_kian) $(SRCS_david)
SRCS := $(addprefix $(SRCS_DIR), $(SRCS))
OBJS := $(patsubst $(SRCS_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))
DEPS := $(patsubst $(SRCS_DIR)%.c, $(DEP_DIR)%.d, $(SRCS)) 
LIBFT := $(addprefix $(LIBFT_DIR), libft.a)

LIB_LINKS := $(LIBFT) -lreadline

CFLAGS_OBJS = -Wall -Wextra -Werror -g -c $< -o $@ -I$(LIBFT_DIR) -I$(HEADER_DIR)
CFLAGS_NAME = -Wall -Wextra -Werror -g -o $@ $(OBJS) $(LIB_LINKS) 
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
	@cc tests/base_test.c -Ilibft -Llibft -lft -lcriterion -o test
	@./test
	rm -rf test
	

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c | $(OBJ_DIR) $(DEP_DIR)
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
