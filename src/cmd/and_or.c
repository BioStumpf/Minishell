/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 12:00:52 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/03 16:28:21 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "structs.h"
#include "err.h"
#include "parsing.h"

void	exec_or(t_ast *node, t_pipe_manager *pipe_info)
{
	bool	inpipe;

	if (pipe_info->in_pipeline)
	{
		inpipe = true;
		pipe_info->in_pipeline = NO_PIPELINE;
	}
	else
		inpipe = false;
	execute(node->left, pipe_info);
	if (g_ret != 0)
		execute(node->right, pipe_info);
	if (inpipe)
	{
		close_heredocs(pipe_info->data);
		cleanup_child(pipe_info->data, pipe_info);
	}
}

void	exec_and(t_ast *node, t_pipe_manager *pipe_info)
{
	bool	inpipe;

	if (pipe_info->in_pipeline)
	{
		inpipe = true;
		pipe_info->in_pipeline = NO_PIPELINE;
	}
	else
		inpipe = false;
	execute(node->left, pipe_info);
	if (g_ret == 0)
		execute(node->right, pipe_info);
	if (inpipe)
	{
		close_heredocs(pipe_info->data);
		cleanup_child(pipe_info->data, pipe_info);
	}
}
