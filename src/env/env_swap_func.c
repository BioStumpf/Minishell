/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_swap_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 08:25:50 by knajmech          #+#    #+#             */
/*   Updated: 2026/08/04 08:29:48 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "env.h"
#include "err.h"

int	set_pwdenv(t_data *data)
{
	char	*currdir;
	char	*k_v[2];

	currdir = getcwd(NULL, 0);
	if (currdir == NULL)
		return (0);
	k_v[0] = "PWD";
	k_v[1] = currdir;
	if (insert_new(data->env_mp->env_ptr, data->env_mp, k_v) == 0)
		return (free(currdir), g_ret = 1, 0);
	free(currdir);
	return (1);
}
