/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 16:54:01 by david             #+#    #+#             */
/*   Updated: 2026/05/06 16:48:32 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "stdlib.h"

static t_word	*word_new(enum e_quote quote, char *lexeme)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->quote = quote;
	word->lexeme = lexeme;
	return (word);
}

static t_token	*token_new(enum e_token type, t_word *word)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->word = word;
	return (token);
}

void	free_token(void *token)
{
	free(((t_token *)token)->word);
	free(token);
}

void	token_cleanup(t_list *lst, t_parse_err *err)
{
	if (err->status == PARSE_ERR_MALLOC)
		ft_putstr_fd("Malloc fail.", 2);
	else if (err->status == PARSE_ERR_INVALID_CHAR)
		ft_putstr_fd("minishell: syntax error near unexpected token", 2);
	ft_lstclear(lst, free_token);
	exit(1);
}

t_node	*new_token_node(enum e_token type, enum e_quote quote, char *lexeme)
{
	t_token	*token;
	t_word	*word;
	t_node	*node;

	word = NULL;
	if (type == WORD)
	{
		word = word_new(quote, lexeme);
		if (!word)
			return (NULL);
	}
	token = token_new(type, word);
	if (!token)
		return (free(word), NULL);
	node = ft_nodenew(token);
	if (!node)
		return (free(word), free(token), NULL);
	return (node);
}
