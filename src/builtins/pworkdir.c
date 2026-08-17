/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pworkdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 08:47:22 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/17 15:46:02 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "err.h"
#include "ft_printf.h"
#include "structs.h"
#include <stdio.h> 
#include <error.h> 
#include <errno.h> 

void	pworkdir(t_data *data)
{
	char	*currdir;

	errno = 0;
	currdir = getcwd(NULL, 0);
	if (currdir == NULL && (errno == ENOENT || errno == EACCES))
	{
		perror(NULL);
		g_ret = 1;
		return ;
	}
	else if (!currdir && errno != 0)
		set_error(data, ERR_SYS, NULL);
	ft_printf(1, "%s\n", currdir);
	free(currdir);
	g_ret = 0;
}
