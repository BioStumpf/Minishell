/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 09:33:31 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/17 12:39:08 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "err.h"

static bool	is_newline_flag(char *str)
{
	if (*str == '\0' || !ft_strncmp(str, "-", 2))
		return (false);
	if (*str && *str != '-')
		return (false);
	while (*++str)
	{
		if (*str != 'n')
			return (false);
	}
	return (true);
}

void	echo_print(char **string_arg)
{
	int	i;
	int	newline_flag;

	i = 1;
	newline_flag = 1;
	while (string_arg[i] != NULL && is_newline_flag(string_arg[i]))
	{
		i++;
		newline_flag = 0;
	}
	while (string_arg[i])
	{
		ft_printf(1, "%s", string_arg[i]);
		i++;
		if (string_arg[i])
			ft_printf(1, "%s", " ");
	}
	if (newline_flag == 1)
		ft_printf(1, "\n");
	g_ret = 0;
}
