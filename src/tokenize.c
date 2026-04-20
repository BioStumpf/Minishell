/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:15:50 by dstumpf           #+#    #+#             */
/*   Updated: 2026/04/20 15:38:08 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "stdlib.h"
#include "libft.h"

#include "stdio.h"
void	print_tokens(t_token *token)
{
	while (token)
	{
		printf("%s\n", token->word->lexeme);
		token = token->next;
	}
}

t_token	*tokenize(t_data *dat)
{
	t_token *tokens = malloc(sizeof(t_token));

	tokens->word = malloc(sizeof(t_word));
	tokens->word->lexeme = malloc(sizeof(char) * 2);
	tokens->word->lexeme[0] = dat->input[0];
	tokens->word->lexeme[1] = 0;
	tokens->next = NULL;
	return (tokens);
}
