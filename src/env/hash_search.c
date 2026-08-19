/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 10:03:18 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/17 17:45:49 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_printf.h"

void	print_expolist(t_node *env_list)
{
	t_env	*node;

	while (env_list)
	{
		node = env_list->content;
		if (node->value && ft_strncmp(node->key, "_", 2))
			ft_printf(1, "declare -x %s=\"%s\"\n", node->key, node->value);
		else
			ft_printf(1, "declare -x %s\n", node->key);
		env_list = env_list->next;
	}
}

unsigned int	find_hash_key(char	*key)
{
	unsigned int	hash;
	unsigned int	key_index;
	unsigned int	i;
	unsigned int	key_len;

	hash = 5381;
	key_len = ft_strlen_char(key, '=');
	i = 0;
	while (i < key_len)
	{
		hash = hash * 31 + key[i];
		i++;
	}
	key_index = hash % CAPACITY;
	return (key_index);
}

void	env_val_swap(t_data *data, char *env1, char *env2)
{
	char	*holder;
	t_env	*node1;
	t_env	*node2;

	node1 = hash_search(data->env_mp->env_ptr, env1);
	node2 = hash_search(data->env_mp->env_ptr, env2);
	if (!node1 || !node2)
		return ;
	holder = node1->value;
	node1->value = node2->value;
	node2->value = holder;
}

t_env	*hash_search(t_list *hash_arr, char *key)
{
	t_env			*key_check;
	t_node			*list;
	unsigned int	hash_key;

	if (!hash_arr)
		return (NULL);
	hash_key = find_hash_key(key);
	list = hash_arr[hash_key].head;
	while (list)
	{
		key_check = list->content;
		if (!ft_strncmp(key_check->key, key, ft_strlen(key) + 1))
			return (key_check);
		else
			list = list->next;
	}
	return (NULL);
}

char	*get_env_val(t_data *data, char *key)
{
	t_env	*key_and_val;

	key_and_val = hash_search(data->env_mp->env_ptr, key);
	if (!key_and_val)
		return (NULL);
	return (key_and_val->value);
}
