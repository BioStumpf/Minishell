/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 17:06:49 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/05 12:42:24 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "err.h"

void	built_ast(t_data *dat, t_compound_arr *ca)
{
	size_t	i;

	i = 0;
	if (!ca || ca->len == 0 || !status_ok(dat))
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
