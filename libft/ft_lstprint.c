/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:39:50 by dstumpf           #+#    #+#             */
/*   Updated: 2025/11/28 17:39:54 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *lst, void (*print_fn)(void *content))
{
	t_node	*cursor;

<<<<<<< HEAD
=======
	if (!lst)
		return ;
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc
	cursor = lst->head;
	while (cursor)
	{
		print_fn(cursor->content);
		cursor = cursor->next;
	}
}
