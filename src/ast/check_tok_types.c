/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tok_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 20:08:12 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/05 20:08:48 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_or(t_compound_arr *ca, size_t i)
{
	return (i < ca->len && comp_type(get_comp(ca, i)) == OR);
}

bool	is_and(t_compound_arr *ca, size_t i)
{
	return (i < ca->len && comp_type(get_comp(ca, i)) == AND);
}

bool	is_pipe(t_compound_arr *ca, size_t i)
{
	return (i < ca->len && comp_type(get_comp(ca, i)) == PIPE);
}
