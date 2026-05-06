/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 21:34:36 by david             #+#    #+#             */
/*   Updated: 2026/05/06 21:56:06 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

static t_parse_err	*parser_err_handler(void)
{
	static t_parse_err	err;

	return (&err);
}

void	set_error(enum e_parse_err status, char c)
{
	t_parse_err	*err;

	err = parser_err_handler();
	err->status = status;
	err->c = c;
}

t_parse_err	*fetch_error(void)
{
	return (parser_err_handler());
}

int	print_error(void)
{
	t_parse_err	*err;

	err = fetch_error();
	if (err->status == PARSE_ERR_MALLOC)
	{
		ft_putstr_fd("Malloc fail", 2);
		return (1);
	}
	else
	{
		ft_putstr_fd("Parsing error, invalid char: ", 2);
		write(2, &err->c, 1);
		return (2);
	}
}
