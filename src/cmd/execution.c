/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:17:19 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/03 16:38:07 by dstumpf          ###   ########.fr       */
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
		return (pipe_info->pathwcmd = NULL, exec_extern(node, pipe_info));
	else
		return (0);
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
