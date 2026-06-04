/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 09:07:15 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/04 10:59:18 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define NO_PIPELINE 0
# define IN_PIPELINE 1
# define LEFT 1
# define RIGHT 0

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include "structs.h"
// # include "builtins.h"

void	redirections(t_data *data, t_ast *redir, char **cmd);
char	**free_out(char **out, size_t len);
void	pathfinder(t_pipe_manager *pipe_info, char **path_parts, char **args);
char	**split_path_env(t_data *data);

#endif
