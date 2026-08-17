/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 17:06:49 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/17 19:32:57 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "err.h"
#include "structs.h"

const char	*tok_to_str(t_compound *comp)
{
	if (comp_type(comp) == AND)
		return ("&&");
	if (comp_type(comp) == OR)
		return ("||");
	if (comp_type(comp) == PIPE)
		return ("|");
	if (comp_type(comp) == REDIR_INFILE)
		return ("<");
	if (comp_type(comp) == REDIR_OUTFILE)
		return (">");
	if (comp_type(comp) == REDIR_APPEND)
		return (">>");
	if (comp_type(comp) == REDIR_HEREDOC)
		return ("<<");
	if (comp_type(comp) == LEFT_PARA)
		return ("(");
	if (comp_type(comp) == RIGHT_PARA)
		return (")");
	if (comp_type(comp) == CMD)
		return (comp_args(comp)->av[0]);
	else
		return ("<unknown token type>");
}

void	built_ast(t_data *dat, t_compound_arr *ca)
{
	size_t	i;

	i = 0;
	if (!ca || ca->len == 0 || !status_ok(dat) || g_ret == 128 + SIGINT)
		return ;
	dat->ast = ast_init(ca->len);
	if (!dat->ast.buf)
		return (set_error(dat, ERR_SYS, NULL));
	dat->ast.root = parse_ast(dat, ca, &i);
	if (status_ok(dat) && i != ca->len)
		set_error(dat, PARSE_ERR_TREE, tok_to_str(arr_get(ca, i)));
	if (!status_ok(dat))
		dat->ast.root = NULL;
}
