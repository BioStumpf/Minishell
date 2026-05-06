/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 08:18:08 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/06 12:29:54 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <assert.h>
# include <errno.h>
# include "headers/main.h"
//# include "minishell.h"
# include "libft/libft.h"

# define CAPACITY 67

typedef struct s_env
{
	char *key;
	char *value;
}		t_env;

/*typedef struct s_env_map
{
	char				*key;
	char				*value;

	struct s_env_map	*next;
} t_env_map;*/

typedef struct s_env_tracker
nt					capacity;
	int					elem_num;

	t_list	*env_ptr;
} 				t_env_tracker;

/*typedef struct s_data
{
	t_list *env_mp;
}				t_data;*/

t_env	*make_kv_node(char *key, char *val);
t_env	*ft_newnode(void *value);
t_env	*hash_search(t_node *list, char *key);
void	error_and_cleanup(t_data *data, char *error_str);
int		insert_new(t_list *env_ptr, t_env_tracker *tracker, char **new_variable);

#endif
