/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:23:19 by dstumpf           #+#    #+#             */
/*   Updated: 2026/05/06 16:42:25 by david            ###   ########.fr       */
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
enum e_quote
{
	NONE,
	SINGLE,
	DOUBLE
};

//enum e_token
//{
//	WORD,
//	PIPE,
//	AND,
//	OR,
//	REDIR_INFILE,
//	REDIR_OUTFILE,
//	REDIR_HEREDOC,
//	REDIR_APPEND,
//	LEFT_PARA,
//	RIGHT_PARA
//};
enum e_token
{
	WORD,
	PIPE = '|',
	AND	= '&' * 2 + 1,
	OR = '|' * 2 + 1,
	REDIR_INFILE = '<',
	REDIR_OUTFILE = '>',
	REDIR_HEREDOC = '<' * 2 + 1,
	REDIR_APPEND = '>' * 2 + 1,
	LEFT_PARA = '(',
	RIGHT_PARA = ')',
	// T_SPACE = ' ',
	// T_NEWLINE = '\n',
	// T_TAB = '\t',
	// T_SEMICOLON = ';'
};

enum e_parse_err
{
    PARSE_OK,
    PARSE_ERR_MALLOC,
    PARSE_ERR_INVALID_CHAR,
};

typedef struct s_parse_err
{
	enum e_parse_err	status;
	char				invalid;
}						t_parse_err;

typedef struct s_word
{
	enum e_quote	quote; 
	char			*lexeme;
}					t_word;

typedef struct s_token
{
	enum e_token	type;
	t_word			*word;
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
t_list	*tokenize(t_data *data);

//utilities for linked list
t_node	*new_token_node(enum e_token type, enum e_quote quote, char *lexeme);

//string utilities
char	get_metachar(char c);
char	is_double_metachar(char c);
char	skip_metachar(char c);
char	invalid_metachar(char c);

//to_delete_functions (just usefull for now)
void	print_token(void *content); //this need to be removed
									//
//cleanup
void	free_token(void *token);
void	token_cleanup(t_list *lst, t_parse_err *err);

//////////////////
//parser
//////////////////


///////////////////////////////////////////
//compound commands structs and enums
///////////////////////////////////////////

//structs and enums
#endif
