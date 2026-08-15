/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 07:24:21 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/05 14:04:57 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include "parsing.h"
#include "err.h"
#include "execution.h"

void	after_execve_exit(t_pipe_manager *pipe_info, t_ast *node)
{
	errno = check_path(pipe_info->pathwcmd);
	perror_messaging(NULL, get_av(node)[0]);
	set_global_status();
	pipe_info->data->err = ERR_SYS;
	cleanup_child(pipe_info->data, pipe_info);
}

char	*check_access(t_pipe_manager *pipe_info, char *ptc, char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		pipe_info->pathwcmd = ft_strdup(cmd);
		if (pipe_info->pathwcmd == NULL)
			return (set_error(pipe_info->data, ERR_SYS, NULL), NULL);
		return (pipe_info->pathwcmd);
	}
	else
		pipe_info->pathwcmd = ft_strjoin(ptc, cmd);
	if (!pipe_info->pathwcmd)
		return (set_error(pipe_info->data, ERR_SYS, NULL), NULL);
	if (!access(pipe_info->pathwcmd, F_OK))
	{
		pipe_info->cmd_found = 1;
		if (!access(pipe_info->pathwcmd, X_OK))
			return (pipe_info->pathwcmd);
	}
	free(pipe_info->pathwcmd);
	pipe_info->pathwcmd = NULL;
	return (NULL);
}

char	*path_fixer(char *path_to_fix)
{
	char	*fixed_path;

	fixed_path = 0;
	if (path_to_fix[ft_strlen(path_to_fix) - 1] == '/')
		fixed_path = ft_strdup(path_to_fix);
	else if (path_to_fix[ft_strlen(path_to_fix) - 1] != '/')
		fixed_path = ft_strjoin(path_to_fix, "/");
	if (!fixed_path)
		return (NULL);
	return (fixed_path);
}

char	**fill_curr_dir(t_data *data)
{
	char	**path_parts;

	path_parts = ft_calloc(2, sizeof(char *));
	if (!path_parts)
		return (set_error(data, ERR_SYS, NULL), NULL);
	path_parts[0] = ft_strdup("./");
	path_parts[1] = '\0';
	if (!path_parts[0])
		return (set_error(data, ERR_SYS, NULL), free(path_parts), NULL);
	return (path_parts);
}

void	pathfinder(t_pipe_manager *pipe_info, char **path_parts)
{
	int		i;
	char	*path_to_check;

	if (!ft_strncmp(get_av(pipe_info->cmd_node)[0], "", 1))
		return ;
	if (ft_strchr(get_av(pipe_info->cmd_node)[0], '/'))
		return (check_access(pipe_info, NULL,
				get_av(pipe_info->cmd_node)[0]), (void)0);
	if (!path_parts)
		return ;
	i = 0;
	while (path_parts[i])
	{
		path_to_check = path_fixer(path_parts[i]);
		if (!path_to_check)
			return (set_error(pipe_info->data, ERR_SYS, NULL),
				perror("malloc"));
		assert(path_to_check);
		if (check_access(pipe_info, path_to_check,
				get_av(pipe_info->cmd_node)[0]))
			return (free(path_to_check));
		free(path_to_check);
		i++;
	}
}
