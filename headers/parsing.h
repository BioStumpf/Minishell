/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 11:00:01 by dstumpf           #+#    #+#             */
/*   Updated: 2026/06/16 13:37:04 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "libft.h"
#include "structs.h"

///////////////////////////////////////////
//tokenizer structs and enums
///////////////////////////////////////////
//task: add to tokenizer the capability of directly associating the next word as 
//union contains either redir or word to save memory. 
//space boolean is to later be capable for redirections to find out about whether the word is associated with the redir after or not (1< file vs 1 < file note the first one belongs to the redir while the second one doesnt)
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

//////////////////
//functions
//////////////////
//not parsing related, combines tokenizer and parser together
void	parse_input(t_data *dat);

//////////////////
//tokenizer
//////////////////
//main function
t_list				*tokenize(t_data *data);

//helpers for word and metatokens
int					double_tok_type(char metachar);
size_t				get_word_len(char *input, t_data *dat);
void				set_word(char **input, char *word, size_t word_len);


//utilities for linked list
t_node				*new_token_node(void);
void				set_redir_tok(t_node *node, enum e_token ttype, int fd, char *file);
void				set_word_tok(t_node *node, enum e_token ttype, char *word, bool space);
void				set_tok(t_node *node, enum e_token ttype);

//utilities for accessing linked list token attributes
char				*tok_word(t_node *node);
char				*tok_filename(t_node *node);
int					tok_fd(t_node *node);
enum e_token		tok_type(t_node *node);

//string utilities
char				is_double_metachar(char *input);
char				is_single_metachar(char c);
char				is_whitespace_metachar(char c);
char				is_quote(char c);
char				skip_whitespace(char **str);

//to_delete_functions (just usefull for now)
void				print_token(void *content); //this need to be removed
									//
//cleanup
void				free_token(void *token);
void				token_cleanup(t_list *lst, enum e_err status, t_data *dat, t_node *n);

//////////////////
//parser
//////////////////


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
			int		fd;
			char	*filename;
		} s_redir;
	} u_value;
}	t_compound;

typedef struct	s_compound_arr
{
	size_t		len;
	t_compound	*arr;
}				t_compound_arr;

//functions
//accessors for compounds
enum e_token		comp_type(t_compound *comp);
int					comp_fd(t_compound *comp);
char				*comp_filename(t_compound *comp);
t_arg				*comp_args(t_compound *comp);
size_t				arg_size(t_compound *comp);
size_t				arg_capacity(t_compound *comp);
char				**arg_av(t_compound *comp);
size_t				arr_len(t_compound_arr *comps);
t_compound			*arr_get(t_compound_arr *comps, size_t idx);

//dynamic argument array
bool				init_args(t_arg *args);
void				*add_arg(t_arg *args, size_t idx, char *arg);
void				free_args(t_arg *args);

//compound forming and freeing
t_compound_arr		*compound_group(t_data *dat, t_list *tokens);
void				free_compound(t_compound_arr *ca, enum e_err status, t_data *dat);

//to_delete_functions (just usefull for now)
void				print_token(void *content); //this need to be removed
void				print_compound(t_compound_arr *compounds);

#endif
