/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_getters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 15:49:58 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 18:36:57 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**get_av(t_ast *node)
{
	return (node->u_value.args.av);
}

size_t	ast_arg_len(t_ast *node)
{
	return (node->u_value.args.size);
}

int	get_fd(t_ast *node)
{
	return (node->u_value.s_redir.fd);
}

int	get_open_fd(t_ast *node)
{
	return (node->u_value.s_redir.open_fd);
}

char	*get_operand(t_ast *node)
{
	return (node->u_value.s_redir.operand);
}
