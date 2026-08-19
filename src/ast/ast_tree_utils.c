/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 16:05:58 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 18:35:58 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "structs.h"

void	clean_ast(t_ast_buff *ast)
{
	size_t	i;
	t_ast	*node;

	i = 0;
	while (i < ast->idx)
	{
		node = &ast->buf[i++];
		if (node->type == CMD)
			free_args(ast_args(node));
		else if (is_redir(node->type))
			free(get_operand(node));
	}
	free(ast->buf);
	ft_bzero(ast, sizeof(t_ast_buff));
}

t_ast_buff	ast_init(size_t size)
{
	t_ast_buff	buf;

	buf.idx = 0;
	buf.root = 0;
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
		if (new->type == REDIR_HEREDOC)
		{
			new->u_value.s_redir.expand = comp_expand(comp);
			set_open_fd(new, comp->u_value.s_redir.open_fd);
		}
		set_fd(new, comp_fd(comp));
		set_operand(new, comp_filename(comp));
		comp->u_value.s_redir.filename = NULL;
	}
	else if (new->type == CMD)
	{
		set_args(new, comp_args(comp));
		comp->u_value.args.av = NULL;
	}
	new->left = NULL;
	new->right = NULL;
	return (new);
}
