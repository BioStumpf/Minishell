/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_accessors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 19:26:03 by dstumpf           #+#    #+#             */
/*   Updated: 2026/06/04 20:00:06 by dstumpf          ###   ########.fr       */
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
