/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_accessors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:28:19 by dstumpf           #+#    #+#             */
/*   Updated: 2026/06/28 19:52:34 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	exp_quote(t_exp_vec *vec, size_t idx)
{
	return (vec->expansions[idx].quoted);
}

size_t	exp_start(t_exp_vec *vec, size_t idx)
{
	return (vec->expansions[idx].start);
}

size_t	exp_len(t_exp_vec *vec, size_t idx)
{
	return (vec->expansions[idx].len);
}
