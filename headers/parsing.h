/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:23:19 by dstumpf           #+#    #+#             */
/*   Updated: 2026/05/06 21:55:04 by david            ###   ########.fr       */
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
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
};

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
	char				c;
}						t_parse_err;

typedef struct s_token
{
	enum e_token	type;
	enum e_quote	quote;
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
t_list	*tokenize(t_data *data);

//utilities for linked list
t_node	*new_token_node(void);
void	set_token_node(t_node *new, enum e_token ttype, enum e_quote qtype, char *word);

//string utilities
char		get_metachar(char c);
char		is_double_metachar(char c);
char		skip_metachar(char c);
char		invalid_metachar(char c);

//to_delete_functions (just usefull for now)
void		print_token(void *content); //this need to be removed
									//
//cleanup
void		free_token(void *token);
void		token_cleanup(t_list *lst);

//error handling
void		set_error(enum e_parse_err status, char c);
t_parse_err	*fetch_error(void);
int			print_error(void);

//////////////////
//parser
//////////////////


///////////////////////////////////////////
//compound commands structs and enums
///////////////////////////////////////////

//structs and enums
#endif
