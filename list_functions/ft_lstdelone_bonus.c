/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 11:15:56 by dstumpf           #+#    #+#             */
<<<<<<<< HEAD:list_functions/ft_lstdelone_bonus.c
/*   Updated: 2026/04/23 09:17:03 by knajmech         ###   ########.fr       */
========
/*   Updated: 2025/11/26 15:28:51 by dstumpf          ###   ########.fr       */
>>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc:libft/ft_lstdelone.c
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

<<<<<<<< HEAD:list_functions/ft_lstdelone_bonus.c
void	ft_delnode(t_env_map *node, void (*del)(void *))
{
	if (!node || !del)
		return ;
	del(node->value);
========
void	ft_lstdelone(t_node *node, void (*del)(void *))
{
	if (!node || !del)
		return ;
	del(node->content);
>>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc:libft/ft_lstdelone.c
	free(node);
}
