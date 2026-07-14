/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 10:00:28 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/14 14:33:41 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "builtins.h"
#include "env.h"
#include <stdio.h>

void	env_oldpwd_swap(t_data *data)
{
	t_env	*key_and_val;
	char	*k_v[2];

	key_and_val = hash_search(data->env_mp->env_ptr, "OLDPWD");
	if (!key_and_val)
	{
		k_v[0] = "OLDPWD";
		k_v[1] = data->cwd;
		if (!insert_new(data->env_mp->env_ptr, data->env_mp, k_v))
			error_and_cleanup(data, "malloc", 0);
	}
	else
	{
		free(key_and_val->value);
		key_and_val->value = data->cwd;
	}
}

int	change_dir(t_data *data)
{
	char	*curdir;
	char	*tmp;

	data->newdir = data->;
	printf("%s\n", data->newdir);
	env_oldpwd_swap(data);
	if (ft_strchr(data->newdir, '/'))
	{
		chdir(data->newdir);
		data->cwd = data->newdir;
		data->newdir = NULL;
		return (1);
	}
	curdir = ft_strjoin(data->cwd, "/");
	if (!curdir)
		error_and_cleanup(data, "malloc", 0);
	tmp = curdir;
	curdir = ft_strjoin(curdir, data->newdir);
	if (!curdir)
		error_and_cleanup(data, "malloc", 0);
	chdir(curdir);
	free(tmp);
	data->cwd = curdir;
	return (1);
}
