/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 09:27:50 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/17 14:53:16 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "env.h"
#include "execution.h"
#include "err.h"
#include "ft_printf.h"

char	**heap_allocate_vars(char *arg1, char delimitter, char *arg2)
{
	char	**ptr;

	ptr = ft_calloc(3, sizeof(char *));
	if (!ptr)
		return (NULL);
	ptr[0] = ft_strndup(arg1, delimitter);
	if (!ptr[0])
		return (free(ptr), NULL);
	ptr[1] = ft_strdup(arg2);
	if (!ptr[1])
		return (free(ptr[0]), free(ptr), NULL);
	return (ptr);
}

bool	valid_check(char *argv)
{
	char	*string;
	int		i;

	string = argv;
	if (string == NULL)
		return (true);
	i = 0;
	if (ft_iswhitespace(string[i]) || string[i] == '=' || ft_isdigit(string[i]))
		return (g_ret = 1,
			ft_printf(2, "export: `%s': not a valid identifier\n", string),
			false);
	while (argv[i] && argv[i] != '=')
	{
		if (!ft_isalnum(argv[i]) && argv[i] != '_')
		{
			g_ret = 1;
			ft_printf(2, "export: `%s': not a valid identifier\n",
				string);
			return (false);
		}
		else
			i++;
	}
	return (true);
}

char	**get_vars(t_data *data, char *argv)
{
	int		i;
	char	**ptr;

	i = 0;
	while (argv && argv[i])
	{
		if (argv[i] == '=')
		{
			ptr = heap_allocate_vars(argv, '=', &argv[i + 1]);
			if (!ptr)
				return (set_error(data, ERR_SYS, NULL), NULL);
			return (ptr);
		}
		i++;
	}
	ptr = heap_allocate_vars(argv, '\0', "\0");
	if (!ptr)
		return (set_error(data, ERR_SYS, NULL), NULL);
	return (ptr);
}

void	export_var(t_data *data, char *argv)
{
	t_list	*env_arr;
	char	**list;

	if (!valid_check(argv))
		return ;
	env_arr = data->env_mp->env_ptr;
	if (data->env_mp->elem_num > 0 && argv)
	{
		list = get_vars(data, argv);
		if (!list)
			return ;
		if (ft_is_numeric(list[0]))
		{
			ft_printf(2, "export: `%s': not a valid identifier\n", list[0]);
			return (free(list[0]), free(list[1]));
		}
		if (ft_count_2d(list) <= 2 && ft_count_2d(list) >= 1)
			if (insert_new(env_arr, data->env_mp, list) == 0)
				set_error(data, ERR_SYS, NULL);
		free_out(list, ft_count_2d(list));
	}
	else
		print_var(env_arr, data->env_mp->capacity);
}

void	export_var_start(t_data *data, char **argv)
{
	int		i;

	i = 1;
	g_ret = 0;
	if (!argv[i])
		print_var(data->env_mp->env_ptr, data->env_mp->capacity);
	while (argv[i])
	{
		export_var(data, argv[i]);
		if (fatal_error(data))
			return ;
		i++;
	}
}
/*
void	export_var_start(t_data *data, char **argv)
{
	int		i;
	int		j;
	char	*string;
	char	delimitter;

	i = 1;
	if (!argv[i])
		print_var(data->env_mp->env_ptr, data->env_mp->capacity);
	while (argv[i])
	{
		j = 0;
		delimitter = 0;
		while (argv[i][j] && (argv[i][j] == '\'' ||
			argv[i][j] == '\"' || argv[i][j] == '`'))
			j++;
		if (j)
			delimitter = argv[i][j - 1];
		if (j == '`')
			delimitter = '\'';
		if (delimitter)
			string = ft_strndup(&argv[i][j], delimitter);
		else
			string = ft_strdup(&argv[i][j]);
		if (!string)
			return (set_error(data, ERR_SYS, NULL));
		export_var(data, string);
		free(string);
		i++;
	}
}*/
