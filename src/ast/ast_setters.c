/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_setters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 15:49:58 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/03 15:58:13 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	set_av(t_ast *node, char **av)
{
	node->u_value.av = av;
}

void	set_fd(t_ast *node, size_t fd)
{
	node->u_value.s_redir.fd = fd;
}

void	set_operand(t_ast *node, char *s)
{
	node->u_value.s_redir.operand = s;
}

void	set_quoted(t_ast *node, bool quoted)
{
	node->u_value.s_redir.quoted = quoted;
}
