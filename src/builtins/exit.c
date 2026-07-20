/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 09:55:27 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/20 16:47:57 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "env.h"
#include "err.h"
#include "parsing.h"

void	exit_minishell(t_data *data)
{
	cleanup(data);
	free(data->cwd);
	//clean_ast(&data->ast);
	set_error(data, EXIT_CALL);
	return ;
	//error_and_cleanup(data, NULL, 0);
}
