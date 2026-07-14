/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 13:40:23 by david             #+#    #+#             */
/*   Updated: 2026/06/15 18:19:39 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_numeric(char *input)
{
	while (*input)
	{
		if (!ft_isdigit(*input))
			return (false);
		input++;
	}
	return (true);
}
