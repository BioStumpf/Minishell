/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_storage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 11:26:15 by knajmech          #+#    #+#             */
/*   Updated: 2026/06/22 11:35:45 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "execution.h"

t_data	*data_storage(t_data	*data)
{
	static t_data	*data_storage;

	if (data == NULL)
		return (data_storage);
	else
		data_storage = data;
}
