/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 10:00:28 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/03 16:26:15 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "builtins.h"
#include "env.h"
#include "err.h"
#include "ft_printf.h"
#include <stdio.h>
#include <errno.h>

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

int	set_pwdenv(t_data *data)
{
	char	*currdir;
	char	*k_v[2];

	currdir = getcwd(NULL, 0);
	if (currdir == NULL)
		return (0);
	k_v[0] = "PWD";
	k_v[1] = currdir;
	if (insert_new(data->env_mp->env_ptr, data->env_mp, k_v) == 0)
		return (free(currdir), 0);
	free(currdir);
	return (1);
}

int	change_dir_swap(t_data *data)
{
	char	*oldpwd_var;

	if (get_env_val(data, "OLDPWD") == NULL)
		return (ft_printf(2, "Minishell: cd: OLDPWD not set\n"), 0);
	if (get_env_val(data, "PWD") == NULL)
		if (set_pwdenv(data) == 0)
			return (set_error(data, ERR_MALLOC), 0);
	oldpwd_var = ft_strdup(get_env_val(data, "OLDPWD"));
	if (!oldpwd_var)
		return (set_error(data, ERR_MALLOC), 0);
	if (chdir(oldpwd_var) == -1)
	{
		if (errno == EACCES)
			ft_printf(2, "Minishell: cd: %s: Permission denied\n",
					data->newdir);
		else if (errno == ENOTDIR)
			ft_printf(2, "Minishell: cd: %s: Not a directory\n", data->newdir);
		else
			ft_printf(2, "Minishell: cd: %s: No such file or directory\n",
					data->newdir);
		g_ret = 1;
		return (free(oldpwd_var), 0);
	}
	ft_printf(1, "%s\n", oldpwd_var);
	env_val_swap(data, "PWD", "OLDPWD");
	return (free(oldpwd_var), 1);
}

int	change_to_home(t_data *data)
{
	t_env	*home_val;

	if (!data->newdir || !ft_strncmp(data->newdir, "~/", 3) ||
			!ft_strncmp(data->newdir, "~", 2))
	{
		home_val = hash_search(data->env_mp->env_ptr, "HOME");
		if (!home_val || !home_val->value)
		{
			ft_printf(2, "Minishell: cd: HOME not set\n");
			return (g_ret = 1, g_ret);
		}
		else
			data->newdir = home_val->value;
	}
	return (g_ret);
}

int	change_dir(t_data *data)
{
	if (change_to_home(data) == 1)
		return (g_ret);
	if (!ft_strncmp(data->newdir, "-", 2))
		return (change_dir_swap(data), g_ret);
	env_oldpwd_swap(data);
	if (chdir(data->newdir) == -1)
	{
		if (errno == EACCES)
			ft_printf(2, "Minishell: cd: %s: Permission denied\n", data->newdir);
		else if (errno == ENOTDIR)
			ft_printf(2, "Minishell: cd: %s: Not a directory\n", data->newdir);
		else
			ft_printf(2, "Minishell: cd: %s: No such file or directory\n", data->newdir);
		g_ret = 1;
	}
	env_pwd_swap(data);
	return (g_ret);
}

/*
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



int	change_dir(t_data *data)
{
	t_env	*home_val;

	if (!data->newdir || !ft_strncmp(data->newdir, "~/", 3) ||
			!ft_strncmp(data->newdir, "~", 2))
	{
		home_val = hash_search(data->env_mp->env_ptr, "HOME");
		if (!home_val || !home_val->value)
		{
			ft_printf(2, "Minishell: cd: HOME not set\n");
			return (0);
		}
		else
			data->newdir = home_val->value;
	}
	if (!ft_strncmp(data->newdir, "-", 2))
	{
		change_dir_swap(data);
		env_pwd_swap(data);
		return (1);
	}
	env_oldpwd_swap(data);
	if (chdir(data->newdir) == -1)
	{
		if (errno == EACCES)
			return (ft_printf(2, "Minishell: cd: %s: Permission denied\n", data->newdir));
		ft_printf(2, "Minishell: cd: %s: No such file or directory\n", data->newdir);
		g_ret = 1;
	}
	env_pwd_swap(data);
	return (1);
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
}*/
