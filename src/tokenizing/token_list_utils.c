/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 18:46:24 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 18:46:25 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "stdlib.h"
#include "structs.h"

static t_token	*token_new(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = NONE;
	ft_bzero(token, sizeof(t_token));
	return (token);
}

t_node	*new_token_node(void)
{
	t_token	*token;
	t_node	*node;

	token = token_new();
	if (!token)
		return (NULL);
	node = ft_nodenew(token);
	if (!node)
		return (free(token), NULL);
	return (node);
}
