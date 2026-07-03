/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 16:05:58 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/03 16:17:56 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast_buff	ast_init(size_t size)
{
	t_ast_buff	buf;

	buf.idx = 0;
	buf.buf = malloc(sizeof(t_ast) * size);
	return (buf);
}

t_ast	*new_ast_node(t_ast_buff *buf, t_compound *comp)
{
	t_ast	*new;

	new = &buf->buf[buf->idx++];
	new->type = comp->type;
	if (is_redir(new->type))
	{
		set_quoted(new, comp->u_value.s_redir.quoted);
		set_fd(new, comp_fd(comp));
		set_operand(new, comp_filename(comp));
	}
	else if (new->type == CMD)
		set_av(new, arg_av(comp));
	return (new);
}
