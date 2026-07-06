/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 13:00:27 by david             #+#    #+#             */
/*   Updated: 2026/07/06 13:29:43 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "structs.h"
# include <readline/readline.h>
# include <readline/history.h>

void	read_input(t_data *dat)
{
	dat->input = readline("minishell$ ");
	if (!dat->input)
		return ;
	add_history(dat->input);
}
