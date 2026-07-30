/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_setters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 15:49:58 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/30 12:26:30 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	set_av(t_ast *node, char **av)
{
	node->u_value.av = av;
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
