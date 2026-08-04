/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pworkdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 08:47:22 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/04 15:21:45 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "err.h"
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
	printf("%s\n", currdir);
	free(currdir);
}
