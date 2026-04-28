/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 08:18:08 by knajmech          #+#    #+#             */
/*   Updated: 2026/04/28 10:45:03 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <errno.h>
//# include "minishell.h"
# include "libft/libft.h"

typedef struct s_env_map
{
	char				*key;
	char				*value;

	struct s_env_map	*next;
} t_env_map;

typedef struct s_env_tracker
{
	int					capacity;
	int					elem_num;

	struct s_env_map	**env_ptr;
} t_env_tracker;

typedef struct s_data
{
	t_env_map **env_mp;
}	t_data;

t_env_map	*ft_newnode(void *value);
void		error_and_cleanup(t_data *data, char *error_str);

#endif
