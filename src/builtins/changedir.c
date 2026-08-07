/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 10:00:28 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/07 09:47:57 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "env.h"
#include "err.h"
#include "ft_printf.h"
#include <stdio.h>
#include <errno.h>

void	env_oldpwd_swap(t_data *data, char *new_oldpwd)
{
	t_env	*key_and_val;
	char	*k_v[2];

	key_and_val = hash_search(data->env_mp->env_ptr, "OLDPWD");
	if (!key_and_val)
	{
		k_v[0] = "OLDPWD";
		k_v[1] = new_oldpwd;
		if (!insert_new(data->env_mp->env_ptr, data->env_mp, k_v))
		{
			set_error(data, ERR_SYS, NULL);
			free(k_v[1]);
		}
		return ;
	}
	free(key_and_val->value);
	key_and_val->value = ft_strdup(new_oldpwd);
	if (!key_and_val->value)
	{
		set_error(data, ERR_SYS, NULL);
		return ;
	}
}

int	env_pwd_swap(t_data *data)
{
	t_env	*key_and_val;
	char	*k_v[2];

	key_and_val = hash_search(data->env_mp->env_ptr, "PWD");
	if (!key_and_val)
	{
		k_v[0] = "PWD";
		k_v[1] = getcwd(NULL, 0);
		if (!k_v[1])
			return (set_error(data, ERR_SYS, NULL), 1);
		if (!insert_new(data->env_mp->env_ptr, data->env_mp, k_v))
			return (free(k_v[1]), set_error(data, ERR_SYS, NULL), 1);
		free(k_v[1]);
	}
	else
	{
		free(key_and_val->value);
		key_and_val->value = getcwd(NULL, 0);
		if (!key_and_val->value)
			return (set_error(data, ERR_SYS, NULL), 1);
	}
	return (0);
}

static void	change_dir_swap(t_data *data)
{
	char	*oldpwd_var;

	if (get_env_val(data, "OLDPWD") == NULL)
		return (ft_printf(2, "Minishell: cd: OLDPWD not set\n"), (void)0);
	if (get_env_val(data, "PWD") == NULL)
		if (set_pwdenv(data) == 0)
			return (set_error(data, ERR_SYS, NULL));
	oldpwd_var = get_env_val(data, "OLDPWD");
	if (chdir(oldpwd_var) == -1)
	{
		perror("cd");
		if (errno == EACCES)
			ft_printf(2, "Minishell: cd: %s: Permission denied\n",
				data->newdir);
		else if (errno == ENOTDIR)
			ft_printf(2, "Minishell: cd: %s: Not a directory\n", data->newdir);
		else
			ft_printf(2, "Minishell: cd: %s: No such file or directory\n",
				data->newdir);
		g_ret = 1;
		return ;
	}
	ft_printf(1, "%s\n", oldpwd_var);
	return (env_val_swap(data, "PWD", "OLDPWD"));
}

static bool	change_to_home(t_data *data)
{
	t_env	*home_val;

	if (!data->newdir || !ft_strncmp(data->newdir, "~/", 3)
		|| !ft_strncmp(data->newdir, "~", 2))
	{
		home_val = hash_search(data->env_mp->env_ptr, "HOME");
		if (!home_val || !home_val->value)
		{
			ft_printf(2, "Minishell: cd: HOME not set\n");
			g_ret = 1;
			return (false);
		}
		data->newdir = home_val->value;
	}
	return (true);
}

void	change_dir(t_data *data)
{
	char	*current_pwd;

	if (!change_to_home(data))
		return ;
	if (!ft_strncmp(data->newdir, "-", 2))
		return (change_dir_swap(data));
	current_pwd = ft_strdup("dummy");
	if (chdir(data->newdir) == -1)
	{
		perror("cd");
		return (g_ret = 1, free(current_pwd));
	}
	free(current_pwd);
}
//this is the old one, just wanted clean norm
// void	change_dir(t_data *data)
// {
// 	char	*current_pwd;
//
// 	if (!change_to_home(data))
// 		return ;
// 	if (!ft_strncmp(data->newdir, "-", 2))
// 		return (change_dir_swap(data));
// 	current_pwd = ft_strdup("dummy");
// 	//current_pwd = getcwd(NULL, 0);
// 	//if (!current_pwd)
// 	//	return (set_error(data, ERR_MALLOC), 1);
// 	if (chdir(data->newdir) == -1)
// 	{
// 		perror("cd");
// 		/*if (errno == EACCES)
// 			ft_printf(2, "Minishell: cd: %s: Permission denied\n",
//					data->newdir);
// 		else if (errno == ENOTDIR)
// 			ft_printf(2, "Minishell: cd: %s: Not a directory\n",
//					data->newdir);
// 		else
// 			ft_printf(2, "Minishell: cd: %s: No such file or directory\n",
//					data->newdir);*/
// 		return (g_ret = 1, free(current_pwd));
// 	}
// 	//env_oldpwd_swap(data, current_pwd);
// 	free(current_pwd);
// 	//env_pwd_swap(data);
// }
