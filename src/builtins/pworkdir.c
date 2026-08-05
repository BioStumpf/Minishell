/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pworkdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 08:47:22 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/04 16:00:46 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "structs.h"
#include "env.h"
#include "err.h"
#include "ft_printf.h"

/*
void	save_cwd(t_data *data)
{
	char	*currdir;

	currdir = getcwd(NULL, 0);
	if (currdir == NULL)
	{
		set_error(data, ERR_MALLOC);
		return ;
	}
	data->cwd = currdir;
}*/

int	pworkdir(t_data *data)
{
	char	*currdir;

	currdir = getcwd(NULL, 0);
	if (currdir == NULL)
	{
		set_error(data, ERR_MALLOC);
		return (0);
	}
	ft_printf(1, "%s\n", currdir);
	free(currdir);
	return (1);
}
