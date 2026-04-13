/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 09:07:15 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/05 12:50:41 by knajmech         ###   ########.fr       */
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

void	exec_pipe(t_ast *node, t_pipe_manager *pipe_info);
void	exec_and(t_ast *node, t_pipe_manager *pipe_info);
void	exec_or(t_ast *node, t_pipe_manager *pipe_info);
void	execute(t_ast *node, t_pipe_manager *pipe_info);
// void	heredoc(t_data *data, t_ast *node);
void	redirect_builtin(t_data *data, t_ast *redir, char **cmd);
void	redirect_extern(t_data *data, t_ast *redir);
char	**free_out(char **out, size_t len);
void	pathfinder(t_pipe_manager *pipe_info, char **path_parts);
char	**split_path_env(t_data *data);
void	exec_builtin(t_ast *node, t_pipe_manager *pipe_info);
void	exec_extern(t_ast *node, t_pipe_manager *pipe_info);
void	coordinate_exec(t_data *data);
void	extern_child_wrapper(t_ast *node, t_pipe_manager *pipe_info);

#endif
