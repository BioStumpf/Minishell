/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pworkdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 08:47:22 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/11 09:22:11 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/env.h"

int	pworkdir(t_data *data)
{
	char	*currdir;

	currdir = getcwd(NULL, 0);
	if (currdir == NULL)
		error_and_cleanup(data, "getcwd");
	printf("%s\n", currdir);
	free(currdir);
	return (1);
}
