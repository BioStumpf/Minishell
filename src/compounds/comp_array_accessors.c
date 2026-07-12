/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_array_accessors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 19:26:03 by dstumpf           #+#    #+#             */
/*   Updated: 2026/06/04 21:19:43 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	arr_len(t_compound_arr *comps)
{
	return (comps->len);
}

t_compound	*arr_get(t_compound_arr *comps, size_t idx)
{
	return (&comps->arr[idx]);
}
