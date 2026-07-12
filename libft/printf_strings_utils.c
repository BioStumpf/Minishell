/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD
/*   strings_utils.c                                    :+:      :+:    :+:   */
=======
/*   printf_strings_utils.c                             :+:      :+:    :+:   */
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 21:22:31 by dstumpf           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/11/03 16:45:47 by dstumpf          ###   ########.fr       */
=======
/*   Updated: 2026/05/14 19:21:49 by david            ###   ########.fr       */
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(const char c)
{
<<<<<<< HEAD
	return (write(1, &c, 1));
=======
	return (write(gfd(), &c, 1));
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc
}

int	ft_putstr(const char *str)
{
	int	i;

	if (!str)
<<<<<<< HEAD
		return (write(1, "(null)", 6));
	i = 0;
	while (str[i])
		i++;
	return (write(1, str, i));
=======
		return (write(gfd(), "(null)", 6));
	i = 0;
	while (str[i])
		i++;
	return (write(gfd(), str, i));
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc
}
