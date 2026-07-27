/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 20:06:33 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/05 20:07:40 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast	*parse_redir(t_data *dat, t_compound_arr *ca, size_t *i)
{
	t_ast	*redir;
	t_ast	*tmp;

	if (!is_ast_redir(ca, *i))
		return (NULL);
	redir = new_ast_node(&dat->ast, get_comp(ca, (*i)++));
	tmp = redir;
	while (is_ast_redir(ca, *i))
	{
		tmp->left = new_ast_node(&dat->ast, get_comp(ca, (*i)++));
		tmp = tmp->left;
	}
	return (redir);
}
//
// t_ast	*last_redir(t_ast *node)
// {
// 	while (node && node->left)
// 		node = node->left;
// 	return (node);
// }
