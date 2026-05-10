/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 09:46:59 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/10 09:49:16 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/structs.h"

t_node	*delete_node(t_node *node)
{
	t_env	*env;
	t_node	*node_next;

	node_next = node->next;
	env = node->content;
	free(env->key);
	free(env->value);
	free((t_env *) node->content);
	free(node);
	return (node_next);
}

