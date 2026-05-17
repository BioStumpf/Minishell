/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:23:19 by dstumpf           #+#    #+#             */
/*   Updated: 2026/05/17 21:36:13 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "main.h"
#include "libft.h"

///////////////////////////////////////////
//tokenizer structs and enums
///////////////////////////////////////////

//structs and enums
enum e_token
{
	T_NONE,
	T_WORD,
	T_PIPE = '|',
	T_AND	= '&' * 2 + 1,
	T_OR = '|' * 2 + 1,
	T_REDIR_INFILE = '<',
	T_REDIR_OUTFILE = '>',
	T_REDIR_HEREDOC = '<' * 2 + 1,
	T_REDIR_APPEND = '>' * 2 + 1,
	T_LEFT_PARA = '(',
	T_RIGHT_PARA = ')',
	SPACE = ' ',
	TAB = ' ',
	NEWLINE = ' '

};

typedef struct s_token
{
	enum e_token	type;
	char			*word;
}					t_token;

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
void				set_token_node(t_node *new, enum e_token ttype, char *word);

//string utilities
char				is_double_metachar(char *input);
char				is_single_metachar(char c);
char				is_whitespace_metachar(char c);
char				is_quote(char c);

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
#endif
