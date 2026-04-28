/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newnode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:04:02 by dstumpf           #+#    #+#             */
/*   Updated: 2026/04/28 10:33:20 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env.h"

t_env_map	*ft_newnode(void *content)
{
	t_env_map	*new;

	new = malloc(sizeof(t_env_map));
	if (!new)
		return (NULL);
	new->value = content;
	new->next = NULL;
	return (new);
}
