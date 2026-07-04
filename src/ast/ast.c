/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 17:06:49 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/04 16:48:53 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "err.h"
#include "structs.h"

// static bool	is_or(t_compound_arr *ca, size_t *i)
// {
// 	return (i < ca->len && comp_type(get_comp(ca, i)) == AND);
// }
//
// static bool	is_and(t_compound_arr *ca, size_t *i)
// {
// 	return (i < ca->len && comp_type(get_comp(ca, i)) == OR);
// }

// static bool	is_left_par(t_compound_arr *ca, size_t i)
// {
// 	return (i < ca->len && comp_type(get_comp(ca, i)) == LEFT_PARA);
// }
//
// static bool	is_right_par(t_compound_arr *ca, size_t i)
// {
// 	return (i < ca->len && comp_type(get_comp(ca, i)) == LEFT_PARA);
// }

static bool	is_pipe(t_compound_arr *ca, size_t i)
{
	return (i < ca->len && comp_type(get_comp(ca, i)) == PIPE);
}

static bool	is_cmd(t_compound_arr *ca, size_t i)
{
	return (i < ca->len && comp_type(get_comp(ca, i)) == CMD);
}

static bool	is_ast_redir(t_compound_arr *ca, size_t i)
{
	return (i < ca->len && is_redir(comp_type(get_comp(ca, i))));
}

static t_ast	*parse_redir(t_data *dat, t_compound_arr *ca, size_t *i)
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

static t_ast	*last_redir(t_ast *node)
{
	while (node && node->left)
		node = node->left;
	return (node);
}

static t_ast	*ast_parser(t_data *dat, t_compound_arr *ca, size_t *i);
static t_ast	*parse_cmd(t_data *dat, t_compound_arr *ca, size_t *i)
{
	t_ast	*redirs;
	t_ast	*cmd;

	// if (is_left_par(ca, *i))
	// 	ast_parser(dat, ca, i);
	redirs = parse_redir(dat, ca , i);
	if (is_cmd(ca, *i))
	{
		cmd = new_ast_node(&dat->ast, get_comp(ca, (*i)++));
		cmd->left = redirs;
		redirs = last_redir(cmd);
		redirs->left = parse_redir(dat, ca, i);
		return (cmd);
	}
	return (NULL);
}

static t_ast	*ast_parser(t_data *dat, t_compound_arr *ca, size_t *i)
{
	t_ast	*left;
	t_ast	*new;

	left = parse_cmd(dat, ca, i);
	while (is_pipe(ca, *i))
	{
		new = new_ast_node(&dat->ast, get_comp(ca, (*i)++));
		new->left = left;
		new->right = parse_cmd(dat, ca, i);
		left = new;
	}
	return (left);
}

void	built_ast(t_data *dat, t_compound_arr *ca)
{
	size_t	i;

	i = 0;
	if (!ca)
		return ;
	dat->ast = ast_init(ca->len);
	if (!dat->ast.buf)
		return (set_error(dat, ERR_MALLOC));
	dat->ast.root = ast_parser(dat, ca, &i);
}
