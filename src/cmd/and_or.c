/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 12:00:52 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/12 12:05:38 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "structs.h"
#include "env.h"

int	exec_or(t_ast *node, t_pipe_manager *pipe_info)
{
	int	status;

	assert(node->left != NULL && node->right != NULL);
	pipe_info->in_pipeline = NO_PIPELINE;
	status = execute(node->left, pipe_info);
	if (status > 0)
		status = execute(node->right, pipe_info);
	if (pipe_info->in_pipeline)
		error_and_cleanup(pipe_info->data, NULL, status);
	return (status);
}

int	exec_and(t_ast *node, t_pipe_manager *pipe_info)
{
	int	status;

	assert(node->left != NULL && node->right != NULL);
	pipe_info->in_pipeline = NO_PIPELINE;
	status = execute(node->left, pipe_info);
	if (status == 0)
		status = execute(node->right, pipe_info);
	if (pipe_info->in_pipeline)
		error_and_cleanup(pipe_info->data, NULL, status);
	return (status);
}

