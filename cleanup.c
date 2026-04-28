/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 07:31:26 by knajmech          #+#    #+#             */
/*   Updated: 2026/04/27 10:34:15 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <errno.h>
#include <stdio.h>

void	error_and_cleanup(t_data *data, char *error_desc)
{
	(void)data->env_mp;
	perror(error_desc);
}
