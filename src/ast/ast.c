/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 17:06:49 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/05 20:15:11 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "err.h"

// static bool	is_or(t_compound_arr *ca, size_t i)
// {
// 	return (i < ca->len && comp_type(get_comp(ca, i)) == OR);
// }
//
// static bool	is_and(t_compound_arr *ca, size_t i)
// {
// 	return (i < ca->len && comp_type(get_comp(ca, i)) == AND);
// }

// static bool	is_left_par(t_compound_arr *ca, size_t i)
// {
// 	return (i < ca->len && comp_type(get_comp(ca, i)) == LEFT_PARA);
// }
//
// static bool	is_right_par(t_compound_arr *ca, size_t i)
// {
// 	return (i < ca->len && comp_type(get_comp(ca, i)) == RIGHT_PARA);
// }

// static bool	is_pipe(t_compound_arr *ca, size_t i)
// {
// 	return (i < ca->len && comp_type(get_comp(ca, i)) == PIPE);
// }

// static bool	is_cmd(t_compound_arr *ca, size_t i)
// {
// 	return (i < ca->len && comp_type(get_comp(ca, i)) == CMD);
// }

// static bool	is_ast_redir(t_compound_arr *ca, size_t i)
// {
// 	return (i < ca->len && is_redir(comp_type(get_comp(ca, i))));
// }

// static t_ast	*parse_redir(t_data *dat, t_compound_arr *ca, size_t *i)
// {
// 	t_ast	*redir;
// 	t_ast	*tmp;
//
// 	if (!is_ast_redir(ca, *i))
// 		return (NULL);
// 	redir = new_ast_node(&dat->ast, get_comp(ca, (*i)++));
// 	tmp = redir;
// 	while (is_ast_redir(ca, *i))
// 	{
// 		tmp->left = new_ast_node(&dat->ast, get_comp(ca, (*i)++));
// 		tmp = tmp->left;
// 	}
// 	return (redir);
// }
//
// static t_ast	*last_redir(t_ast *node)
// {
// 	while (node && node->left)
// 		node = node->left;
// 	return (node);
// }

// static t_ast	*parse_ast(t_data *dat, t_compound_arr *ca, size_t *i);
// static t_ast	*parse_parnthesis(t_data *dat, t_compound_arr *ca, size_t *i)
// {
// 	t_ast		*p;
//
// 	(*i)++;
// 	p = parse_ast(dat, ca, i);
// 	if (status_ok(dat) && !is_right_par(ca, *i))
// 		return (set_error(dat, (enum e_err)LEFT_PARA), NULL);
// 	(*i)++;
// 	return (p);
// }
//
// static t_ast	*parse_cmd(t_data *dat, t_compound_arr *ca, size_t *i)
// {
// 	t_ast		*redirs;
// 	t_ast		*cmd;
//
// 	if (is_left_par(ca, *i))
// 		return (parse_parnthesis(dat, ca, i));
// 	redirs = parse_redir(dat, ca, i);
// 	if (is_cmd(ca, *i))
// 	{
// 		cmd = new_ast_node(&dat->ast, get_comp(ca, (*i)++));
// 		cmd->left = redirs;
// 		redirs = last_redir(cmd);
// 		redirs->left = parse_redir(dat, ca, i);
// 		return (cmd);
// 	}
// 	else if (redirs)
// 		return (redirs);
// 	else if (*i < ca->len)
// 		return (set_error(dat, (enum e_err)get_comp(ca, *i)->type), NULL);
// 	return (NULL);
// }
//
// static t_ast	*parse_pipe(t_data *dat, t_compound_arr *ca, size_t *i)
// {
// 	t_compound	*comp;
// 	t_ast		*left;
// 	t_ast		*new;
//
// 	left = parse_cmd(dat, ca, i);
// 	while (left && is_pipe(ca, *i))
// 	{
// 		comp = get_comp(ca, (*i)++);
// 		if (*i == ca->len)
// 			return (set_error(dat, (enum e_err)comp->type), NULL);
// 		new = new_ast_node(&dat->ast, comp);
// 		new->left = left;
// 		new->right = parse_cmd(dat, ca, i);
// 		if (!new->right)
// 			return (NULL);
// 		left = new;
// 	}
// 	return (left);
// }
//
// static t_ast	*parse_ast(t_data *dat, t_compound_arr *ca, size_t *i)
// {
// 	t_compound	*comp;
// 	t_ast		*left;
// 	t_ast		*new;
//
// 	left = parse_pipe(dat, ca, i);
// 	while (left && ((is_or(ca, *i)) || is_and(ca, *i)))
// 	{
// 		comp = get_comp(ca, (*i)++);
// 		if (*i == ca->len)
// 			return (set_error(dat, (enum e_err)comp->type), NULL);
// 		new = new_ast_node(&dat->ast, comp);
// 		new->left = left;
// 		new->right = parse_pipe(dat, ca, i);
// 		if (!new->right)
// 			return (NULL);
// 		left = new;
// 	}
// 	return (left);
// }

void	built_ast(t_data *dat, t_compound_arr *ca)
{
	size_t	i;

	i = 0;
	if (!ca || ca->len == 0)
		return ;
	dat->ast = ast_init(ca->len);
	if (!dat->ast.buf)
		return (set_error(dat, ERR_MALLOC));
	dat->ast.root = parse_ast(dat, ca, &i);
	if (status_ok(dat) && i != ca->len)
		set_error(dat, (enum e_err)get_comp(ca, i)->type);
	if (!status_ok(dat))
		dat->ast.root = NULL;
}
