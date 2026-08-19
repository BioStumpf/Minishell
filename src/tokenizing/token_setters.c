/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_setters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 18:46:32 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 18:46:33 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
