/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 09:27:50 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/04 15:06:46 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "env.h"
#include "execution.h"
#include "err.h"
#include "ft_printf.h"

void	print_var(t_list *env_arr, int capacity)
{
	int	i;

	i = 0;
	while (i < capacity)
	{
		if (env_arr[i].head)
			print_expolist(env_arr[i].head);
		i++;
	}
}

bool	valid_check(char *argv)
{
	char	*string;
	int		i;

	string = argv;
	if (string == NULL)
		return (true);
	i = 0;
	if (ft_iswhitespace(string[i]) || (string[i] == '='))
	{
		g_ret = 1;
		ft_printf(2, "minishell: export: '%s': not a valid identifier\n",
			string);
		return (false);
	}
	return (true);
}

char	**get_vars(t_data *data, char *argv)
{
	int		i;
	char	**ptr;

	i = 0;
	ptr = ft_calloc(3, sizeof(char *));
	if (!ptr)
		return (set_error(data, ERR_MALLOC), NULL);
	while (argv && argv[i])
	{
		if (argv[i] == '=')
		{
			ptr[0] = ft_strndup(argv, '=');
			ptr[1] = ft_strdup(&argv[i + 1]);
			if (!ptr[0] || !ptr[1])
				return (free(ptr[0]), free(ptr), set_error(data, ERR_MALLOC),
					NULL);
			return (ptr);
		}
		i++;
	}
	ptr[0] = ft_strdup(argv);
	ptr[1] = ft_strdup("\0");
	if (!ptr[0] || !ptr[1])
		return (free(ptr[0]), free(ptr), set_error(data, ERR_MALLOC), NULL);
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
		if (ft_count_2d(list) <= 2 && ft_count_2d(list) >= 1)
			if (insert_new(env_arr, data->env_mp, list) == 0)
				set_error(data, ERR_MALLOC);
		free_out(list, ft_count_2d(list));
	}
	else
		print_var(env_arr, data->env_mp->capacity);
}

void	export_var_start(t_data *data, char **argv)
{
	int	i;

	i = 1;
	if (!argv[i])
		print_var(data->env_mp->env_ptr, data->env_mp->capacity);
	while (argv[i])
	{
		export_var(data, argv[i]);
		i++;
	}
}
