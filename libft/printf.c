/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 21:23:29 by dstumpf           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/11/05 11:08:50 by dstumpf          ###   ########.fr       */
=======
/*   Updated: 2026/05/14 19:25:31 by david            ###   ########.fr       */
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static bool	add_printed(int printed_bytes, int *tot_bytes)
{
	if (printed_bytes == -1)
	{
		*tot_bytes = -1;
		return (false);
	}
	*tot_bytes += printed_bytes;
	return (true);
}

<<<<<<< HEAD
int	ft_printf(const char *str, ...)
=======
static int	*get_fd(void)
{
	static int	fd;

	return (&fd);
}

static void	init_fd(int val)
{
	*get_fd() = val;
}

int	gfd(void)
{
	 return (*get_fd());
}

int	ft_printf(int fd, const char *str, ...)
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc
{
	va_list		args;
	const char	*cursor;
	int			tot_bytes;
	int			printed_bytes;

	if (!str)
		return (-1);
<<<<<<< HEAD
=======
	init_fd(fd);
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc
	va_start(args, str);
	tot_bytes = 0;
	while (*str)
	{
		cursor = find_option(str);
<<<<<<< HEAD
		printed_bytes = write(1, str, cursor - str);
=======
		printed_bytes = write(gfd(), str, cursor - str);
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc
		if (!add_printed(printed_bytes, &tot_bytes) || !*cursor)
			break ;
		printed_bytes = print_arg(args, cursor + 1);
		if (!add_printed(printed_bytes, &tot_bytes))
			break ;
		str = cursor + 2;
	}
	va_end(args);
	return (tot_bytes);
}
