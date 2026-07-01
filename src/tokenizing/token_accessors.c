/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_accessors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 19:11:00 by dstumpf           #+#    #+#             */
/*   Updated: 2026/06/16 13:06:09 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

enum e_token	tok_type(t_node *node)
{
	return (((t_token *)node->content)->type);
}

int	tok_fd(t_node *node)
{
	return (((t_token *)node->content)->u_value.s_redir.fd);
}

char	*tok_filename(t_node *node)
{
	return (((t_token *)node->content)->u_value.s_redir.filename);
}

char	*tok_word(t_node *node)
{
	return (((t_token *)node->content)->u_value.s_word.word);
}

bool	tok_space(t_node *node)
{
	return (((t_token *)node->content)->u_value.s_word.space);
}
