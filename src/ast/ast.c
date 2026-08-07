/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 17:06:49 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/07 10:03:13 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "err.h"
#include "structs.h"

const char	*tok_to_str(enum e_token tok)
{
	if (tok == AND)
		return ("&&");
	if (tok == OR)
		return ("||");
	if (tok == PIPE)
		return ("|");
	if (tok == REDIR_INFILE)
		return ("<");
	if (tok == REDIR_OUTFILE)
		return (">");
	if (tok == REDIR_APPEND)
		return (">>");
	if (tok == REDIR_HEREDOC)
		return ("<<");
	if (tok == LEFT_PARA)
		return ("(");
	if (tok == RIGHT_PARA)
		return (")");
	else
		return ("<unknown token type>");
}

void	built_ast(t_data *dat, t_compound_arr *ca)
{
	size_t	i;

	i = 0;
	if (!ca || ca->len == 0 || !status_ok(dat))
		return ;
	dat->ast = ast_init(ca->len);
	if (!dat->ast.buf)
		return (set_error(dat, ERR_SYS, NULL));
	dat->ast.root = parse_ast(dat, ca, &i);
	if (status_ok(dat) && i != ca->len)
		set_error(dat, PARSE_ERR_TREE, tok_to_str(comp_type(arr_get(ca, i))));
	if (!status_ok(dat))
		dat->ast.root = NULL;
}
