/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 13:52:42 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/07 09:21:30 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libft/libft.h"
/*typedef struct s_env_map
{
	char				*key;
	char				*value;

	struct s_env_map	*next;
} t_env_map;*/

typedef struct s_env_tracker
{
	int					capacity;
	int					elem_num;

	t_list	*env_ptr;
} 				t_env_tracker;

typedef struct s_env
{
	char *key;
	char *value;
}			t_env;

typedef struct s_data
{
//	t_ast	*ast;
//	t_envp	*envp;
	char			*input;
	char			**new_variable;
	t_env_tracker	*env_mp;
}			t_data;

#endif
