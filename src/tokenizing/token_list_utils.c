/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 16:54:01 by david             #+#    #+#             */
/*   Updated: 2026/07/06 10:54:33 by david            ###   ########.fr       */
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
