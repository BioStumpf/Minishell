/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 07:24:21 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/04 14:39:08 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "structs.h"
#include "parsing.h"
#include "err.h"

char	*check_access(t_pipe_manager *pipe_info, char *ptc, char *cmd)
{
	if (ft_strchr(cmd, '/'))
		pipe_info->pathwcmd = ft_strdup(cmd);
	else
		pipe_info->pathwcmd = ft_strjoin(ptc, cmd);
	if (!pipe_info->pathwcmd)
		return (set_error(pipe_info->data, ERR_MALLOC), NULL);
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

int	pathfinder(t_pipe_manager *pipe_info, char **path_parts)
{
	int		i;
	char	*path_to_check;

	if (!path_parts)
		return (0);
	i = 0;
	while (path_parts[i])
	{
		path_to_check = path_fixer(path_parts[i]);
		if (!path_to_check)
			return (set_error(pipe_info->data, ERR_MALLOC), -1);
		assert(path_to_check);
		if (check_access(pipe_info, path_to_check,
				get_av(pipe_info->cmd_node)[0]))
			return (1);
		free(path_to_check);
		i++;
	}
	return (0);
}
