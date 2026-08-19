/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 18:45:58 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 18:45:59 by dstumpf          ###   ########.fr       */
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
	while (i < ca->len && g_ret != 128 + SIGINT)
	{
		comp = get_comp(ca, i);
		if (comp_type(comp) == REDIR_HEREDOC)
			prompt_heredoc(dat, comp);
		++i;
	}
}
