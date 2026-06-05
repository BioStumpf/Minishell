/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 10:00:28 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/04 12:02:51 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "builtins.h"
#include "env.h"

int	change_dir(t_data *data)
{
	char	*curdir;
	char	*tmp;

	if (ft_strchr(data->newdir, '/'))
	{
		chdir(data->newdir);
		free(data->cwd);
		data->cwd = data->newdir;
		return (1);
	}
	curdir = ft_strjoin(data->cwd, "/");
	if (!curdir)
		error_and_cleanup(data, "malloc", 0);
	tmp = curdir;
	curdir = ft_strjoin(curdir, data->newdir);
	if (!curdir)
		error_and_cleanup(data, "malloc", 0);
	free(tmp);
	chdir(curdir);
	data->cwd = curdir;
	return (1);
}
