/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 10:55:51 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 18:43:11 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

# include <stdbool.h>
# include "structs.h"
# include <signal.h>

extern volatile sig_atomic_t	g_ret;

//error handling
void	clean_extern_helper(t_pipe_manager *pipe_info, char ***env, char ***pb);
int		check_path(char *cmd);
void	perror_messaging(char *command, char *arg);
void	set_error(t_data *dat, enum e_err status, const char *str);
void	set_global_status(void);
bool	status_ok(t_data *dat);
bool	fatal_error(t_data *dat);
t_data	*data_storage(t_data *data);
void	cleanup_normal(t_data *data);
void	cleanup_child(t_data *data, t_pipe_manager *pipe_info);
void	close_fds(int *fd_arr, int amount);
#endif
