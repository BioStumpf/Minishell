/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 13:52:42 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/11 11:23:03 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libft/libft.h"

typedef enum e_builtin
{
	echo,
	cd,
	pwd,
	expo,
	unset,
	env,
	exit_shell
}			t_builtin;

typedef struct s_env_tracker
{
	int					capacity;
	int					elem_num;
	t_list				*env_ptr;
}						t_env_tracker;

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

typedef struct s_data
{
	char			*input;
	char			**new_variable;
	char			*find_var;
	char			*cwd;
	char			*newdir;
	t_env_tracker	*env_mp;
}			t_data;

#endif
