/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_delete_later.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 17:02:23 by david             #+#    #+#             */
/*   Updated: 2026/05/06 16:49:54 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "parsing.h"

void	print_token(void *content)
{
	char *token_map[253];
	token_map[WORD] = "WORD";
	token_map[PIPE] = "PIPE";
	token_map[AND] = "AND";
	token_map[OR] = "OR";
	token_map[REDIR_INFILE] = "REDIR_INFILE";
	token_map[REDIR_OUTFILE] = "REDIR_OUTFILE";
	token_map[REDIR_HEREDOC] = "REDIR_HEREDOC";
	token_map[REDIR_APPEND] = "REDIR_APPEND";
	token_map[LEFT_PARA] = "LEFT_PARA";
	token_map[RIGHT_PARA] = "RIGHT_PARA";
	// token_map[T_SPACE] = "SPACE";
	// token_map[T_NEWLINE] = "NEWLINE";
	// token_map[T_TAB] = "TAB";
	// token_map[T_SEMICOLON] = "SEMICOLON";
	t_token *tok = (t_token *)content;
	printf("Type: %s  ", token_map[tok->type]);
	if (tok->type == WORD)
		printf("Word: %s", tok->word->lexeme);
	printf("\n");
}
