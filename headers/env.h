/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 08:18:08 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/07 10:18:40 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <assert.h>
# include <errno.h>
# include "main.h"
# include "structs.h"
//# include "minishell.h"
# include "../libft/libft.h"

# define CAPACITY 67

t_env	*make_kv_node(char *key, char *val);
t_env	*ft_newnode(void *value);
t_env	*hash_search(t_node *list, char *key);
void	error_and_cleanup(t_data *data, char *error_str);
int		insert_new(t_list *env_ptr, t_env_tracker *tracker, char **new_variable);
t_node	*delete_node(t_node *node);

#endif
