/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 11:15:56 by dstumpf           #+#    #+#             */
/*   Updated: 2026/04/23 09:17:03 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	ft_delnode(t_env_map *node, void (*del)(void *))
{
	if (!node || !del)
		return ;
	del(node->value);
	free(node);
}
