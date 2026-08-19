/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_accessors_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 18:47:30 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 18:47:31 by dstumpf          ###   ########.fr       */
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
