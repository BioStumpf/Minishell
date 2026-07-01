/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 16:54:01 by david             #+#    #+#             */
/*   Updated: 2026/06/16 16:47:43 by david            ###   ########.fr       */
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

void	set_redir_fd(t_node *node, int fd)
{
	((t_token *)node->content)->u_value.s_redir.fd = fd;
}

void	set_redir_file(t_node *node, char *file)
{
	((t_token *)node->content)->u_value.s_redir.filename = file;
}

void	set_word_tok(t_node *node, char *word, bool space)
{
	set_tok(node, WORD);
	((t_token *)node->content)->u_value.s_word.word = word;
	((t_token *)node->content)->u_value.s_word.space = space;
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
