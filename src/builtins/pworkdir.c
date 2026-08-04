/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pworkdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 08:47:22 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/05 08:31:20 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "err.h"
#include "ft_printf.h"
#include <stdio.h> 
#include <error.h> 
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

void	pworkdir(void)
{
	char	*currdir;

	currdir = getcwd(NULL, 0);
	if (currdir == NULL)
	{
		perror(NULL);
		g_ret = 1;
	}
	ft_printf(1, "%s\n", currdir);
	free(currdir);
}
