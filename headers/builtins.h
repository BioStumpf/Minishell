/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 07:52:24 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/17 15:07:05 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include "structs.h"

void	export_var_start(t_data *data, char **cmd_argv);
int		is_builtin(char *cmd);
void	which_builtin(t_data *built_in, char **cmd_argv, int builtin_call);
void	echo_print(char **echo_string);
void	change_dir(t_data *data);
void	pworkdir(t_data *dat);
void	export_var(t_data *data, char **argv);
void	unset_var(t_env_tracker *env, t_list *map_env, char *key);
void	env_var(t_data *data);
void	exit_minishell(t_data *data, char **av);
void	execute_builtin(t_ast *node, bool in_pipeline, t_data *data);

#endif
