/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 09:33:31 by knajmech          #+#    #+#             */
/*   Updated: 2026/07/15 14:09:43 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	echo_print(char **string_arg)
{
	int	i;
	int	newline_flag;

	assert(string_arg != NULL && *string_arg != NULL);
	i = 1;
	newline_flag = 1;
	if (string_arg[1] == NULL)
		newline_flag = 0;
	if (string_arg[1] != NULL && !ft_strncmp(string_arg[1], "-n", 3))
	{
		i++;
		newline_flag = 1;
	}
	while (string_arg[i])
	{
		if (string_arg[i] != NULL)
			printf("%s ", string_arg[i]);
		i++;
	}
	if (newline_flag == 1)
		printf("\n");
	return (0);
}
