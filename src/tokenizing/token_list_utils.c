/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 16:54:01 by david             #+#    #+#             */
/*   Updated: 2026/05/26 15:05:34 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "stdlib.h"

t_token	*fetch_token(t_node *node)
{
	return ((t_token *)node->content);
}

static t_token	*token_new(void)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = NONE;
	token->word = NULL;
	return (token);
}

void	set_token_node(t_node *node, enum e_token ttype, char *word)
{
	((t_token *)node->content)->type = ttype;
	((t_token *)node->content)->word = word;
}

t_node	*new_token_node(void)
{
	t_token	*token;
	t_node	*node;

	token = token_new();
	if (!token)
		return (NULL);
	node = ft_nodenew(token);
	if (!node)
		return (free(token), NULL);
	return (node);
}
