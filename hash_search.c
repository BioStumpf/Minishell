/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 10:03:18 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/05 16:46:22 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*hash_search(t_node *list, char *key)
{
	t_env	*key_check;

	if (!list)
		return (NULL);
	while (list)
	{
		key_check = list->content;
		if (!ft_strncmp(key_check->key, key, ft_strlen(key) + 1))
			return (key_check);
		else
			list = list->next;
	}
	return (NULL);
}
