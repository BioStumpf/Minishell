/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_compound_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:24:02 by david             #+#    #+#             */
/*   Updated: 2026/05/27 15:51:07 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <stdlib.h>

bool	init_args(t_arg *args)
{
	args->size = 0;
	args->capacity = 5;
	args->av = malloc(sizeof(char *) * 5);
	if (!args->av)
		return (false);
	return (true);
}

void	free_args(t_arg *args)
{
	size_t	i;

	i = 0;
	while (i < args->size)
	{
		free(args->av[i]);
		i++;
	}
	free(args->av);
}

static void	*grow_arr(t_arg *args)
{
	char	*new_buff;

	new_buff = malloc(args->capacity * sizeof(char *));
	if (!new_buff)
		return (free_args(args), NULL);
	ft_memcpy(new_buff, args->av, args->size * sizeof(char *));
	free(args->av);
	return (new_buff);
}

void	*add_arg(t_arg *args, size_t idx, char *arg)
{
	size_t	to_move;
	void	*dest;
	void	*src;

	if (idx > args->size)
		return (NULL);
	if (args->size >= args->capacity)
	{
		args->capacity *= 2;
		args->av = grow_arr(args);
	}
	if (!args->av)
		return (NULL);
	to_move = args->size - idx;
	dest = &args->av[idx + 1];
	src = &args->av[idx];
	ft_memmove(dest, src, to_move * sizeof(char *));
	args->av[idx] = ft_strdup(arg);
	if (!args->av[idx])
		return (free_args(args), NULL);
	args->size++;
	return (args);
}
