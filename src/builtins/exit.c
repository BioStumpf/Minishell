/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 09:55:27 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/04 12:00:40 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "env.h"
void	exit_minishell(t_data *data)
{
	error_and_cleanup(data, NULL, 0);
}
