/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tok_types2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 20:08:12 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/05 20:11:50 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_left_par(t_compound_arr *ca, size_t i)
{
	return (i < ca->len && comp_type(get_comp(ca, i)) == LEFT_PARA);
}

bool	is_right_par(t_compound_arr *ca, size_t i)
{
	return (i < ca->len && comp_type(get_comp(ca, i)) == RIGHT_PARA);
}

bool	is_cmd(t_compound_arr *ca, size_t i)
{
	return (i < ca->len && comp_type(get_comp(ca, i)) == CMD);
}

bool	is_ast_redir(t_compound_arr *ca, size_t i)
{
	return (i < ca->len && is_redir(comp_type(get_comp(ca, i))));
}
