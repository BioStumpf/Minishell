/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_compound_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:24:02 by david             #+#    #+#             */
/*   Updated: 2026/06/04 15:36:03 by dstumpf          ###   ########.fr       */
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
	char	*new_arg;
	void	*dest;
	void	*src;

	if (!args->av && !init_args(args))
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
	new_arg = ft_strdup(arg);
	if (!new_arg)
		return (free_args(args), NULL);
	ft_memmove(dest, src, to_move * sizeof(char *));
	args->av[idx] = new_arg; 
	args->size++;
	return (args);
}
