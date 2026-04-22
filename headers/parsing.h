/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:23:19 by dstumpf           #+#    #+#             */
/*   Updated: 2026/04/22 14:39:32 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "main.h"

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

enum e_token
{
	WORD,
	PIPE,
	AND,
	OR,
	REDIR_INFILE,
	REDIR_OUTFILE,
	REDIR_HEREDOC,
	REDIR_APPEND,
	LEFT_PARA,
	RIGHT_PARAN
};

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

//functions
void	parse_input(t_data *dat);
t_token	*tokenize(t_data *data);
void	print_tokens(t_token *token);



///////////////////////////////////////////
//compound commands structs and enums
///////////////////////////////////////////

//structs and enums
#endif
