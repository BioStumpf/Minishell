/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 07:52:24 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/12 09:57:17 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "main.h"
# include <unistd.h>

# define ECHO 0
# define CD 1
# define PWD 2
# define EXPORT 3
# define UNSET 4
# define ENV 5
# define EXIT 6

int		which_builtin(t_data *built_in, int builtin_call);
int		echo_print(t_data *data, int flag);
int		change_dir(t_data *data);
int		pworkdir(t_data *data);
void	export_var(t_data *data);
void	unset_var(t_list *map_env, char *key);
void	env_var(t_data *data);
void	exit_minishell(t_data *data);

#endif
