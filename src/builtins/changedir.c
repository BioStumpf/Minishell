/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 10:00:28 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/27 16:30:53 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "builtins.h"
#include "env.h"
#include "err.h"
#include <stdio.h>

void	env_pwd_swap(t_data *data)
{
	t_env	*key_and_val;
	char	*k_v[2];

	key_and_val = hash_search(data->env_mp->env_ptr, "PWD");
	if (!key_and_val)
	{
		k_v[0] = "PWD";
		k_v[1] = getcwd(NULL, 0);
		if (!insert_new(data->env_mp->env_ptr, data->env_mp, k_v))
		{
			set_error(data, ERR_MALLOC);
			return ;
		}
		free(k_v[1]);
	}
	else
	{
		free(key_and_val->value);
		key_and_val->value = getcwd(NULL, 0);
		if (!key_and_val->value)
		{
			set_error(data, ERR_MALLOC);
			return ;
		}
	}
}

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
		{
			set_error(data, ERR_MALLOC);
			return ;
		}
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

	env_oldpwd_swap(data);
	if (ft_strchr(data->newdir, '/'))
	{
		chdir(data->newdir);
		data->cwd = data->newdir;
		env_pwd_swap(data);
		return (1);
	}
	curdir = ft_strjoin(data->cwd, "/");
	if (!curdir)
		return (set_error(data, ERR_MALLOC), 0);
	tmp = curdir;
	curdir = ft_strjoin(curdir, data->newdir);
	if (!curdir)
		return (free(tmp), set_error(data, ERR_MALLOC), 0);
	chdir(curdir);
	free(tmp);
	data->cwd = curdir;
	env_pwd_swap(data);
	return (1);
}
