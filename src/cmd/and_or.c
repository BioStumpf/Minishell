/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 12:00:52 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/27 12:36:09 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "structs.h"
#include "env.h"
#include "err.h"

int	exec_or(t_ast *node, t_pipe_manager *pipe_info)
{
	bool	inpipe;

	if (pipe_info->in_pipeline)
	{
		inpipe = true;
		pipe_info->in_pipeline = NO_PIPELINE;
	}
	else
		inpipe = false;
	assert(node->left != NULL && node->right != NULL);
	g_ret = execute(node->left, pipe_info);
	if (g_ret > 0)
		g_ret = execute(node->right, pipe_info);
	if (inpipe)
		cleanup_child(pipe_info->data, pipe_info);
	return (g_ret);
}

int	exec_and(t_ast *node, t_pipe_manager *pipe_info)
{
	bool	inpipe;

	if (pipe_info->in_pipeline)
	{
		inpipe = true;
		pipe_info->in_pipeline = NO_PIPELINE;
	}
	else
		inpipe = false;
	assert(node->left != NULL && node->right != NULL);
	g_ret = execute(node->left, pipe_info);
	if (g_ret == 0)
		g_ret = execute(node->right, pipe_info);
	if (inpipe)
		cleanup_child(pipe_info->data, pipe_info);
	return (g_ret);
}

