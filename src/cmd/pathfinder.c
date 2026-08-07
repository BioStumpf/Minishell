/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:52:36 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/05 12:18:15 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include "env.h"
#include "err.h"

char	**free_out(char **out, size_t len)
{
	while (len)
		free(out[--len]);
	free(out);
	out = NULL;
	return (NULL);
}

static char	**mallocing(char *s, char **list, int *i, int *k)
{
	while (s[*i])
	{
		if (s[*i] == ':' && (s[*i + 1] == ':' || s[*i + 1] == '\0'))
		{
			list[*k] = ft_strdup("./");
			*i += 1;
			*k += 1;
		}
		else if (s[*i] != ':' && s[*i + 1] != ':')
		{
			list[*k] = ft_substr(s, *i, ft_strlen_char(&s[*i], ':'));
			*k += 1;
			while (s[*i] && s[*i] != ':')
				(*i)++;
		}
		else
			(*i)++;
		if (!list[*k - 1])
			return (free_out(list, *k - 1));
	}
	list[*k] = 0;
	return (list);
}

char	**split_the_path(char *entire_path)
{
	int	count_paths;
	int	i;

	i = 0;
	count_paths = 0;
	if (*entire_path == ':')
		count_paths++;
	while (entire_path[i])
	{
		if (entire_path[i] != ':')
		{
			count_paths++;
			while (entire_path[i] && entire_path[i] != ':')
				i++;
		}
		else
			i++;
	}
	if (i > 0 && entire_path[i - 1] == ':')
		count_paths++;
	return (malloc((count_paths + 1) * sizeof(char *)));
}

char	**protection_and_initialisation(t_data *data, t_list *hash_arr)
{
	t_env	*key_and_val;
	char	**path_parts;

	key_and_val = hash_search(hash_arr, "PATH");
	if (key_and_val == NULL || key_and_val->value == NULL)
		return (0);
	path_parts = split_the_path(key_and_val->value);
	if (!path_parts)
		return (set_error(data, ERR_SYS, NULL), NULL);
	return (path_parts);
}

char	**split_path_env(t_data *data)
{
	t_env	*key_and_val;
	char	**path_parts;
	int		i;
	int		k;

	path_parts = protection_and_initialisation(data, data->env_mp->env_ptr);
	if (path_parts == NULL)
		return (NULL);
	i = 0;
	k = 0;
	key_and_val = hash_search(data->env_mp->env_ptr, "PATH");
	if (key_and_val->value[0] == ':')
	{
		i = ft_strlen_char(key_and_val->value, ':');
		path_parts[0] = ft_substr(key_and_val->value, 0, i);
		if (!path_parts[0])
			return (set_error(data, ERR_SYS, NULL), NULL);
		k++;
	}
	path_parts = mallocing(key_and_val->value, path_parts, &i, &k);
	if (path_parts == NULL)
		return (set_error(data, ERR_SYS, NULL), NULL);
	return (path_parts);
}
