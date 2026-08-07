/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 09:55:27 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/07 09:48:28 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "structs.h"
#include "err.h"
#include <errno.h>

static bool	valid_exit_code(char *str)
{
	if (*str == '-' || *str == '+')
		++str;
	while (*str)
	{
		if (!ft_isdigit(*str++))
			return (false);
	}
	return (true);
}

void	exit_minishell(t_data *data, char **av)
{
	int	ret;

	set_error(data, EXIT_CALL, NULL);
	if (av[0] && av[1] && av[2])
		return (ft_printf(2, "exit: too many arguments\n"),
			data->ret = 2, (void)0);
	else if (av[0] && av[1])
	{
		errno = 0;
		ret = ft_atol(av[1]) % 256;
		if (!valid_exit_code(av[1]) || errno == ERANGE)
			return (ft_printf(2, "exit: %s numeric argument required\n",
					av[1]), data->ret = 2, (void)0);
		return (data->ret = ret, (void)0);
	}
}
