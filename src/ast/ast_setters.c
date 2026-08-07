/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_setters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 15:49:58 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/06 16:51:32 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_arg	*ast_args(t_ast *node)
{
	return (&node->u_value.args);
}

void	set_args(t_ast *node, t_arg *args)
{
	node->u_value.args = *args;
}

void	set_fd(t_ast *node, int fd)
{
	node->u_value.s_redir.fd = fd;
}

void	set_operand(t_ast *node, char *s)
{
	node->u_value.s_redir.operand = s;
}

void	set_open_fd(t_ast *node, int open_fd)
{
	node->u_value.s_redir.open_fd = open_fd;
}
