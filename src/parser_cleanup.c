/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <user@student.42mail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:57:40 by david             #+#    #+#             */
/*   Updated: 2026/05/14 17:03:02 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parsing.h"

void	free_token(void *token)
{
	free(((t_token *)token)->word);
	free(token);
}

void	token_cleanup(t_list *lst, t_data *dat)
{
	if (evaluate_state() == ERR_MALLOC)
		dat->quit = QUIT;
	dat->ret_code = get_and_print_error();
	ft_lstclear(lst, free_token);
}
