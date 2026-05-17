/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 21:34:36 by david             #+#    #+#             */
/*   Updated: 2026/05/17 18:22:38 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "ft_printf.h"

static int	print_error_get_return(enum e_err err)
{
	if (err == ERR_MALLOC)
		return (ft_printf(2, "Malloc fail\n"), 1);
	else if (err == PARSE_ERR_UNCLOSED_QUOTES)
	 	return (ft_printf(2, "Parsing error, unclosed quotes\n"), 2);
	else
		return (0);
}

void	set_error(t_data *dat, enum e_err status)
{
	dat->err = status;
	dat->ret_code = print_error_get_return(dat->err);
}

bool	status_ok(t_data *dat)
{
	return (dat->err == OK);
}

bool	fatal_error(t_data *dat)
{
	return (dat->err == ERR_MALLOC);
}
