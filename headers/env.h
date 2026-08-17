/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 08:18:08 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/17 14:33:55 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <assert.h>
# include "structs.h"
# include "libft.h"
# define CAPACITY 67

void	print_var(t_list *env_arr, int capacity);
int				set_pwdenv(t_data *data);
void			print_expolist(t_node *env_list);
void			delete_envnode(t_env *env);
int				process_env(t_data *data, char **env);
void			unset_variable(t_env_tracker *env, t_list *map_env, char *key);
t_env			*make_kv_node(char *key, char *val);
t_env			*ft_newnode(void *value);
t_env			*hash_search(t_list *hash_arr, char *key);
unsigned int	find_hash_key(char	*key);
char			*get_env_val(t_data *data, char *key);
int				insert_new(t_list *env_ptr, t_env_tracker *tracker,
					char **new_variable);
t_node			*delete_node(t_node *node);
char			**env_ptrptr(t_data *data, t_list *env_list, char **env);
void			env_val_swap(t_data *data, char *env1, char *env2);

#endif
