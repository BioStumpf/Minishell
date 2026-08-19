/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 11:12:07 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/06 12:03:44 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "err.h"
#include <stdio.h>
#include "ft_printf.h"

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
