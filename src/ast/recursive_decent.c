/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_decent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 20:03:03 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/07 10:12:13 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "err.h"

static t_ast	*parse_parnthesis(t_data *dat, t_compound_arr *ca, size_t *i)
{
	t_ast		*p;

	(*i)++;
	p = parse_ast(dat, ca, i);
	if (status_ok(dat) && !is_right_par(ca, *i))
		return (set_error(dat, PARSE_ERR_TREE, tok_to_str(LEFT_PARA)), NULL);
	(*i)++;
	return (p);
}

static t_ast	*parse_cmd(t_data *dat, t_compound_arr *ca, size_t *i)
{
	t_ast		*redirs;
	t_ast		*cmd;

	if (is_left_par(ca, *i))
		return (parse_parnthesis(dat, ca, i));
	redirs = parse_redir(dat, ca, i);
	if (is_cmd(ca, *i))
	{
		cmd = new_ast_node(&dat->ast, get_comp(ca, (*i)++));
		cmd->left = redirs;
		return (cmd);
	}
	else if (redirs)
		return (redirs);
	else if (*i < ca->len)
		return (set_error(dat, PARSE_ERR_TREE,
				tok_to_str(get_comp(ca, *i)->type)), NULL);
	return (NULL);
}

static t_ast	*parse_pipe(t_data *dat, t_compound_arr *ca, size_t *i)
{
	t_compound	*comp;
	t_ast		*left;
	t_ast		*new;

	left = parse_cmd(dat, ca, i);
	while (left && is_pipe(ca, *i))
	{
		comp = get_comp(ca, (*i)++);
		if (*i == ca->len)
			return (set_error(dat, PARSE_ERR_TREE,
					tok_to_str(comp->type)), NULL);
		new = new_ast_node(&dat->ast, comp);
		new->left = left;
		new->right = parse_cmd(dat, ca, i);
		if (!new->right)
			return (NULL);
		left = new;
	}
	return (left);
}

t_ast	*parse_ast(t_data *dat, t_compound_arr *ca, size_t *i)
{
	t_compound	*comp;
	t_ast		*left;
	t_ast		*new;

	left = parse_pipe(dat, ca, i);
	while (left && ((is_or(ca, *i)) || is_and(ca, *i)))
	{
		comp = get_comp(ca, (*i)++);
		if (*i == ca->len)
			return (set_error(dat, PARSE_ERR_TREE,
					tok_to_str(comp->type)), NULL);
		new = new_ast_node(&dat->ast, comp);
		new->left = left;
		new->right = parse_pipe(dat, ca, i);
		if (!new->right)
			return (NULL);
		left = new;
	}
	return (left);
}
