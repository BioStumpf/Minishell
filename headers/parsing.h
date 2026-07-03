/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 11:00:01 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/03 16:19:19 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "structs.h"

# define SPCE " \t\n"
# define RM_QUOTES true
# define KEEP_QUOTES false

///////////////////////////////////////////
//tokenizer structs and enums
///////////////////////////////////////////
//task: add to tokenizer the capability of directly associating the 
//next word as union contains either redir or word to save memory. 
//space boolean is to later be capable for redirections to find 
//out about whether the word is associated with the redir after 
//or not (1< file vs 1 < file note the first one belongs to the 
//redir while the second one doesnt)
typedef struct s_token
{
	enum e_token	type;
	union
	{
		struct
		{
			bool	space;
			char	*word;
		} s_word;
		struct
		{
			int		fd;
			char	*filename;
		} s_redir;
	} u_value;
}	t_token;

typedef struct s_quotes
{
	bool	sngl;
	bool	dbl;
}			t_quotes;

//////////////////
//functions
//////////////////
//not parsing related, combines tokenizer and parser together
void			parse_input(t_data *dat);

//////////////////
//tokenizer
//////////////////
//main function
t_list			*tokenize(t_data *data);
void			refine_redirs(t_data *dat, t_list *lst);

//helpers for word and metatokens
int				double_tok_type(char metachar);
size_t			get_word_len(char *input, t_data *dat);
void			set_word(char **input, char *word, size_t word_len);

//utilities for linked list
t_node			*new_token_node(void);
void			set_word_tok(t_node *node, char *word, bool space);
void			set_redir_tok(t_node *node, int fd, char *file);
void			set_tok(t_node *node, enum e_token ttype);
void			set_redir_fd(t_node *node, int fd);
void			set_redir_file(t_node *node, char *file);
bool			is_redir(enum e_token ttype);

//utilities for accessing linked list token attributes
char			*tok_word(t_node *node);
char			*tok_filename(t_node *node);
int				tok_fd(t_node *node);
enum e_token	tok_type(t_node *node);
bool			tok_space(t_node *node);

//string utilities
char			char_in_str(char c, const char *str);
char			is_double_metachar(char *input);
char			is_single_metachar(char c);
char			is_whitespace_metachar(char c);
bool			update_quote_status(t_quotes *quotes, char *str);
char			is_quote(char c);
char			skip_whitespace(char **str);

//to_delete_functions (just usefull for now)
void			print_token(void *content); //this need to be removed
									//
//cleanup
void			free_token(void *token);
void			token_cleanup(t_list *l, enum e_err st, t_data *d, t_node *n);

///////////////////////////////////////////
//compound commands structs and enums
///////////////////////////////////////////
//structs and enums
typedef struct s_arg
{
	size_t	size;
	size_t	capacity;
	char	**av;
}			t_arg;

typedef struct s_compound
{
	enum e_token	type;
	union
	{
		t_arg	args;
		struct
		{
			bool	quoted;
			int		fd;
			char	*filename;
		} s_redir;
	} u_value;
}	t_compound;

typedef struct s_compound_arr
{
	size_t		len;
	t_compound	*arr;
}				t_compound_arr;

//functions
//accessors for compounds
enum e_token	comp_type(t_compound *comp);
int				comp_fd(t_compound *comp);
char			*comp_filename(t_compound *comp);
t_arg			*comp_args(t_compound *comp);
size_t			arg_size(t_compound *comp);
size_t			arg_capacity(t_compound *comp);
char			**arg_av(t_compound *comp);
size_t			arr_len(t_compound_arr *comps);
t_compound		*arr_get(t_compound_arr *comps, size_t idx);

//dynamic argument array
bool			init_args(t_arg *args);
void			*add_arg(t_arg *args, size_t idx, char *arg);
void			*replace_arg(t_arg *args, size_t idx, char *arg);
void			free_args(t_arg *args);

//compound forming and freeing
t_compound_arr	*compound_group(t_data *dat, t_list *tokens);
void			free_compound(t_compound_arr *c, enum e_err s, t_data *d);

//to_delete_functions (just usefull for now)
void			print_token(void *content); //this need to be removed
void			print_compound(t_compound_arr *compounds);

///////////////////////////////////////////
// expansion
///////////////////////////////////////////
//structs
typedef struct s_exp
{
	bool	quoted;
	size_t	start;
	size_t	len;
}			t_exp;

typedef struct s_exp_vec
{
	size_t	capacity;
	size_t	size;
	t_exp	*expansions;
}			t_exp_vec;

typedef struct s_word_split
{
	size_t	tmp_idx;
	size_t	splt_idx;
	char	*tmp;
	char	*to_split;
	char	*ifs;
}			t_word_split;

///////////////////////////////////////////
//functions
///////////////////////////////////////////
//main
void			expand(t_data *dat, t_compound_arr *ca);

///////////////////////////////////////////
//expansion part
///////////////////////////////////////////
//accessors
bool			exp_quote(t_exp_vec *vec, size_t idx);
size_t			exp_start(t_exp_vec *vec, size_t idx);
size_t			exp_len(t_exp_vec *vec, size_t idx);
t_exp			*get_exp(t_exp_vec *vec, size_t idx);

//expansion vector utils
bool			init_exp_vec(t_exp_vec *vec);
void			*add_exp(t_exp_vec *vec, size_t idx, t_exp *exp);
//finding expansions
bool			is_expand_signal(char *str, bool sngl_quotes);
bool			find_expansions(t_exp_vec *exps, char *str, bool quote_removal);
//trimming quotes and dollar signs from expansions
char			*remove_dollar_quotes(t_exp_vec *e, char *s, bool qrm);
//insert expansions
char			*insert_expansions(t_data *dat, t_exp_vec *exps, char *str);
//function to take string and return expanded version of it
char			*expand_str(t_data *d, char *s, bool qrm, t_exp_vec *e);

///////////////////////////////////////////
//word splitting part
///////////////////////////////////////////
//utils
bool			in_splittable_expansion(size_t idx, t_exp *exp);
bool			expansion_used(size_t idx, t_exp *exp);
bool			new_field(t_arg *arg, char *str, size_t *str_idx);
bool			split_signal(t_word_split *ws, t_exp *exp);
char			*get_ifs(t_data *dat);
//main  
bool			word_split(t_data *d, t_exp_vec *e, t_arg *n, char *splt);

///////////////////////////////////////////
//build syntax tree
///////////////////////////////////////////
//tree utils
//accessors
char			**get_av(t_ast *node);
size_t			get_fd(t_ast *node);
bool			get_quoted(t_ast *node);
char			*get_operand(t_ast *node);
void			set_quoted(t_ast *node, bool quoted);
void			set_operand(t_ast *node, char *s);
void			set_fd(t_ast *node, size_t fd);
void			set_av(t_ast *node, char **av);

//setting up ast buffer and nodes
t_ast_buff		ast_init(size_t size);
t_ast			*new_ast_node(t_ast_buff *buf, t_compound *comp);


#endif
