/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 09:05:59 by david             #+#    #+#             */
/*   Updated: 2026/08/09 09:11:20 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "err.h"
#include "parsing.h"

void	heredoc(t_data *dat, t_compound_arr *ca)
{
	size_t		i;
	t_compound	*comp;

	if (!ca || !status_ok(dat))
		return ;
	i = 0;
	while (i < ca->len)
	{
		comp = get_comp(ca, i);
		if (comp_type(comp) == REDIR_HEREDOC)
			prompt_heredoc(dat, comp);
		++i;
	}
}
