/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 21:20:41 by dstumpf           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/11/05 15:31:45 by dstumpf          ###   ########.fr       */
=======
/*   Updated: 2026/05/14 19:16:46 by david            ###   ########.fr       */
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdbool.h>

typedef unsigned int	t_uint;
typedef unsigned long	t_ulong;

const char	*find_option(const char *str);
int			print_arg(va_list args, const char *arg);
int			ft_putchar(const char c);
int			ft_putstr(const char *str);
int			ft_putnbr_base(t_ulong num, t_uint base_len, char base_id);
int			ft_putnbr_signed(int num);
int			print_pointer(t_ulong num);
<<<<<<< HEAD
int			ft_printf(const char *str, ...);
=======
int			ft_printf(int fd, const char *str, ...);
int			gfd(void);
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc

#endif
