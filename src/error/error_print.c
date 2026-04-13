/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 14:18:47 by david             #+#    #+#             */
/*   Updated: 2026/08/12 14:18:47 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	perror_messaging(char *command, char *arg)
{
	if (arg && command)
		ft_printf(2, "Minishell: %s: %s: ", command, arg);
	else if (!arg && command)
		ft_printf(2, "Minishell: %s: ", command);
	else if (arg && !command)
		ft_printf(2, "%s: ", arg);
	perror(NULL);
}
