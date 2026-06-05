/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 07:24:21 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/04 11:48:26 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "structs.h"

char	*check_access(t_pipe_manager *pipe_info, char *ptc, char *cmd)
{
	char	*full_path;

	if (ft_strchr(cmd, '/') && !(access(cmd, X_OK)))
	{
		pipe_info->pathwcmd = ft_strdup(cmd);
		if (!pipe_info->pathwcmd)
			error_and_cleanup(pipe_info->data, "malloc", 0);
		return (pipe_info->pathwcmd);
	}
	else
	{
		full_path = ft_strjoin(ptc, cmd);
		if (!full_path)
			error_and_cleanup(pipe_info->data, "malloc", 0);
		if (!access(full_path, F_OK) || !access(cmd, F_OK))
		{
			pipe_info->cmd_found = 1;
			if (!access(full_path, X_OK))
				return (pipe_info->pathwcmd);
		}
	}
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

void	pathfinder(t_pipe_manager *pipe_info, char **path_parts, char **args)
{
	int		i;
	char	*path_to_check;

	i = 0;
	while (path_parts[i])
	{
		path_to_check = path_fixer(path_parts[i]);
		if (!path_to_check)
			error_and_cleanup(pipe_info->data, "malloc", 0);
		if (check_access(pipe_info, path_to_check, args[0]))
			return ;
		free(path_to_check);
		i++;
	}
}

