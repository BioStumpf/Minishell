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

SRCS_main := main.c error_handling.c
SRCS_david := parsing.c tokenize.c to_delete_later.c token_list_utils.c token_string_utils.c parser_cleanup.c token_word_utils.c token_metachar_utils.c
SRCS_kian := 
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
	@echo -e 
	@echo -e "$(GREEN)==$(BOLD)$(BLUE)Executable$(GREEN)==$(RESET)"
	$(CC) $(CFLAGS_NAME)

$(LIBFT): FORCE
	@echo -e "$(GREEN)==$(BOLD)$(BLUE)Libft/Objs$(GREEN)==$(RESET)"
	$(MAKE) --no-print-directory -sC $(LIBFT_DIR)

FORCE:
	@echo -e "$(GREEN)======================================$(RESET)"
	@echo -e "$(BOLD)$(BLUE)       Compile Project          $(RESET)"
	@echo -e "$(GREEN)======================================$(RESET)"

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
	@echo -e "$(GREEN)======================================$(RESET)"
	@echo -e "$(BOLD)$(BLUE)       LOCAL CLEANING          $(RESET)"
	@echo -e "$(GREEN)======================================$(RESET)"
	rm -rf $(OBJ_DIR)
	rm -rf $(DEP_DIR)
	@echo -e 

clean: localclean
	@echo -e "$(GREEN)======================================$(RESET)"
	@echo -e "$(BOLD)$(BLUE)       CLEANING          $(RESET)"
	@echo -e "$(GREEN)======================================$(RESET)"
	$(MAKE) --no-print-directory -sC $(LIBFT_DIR) clean
	@echo -e 

fclean: localclean
	@echo -e "$(GREEN)======================================$(RESET)"
	@echo -e "$(BOLD)$(BLUE)       FCLEANING          $(RESET)"
	@echo -e "$(GREEN)======================================$(RESET)"
	rm -rf $(NAME)
	$(MAKE) --no-print-directory -sC $(LIBFT_DIR) fclean
	@echo -e 

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re FORCE test
