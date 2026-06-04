/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:57:40 by david             #+#    #+#             */
/*   Updated: 2026/06/04 16:12:24 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "err.h"

void	free_token(void *token)
{
	free(((t_token *)token)->word);
	free(token);
}

void	free_compound(t_compound_arr *ca, enum e_err status, t_data *dat)
{
	size_t	i;

	i = 0;
	if (ca && ca->arr)
	{
		while (i < ca->len)
			free_args(&ca->arr[i++].args);
	}
	if (ca)
		free(ca->arr);
	free(ca);
	if (status != OK)
		set_error(dat, status);
}

void	token_cleanup(t_list *lst, enum e_err status, t_data *dat, t_node *n)
{
	ft_lstdelone(n, free_token);
	ft_lstclear(lst, free_token);
	if (status != OK)
		set_error(dat, status);
}
