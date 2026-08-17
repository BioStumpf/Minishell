/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:17:19 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/17 12:38:00 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "structs.h"
#include "execution.h"
#include "err.h"
#include "builtins.h"

void	execute(t_ast *node, t_pipe_manager *pipe_info)
{
	if (fatal_error(pipe_info->data))
		cleanup_child(pipe_info->data, pipe_info);
	expand(pipe_info->data, node);
	if (fatal_error(pipe_info->data))
		cleanup_child(pipe_info->data, pipe_info);
	if (node->type == AND)
		exec_and(node, pipe_info);
	else if (node->type == OR)
		exec_or(node, pipe_info);
	else if (node->type == PIPE)
		exec_pipe(node, pipe_info);
	else if (node->type == CMD && is_builtin(get_av(node)[0]) > -1)
		exec_builtin(node, pipe_info);
	else if (node->type == CMD && get_av(node)[0])
	{
		pipe_info->cmd_found = 0;
		pipe_info->cmd_node = node;
		exec_extern(node->left, pipe_info);
		if (fatal_error(pipe_info->data))
			return ;
	}
	else
		redirect_builtin(pipe_info->data, node, NULL);
}

void	coordinate_exec(t_data *data)
{
	t_ast			*node;
	t_pipe_manager	pipe_info;

	if (data->ast.root == NULL)
		return ;
	pipe_info.data = data;
	pipe_info.in_pipeline = NO_PIPELINE;
	pipe_info.child[0] = 0;
	pipe_info.child[1] = 0;
	pipe_info.pathwcmd = NULL;
	data->pipe_info = &pipe_info;
	node = data->ast.root;
	execute(node, &pipe_info);
}
