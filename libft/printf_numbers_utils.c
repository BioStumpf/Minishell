/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD
/*   numbers_utils.c                                    :+:      :+:    :+:   */
=======
/*   printf_numbers_utils.c                             :+:      :+:    :+:   */
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 21:21:46 by dstumpf           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/11/05 15:11:59 by dstumpf          ###   ########.fr       */
=======
/*   Updated: 2026/05/14 19:21:19 by david            ###   ########.fr       */
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	putnbr_rec(t_ulong num, const char *base, t_uint base_len)
{
	int	digits;

	if (base_len > num)
<<<<<<< HEAD
		return (write(1, &base[num], 1));
	digits = putnbr_rec(num / base_len, base, base_len);
	if (digits == -1)
		return (-1);
	if (write(1, &base[num % base_len], 1) == -1)
=======
		return (write(gfd(), &base[num], 1));
	digits = putnbr_rec(num / base_len, base, base_len);
	if (digits == -1)
		return (-1);
	if (write(gfd(), &base[num % base_len], 1) == -1)
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc
		return (-1);
	return (digits + 1);
}

int	ft_putnbr_base(t_ulong num, t_uint base_len, char base_id)
{
	const char	*base;

	if (base_id == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	return (putnbr_rec(num, base, base_len));
}

int	ft_putnbr_signed(int num)
{
	if (num < 0)
	{
<<<<<<< HEAD
		if (write(1, "-", 1) == -1)
=======
		if (write(gfd(), "-", 1) == -1)
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc
			return (-1);
		return (ft_putnbr_base((t_ulong)(-(long)num), 10, 'i') + 1);
	}
	else
		return (ft_putnbr_base((t_ulong)num, 10, 'i'));
}

int	print_pointer(t_ulong num)
{
	if (!num)
<<<<<<< HEAD
		return (write(1, "(nil)", 5));
	if (write(1, "0x", 2) == -1)
=======
		return (write(gfd(), "(nil)", 5));
	if (write(gfd(), "0x", 2) == -1)
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc
		return (-1);
	return (ft_putnbr_base(num, 16, 'x') + 2);
}
