/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 21:34:36 by david             #+#    #+#             */
/*   Updated: 2026/05/14 19:34:47 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "ft_printf.h"

t_err	*fetch_error(void)
{
	static t_err	err;

	return (&err);
}

void	set_error(enum e_err status, char c)
{
	t_err	*err;

	err = fetch_error();
	err->status = status;
	err->c = c;
}

int	get_and_print_error(void)
{
	t_err	*err;

	err = fetch_error();
	if (err->status == ERR_MALLOC)
		return (ft_printf(2, "Malloc fail\n"), 1);
	else if (err->status == PARSE_ERR_INVALID_CHAR)
	 	return (ft_printf(2, "Parsing error, invalid char: %c\n", err->c), 2);
	else if (err->status == PARSE_ERR_UNCLOSED_QUOTES)
	 	return (ft_printf(2, "Parsing error, unclosed quotes\n"), 2);
	else
		return (0);
}

enum e_err	evaluate_state(void)
{
	return (fetch_error()->status);
}
