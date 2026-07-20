/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:17:19 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/20 10:22:30 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "structs.h"
#include "execution.h"
#include "builtins.h"

int	execute(t_ast *node, t_pipe_manager *pipe_info)
{
	if (node->type == AND)
		return (exec_and(node, pipe_info));
	else if (node->type == OR)
		return (exec_or(node, pipe_info));
	else if (node->type == PIPE)
		return (exec_pipe(node, pipe_info));
	else if (node->type == CMD && is_builtin(get_av(node)[0]) > -1)
		return (exec_builtin(node, pipe_info));
	else if (node->type == CMD)
	{
		pipe_info->pathwcmd = NULL;
		pipe_info->data->pipe_info = pipe_info;
		pipe_info->cmd_node = node;
		redirect_extern(pipe_info->data, node->left, node);
	}
	else
		return (0);
	return (2);
}

void	coordinate_exec(t_data *data)
{
	t_ast			*node;
	t_pipe_manager	pipe_info;

	assert(data->ast.root != NULL);
	pipe_info.data = data;
	pipe_info.in_pipeline = NO_PIPELINE;
	pipe_info.child[0] = 0;
	pipe_info.child[1] = 0;
	node = data->ast.root;
	execute(node, &pipe_info);
}
