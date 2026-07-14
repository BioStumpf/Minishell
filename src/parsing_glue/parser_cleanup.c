/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:57:40 by david             #+#    #+#             */
/*   Updated: 2026/06/05 10:54:24 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "err.h"
#include "structs.h"

void	free_token(void *token)
{
	if (((t_token *)token)->type == WORD)
		free(((t_token *)token)->u_value.s_word.word);
	else if (is_redir(((t_token *)token)->type))
		free(((t_token *)token)->u_value.s_redir.filename);
	free(token);
}

void	free_compound(t_compound_arr *ca, enum e_err status, t_data *dat)
{
	size_t		i;
	t_compound	*comp;

	i = 0;
	if (ca && ca->arr)
	{
		while (i < ca->len)
		{
			comp = arr_get(ca, i);
			if (comp_type(comp) == CMD)
				free_args(comp_args(comp));
			else if (is_redir(comp_type(comp)))
				free(comp_filename(comp));
			i++;
		}
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
