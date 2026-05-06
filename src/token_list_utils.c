/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 16:54:01 by david             #+#    #+#             */
/*   Updated: 2026/05/06 21:56:43 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "stdlib.h"

static t_token	*token_new(void)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = T_NONE;
	token->quote = Q_NONE;
	token->word = NULL;
	return (token);
}

void	free_token(void *token)
{
	// free(((t_token *)token)->word);
	free(token);
}

void	token_cleanup(t_list *lst)
{
	int	ret_value;

	ret_value = print_error();
	ft_lstclear(lst, free_token);
	exit(ret_value);
}

void	set_token_node(t_node *node, enum e_token ttype, enum e_quote qtype, char *word)
{
	((t_token *)node->content)->type = ttype;
	((t_token *)node->content)->quote = qtype;
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
