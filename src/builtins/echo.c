/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 09:33:31 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/03 11:01:29 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_printf.h"

static bool	is_newline_flag(char *str)
{
	if (*str && *str != '-')
		return (false);
	while (*++str)
	{
		if (*str != 'n')
			return (false);
	}
	return (true);
}

int	echo_print(char **string_arg)
{
	int	i;
	int	newline_flag;

	assert(string_arg != NULL && *string_arg != NULL);
	i = 1;
	newline_flag = 1;
	if (string_arg[1] != NULL && is_newline_flag(string_arg[i]))
	{
		i++;
		newline_flag = 0;
	}
	while (string_arg[i])
	{
		printf("%s", string_arg[i]);
		i++;
		if (string_arg[i])
			printf("%s", " ");
	}
	if (newline_flag == 1)
		ft_printf(1, "\n");
	return (0);
}
