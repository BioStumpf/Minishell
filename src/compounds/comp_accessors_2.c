/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_accessors_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 09:56:33 by david             #+#    #+#             */
/*   Updated: 2026/08/08 10:04:21 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	comp_open_fd(t_compound *comp)
{
	return (comp->u_value.s_redir.open_fd);
}

void	comp_set_filename(t_compound *comp, char *filename)
{
	comp->u_value.s_redir.filename = filename;
}

void	comp_set_expand(t_compound *comp, bool expand)
{
	comp->u_value.s_redir.expand = expand;
}

bool	comp_expand(t_compound *comp)
{
	return (comp->u_value.s_redir.expand);
}

void	comp_set_open_fd(t_compound *comp, int fd)
{
	comp->u_value.s_redir.open_fd = fd;
}
