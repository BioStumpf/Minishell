/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_arg_accessors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 19:26:03 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/28 11:16:53 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	comp_heredoc(t_compound *comp)
{
	return (comp->u_value.s_redir.open_fd);
}

size_t	arg_size(t_compound *comp)
{
	return (comp->u_value.args.size);
}

size_t	arg_capacity(t_compound *comp)
{
	return (comp->u_value.args.capacity);
}

char	**arg_av(t_compound *comp)
{
	return (comp->u_value.args.av);
}
