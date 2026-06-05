/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 09:33:31 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/04 12:01:59 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	echo_print(char **string_arg)
{
	int	i;
	int	newline_flag;

	assert(string_arg != NULL);
	i = 1;
	newline_flag = 1;
	if (!ft_strncmp(string_arg[1], "-n", 3))
	{
		i++;
		newline_flag = 0;
	}
	while (string_arg[i])
	{
		printf("%s ", string_arg[i]);
		i++;
	}
	if (newline_flag == 1)
		printf("\n");
	return (0);
}
