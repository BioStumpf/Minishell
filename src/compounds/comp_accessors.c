/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_accessors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 18:47:32 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 18:47:33 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

enum e_token	comp_type(t_compound *comp)
{
	return (comp->type);
}

int	comp_fd(t_compound *comp)
{
	return (comp->u_value.s_redir.fd);
}

char	*comp_filename(t_compound *comp)
{
	return (comp->u_value.s_redir.filename);
}

t_arg	*comp_args(t_compound *comp)
{
	return (&comp->u_value.args);
}

t_compound	*get_comp(t_compound_arr *ca, size_t i)
{
	return (&ca->arr[i]);
}
