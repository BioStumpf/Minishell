/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 09:33:31 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/11 09:36:14 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/builtins.h"

int	echo_print(t_data *data, int n_flag)
{
	assert(data->input != NULL);
	printf("%s", data->input);
	if (n_flag != 0)
		printf("\n");
	return (0);
}
