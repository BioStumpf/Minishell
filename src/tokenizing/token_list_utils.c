/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 16:54:01 by david             #+#    #+#             */
/*   Updated: 2026/06/04 19:05:25 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "stdlib.h"
#include "structs.h"

static t_token	*token_new(void)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = NONE;
	ft_bzero(token, sizeof(t_token));
	return (token);
}

void	set_redir_tok(t_node *node, enum e_token ttype, int fd, char *file)
{
	((t_token *)node->content)->type = ttype;
	((t_token *)node->content)->u_value.s_redir.fd = fd;
	((t_token *)node->content)->u_value.s_redir.filename = file;
}

void	set_word_tok(t_node *node, enum e_token ttype, char *word)
{
	((t_token *)node->content)->type = ttype;
	((t_token *)node->content)->u_value.word = word;
}

void	set_tok(t_node *node, enum e_token ttype)
{
	((t_token *)node->content)->type = ttype;
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
