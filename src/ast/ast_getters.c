/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_accessors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 15:49:58 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/03 15:53:50 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**get_av(t_ast *node)
{
	return (node->u_value.av);
}

int	get_fd(t_ast *node)
{
	return (node->u_value.s_redir.fd);
}

bool	get_quoted(t_ast *node)
{
	return (node->u_value.s_redir.quoted);
}

char	*get_operand(t_ast *node)
{
	return (node->u_value.s_redir.operand);
}
