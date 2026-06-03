/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 07:52:24 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/01 11:03:11 by knajmech         ###   ########.fr       */
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

int		is_builtin(char *cmd);
int		which_builtin(t_data *built_in, char **cmd_argv, int builtin_call);
int		echo_print(char **echo_string);
int		change_dir(t_data *data);
int		pworkdir(t_data *data);
void	export_var(t_data *data);
void	unset_var(t_list *map_env, char *key);
void	env_var(t_data *data);
void	exit_minishell(t_data *data);
int		execute_builtin(t_ast *node, bool in_pipeline, t_data *data);

#endif
