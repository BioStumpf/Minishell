/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 10:00:28 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/31 08:32:35 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "builtins.h"
#include "env.h"
#include "err.h"
#include "ft_printf.h"
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
		if (!k_v[1])
		{
			set_error(data, ERR_MALLOC);
			return ;
		}
		if (!insert_new(data->env_mp->env_ptr, data->env_mp, k_v))
		{
			set_error(data, ERR_MALLOC);
			free(k_v[1]);
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
		k_v[1] = getcwd(NULL, 0);
		if (!k_v[1])
		{
			set_error(data, ERR_MALLOC);
			return ;
		}
		if (!insert_new(data->env_mp->env_ptr, data->env_mp, k_v))
		{
			set_error(data, ERR_MALLOC);
			free(k_v[1]);
			return ;
		}
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

int	change_dir(t_data *data)
{
	t_env	*home_val;

	if (!data->newdir || !ft_strncmp(data->newdir, "~/", 3) ||
			!ft_strncmp(data->newdir, "~", 2))
	{
		home_val = hash_search(data->env_mp->env_ptr, "HOME");
		if (!home_val || !home_val->value)
		{
			ft_printf(2, "Minishell: cd: %s: HOME not set\n", data->newdir);
			return (0);
		}
		else
			data->newdir = home_val->value;
	}
	env_oldpwd_swap(data);
	if (chdir(data->newdir) == -1)
		ft_printf(2, "Minishell: cd: %s: No such file or directory\n", data->newdir);
	env_pwd_swap(data);
	return (1);
}

/*
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
}*/
