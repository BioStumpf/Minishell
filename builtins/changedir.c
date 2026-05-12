/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 10:00:28 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/11 11:26:26 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/builtins.h"

int	change_dir(t_data *data)
{
	char	*curdir;
	char	*tmp;

	curdir = ft_strjoin(data->cwd, "/");
	if (!curdir)
		error_and_cleanup(data, "malloc");
	tmp = curdir;
	curdir = ft_strjoin(curdir, data->newdir);
	if (!curdir)
		error_and_cleanup(data, "malloc");
	free(tmp);
	chdir(curdir);
	data->cwd = curdir;
	return (1);
}
