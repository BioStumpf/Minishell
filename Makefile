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

SRCS_main := main.c error/error_handling.c readline_signals/read_input.c readline_signals/sighandler.c
SRCS_david := parsing_glue/parsing.c parsing_glue/to_delete_later.c parsing_glue/parser_cleanup.c \
			  tokenizing/tokenize.c tokenizing/token_list_utils.c tokenizing/token_string_utils.c tokenizing/token_word_utils.c tokenizing/token_metachar_utils.c tokenizing/token_accessors.c tokenizing/token_redir_utils.c tokenizing/token_setters.c \
			  compounds/compound.c compounds/dynamic_compound_array.c compounds/comp_accessors.c compounds/comp_arg_accessors.c compounds/comp_array_accessors.c \
			  expansion/expand.c expansion/expand_split_compounds.c expansion/expansion_accessors.c expansion/expansion_vector.c expansion/find_expansions.c expansion/insert_expansion.c expansion/trim_expansions.c expansion/word_split.c expansion/word_split_utils.c expansion/heredoc.c expansion/reopen_heredoc.c \
			  ast/ast_getters.c ast/ast_setters.c ast/ast_tree_utils.c ast/ast.c ast/check_tok_types.c ast/check_tok_types2.c ast/recursive_decent.c ast/redir_utils.c

SRCS_kian := env/delete_env.c env/hash_search.c env/new_variables.c env/env.c env/env_swap_func.c\
builtins/which_builtin.c builtins/unset.c builtins/pworkdir.c builtins/export.c builtins/exit.c builtins/env_bi.c builtins/echo.c builtins/changedir.c \
cmd/execution.c cmd/pathfinder.c cmd/pipex_utils.c cmd/redirections.c cmd/and_or.c cmd/pipe.c cmd/extern_builtin.c \
error/cleanup_error.c error/error_print.c
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
	@printf "\n"
	@printf "$(GREEN)==$(BOLD)$(BLUE)Executable$(GREEN)==$(RESET)\n"
	$(CC) $(CFLAGS_NAME)

$(LIBFT): FORCE
	@printf "$(GREEN)==$(BOLD)$(BLUE)Libft/Objs$(GREEN)==$(RESET)\n"
	$(MAKE) --no-print-directory -sC $(LIBFT_DIR)

FORCE:
	@printf "$(GREEN)======================================$(RESET)\n"
	@printf "$(BOLD)$(BLUE)       Compile Project          $(RESET)\n"
	@printf "$(GREEN)======================================$(RESET)\n"

norm:
	./norm.sh

test:
	@cc tests/base_test.c -Ilibft -Llibft -lft -lcriterion -o test
	@./test
	rm -rf test

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c | $(OBJ_DIR) $(DEP_DIR)
	@mkdir -p $(dir $@) $(dir $(DEP_DIR)$*.d)
	$(CC) $(CFLAGS_OBJS) $(DEP_FLAGS)

$(DEP_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

localclean:
	@printf "$(GREEN)======================================$(RESET)\n"
	@printf "$(BOLD)$(BLUE)       LOCAL CLEANING          $(RESET)\n"
	@printf "$(GREEN)======================================$(RESET)\n"
	rm -rf $(OBJ_DIR)
	rm -rf $(DEP_DIR)
	@printf "\n"

clean: localclean
	@printf "$(GREEN)======================================$(RESET)\n"
	@printf "$(BOLD)$(BLUE)       CLEANING          $(RESET)\n"
	@printf "$(GREEN)======================================$(RESET)\n"
	$(MAKE) --no-print-directory -sC $(LIBFT_DIR) clean
	@printf "\n"

fclean: localclean
	@printf "$(GREEN)======================================$(RESET)\n"
	@printf "$(BOLD)$(BLUE)       FCLEANING          $(RESET)\n"
	@printf "$(GREEN)======================================$(RESET)\n"
	rm -rf $(NAME)
	$(MAKE) --no-print-directory -sC $(LIBFT_DIR) fclean
	@printf "\n"

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re FORCE test
