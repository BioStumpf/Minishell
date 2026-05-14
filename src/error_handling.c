/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 21:34:36 by david             #+#    #+#             */
/*   Updated: 2026/05/13 18:27:26 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

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
	{
		ft_putstr_fd("Malloc fail\n", 2);
		return (1);
	}
	else if (err->status == PARSE_ERR_INVALID_CHAR)
	{
		ft_putstr_fd("Parsing error, invalid char: ", 2);
		write(2, &err->c, 1);
		write(2, "\n", 1);
		return (2);
	}
	else if (err->status == OK)
		return (0);
	// else if (err->status == PARSE_ERR_UNCLOSED_QUOTES)
	else
	{
		ft_putstr_fd("Parsing error, unclose quotes: ", 2);
		return (2);
	}
}

enum e_err	evaluate_state(void)
{
	return (fetch_error()->status);
}
