/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 11:12:07 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/04 11:47:02 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "err.h"
#include <errno.h>
#include "ft_printf.h"

void	error_print(t_data *data, char *command, char *arg)
{
	if (errno == EACCES)
		ft_printf(2, "minishell: %s: %s: Permission denied\n", command, arg);
	else if (errno == ENOTDIR)
		ft_printf(2, "minishell: %s %s: Not a directory\n", command, arg);
	else if (errno == EFAULT)
		ft_printf(2, "minishell: %s %s: Not a directory\n", command, arg);
	else if (errno == ENOTDIR)
		ft_printf(2, "minishell: %s %s: Not a directory\n", command, arg);
	else if (errno == ENOTDIR)
		ft_printf(2, "minishell: %s %s: Not a directory\n", command, arg);
	else if (errno == ENOTDIR)
		ft_printf(2, "minishell: %s %s: Not a directory\n", command, arg);
}
