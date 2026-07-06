/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 10:55:51 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/06 12:10:34 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

# include <stdbool.h>
# include "structs.h"

//error handling
void				set_error(t_data *dat, enum e_err status);
bool				status_ok(t_data *dat);
bool				fatal_error(t_data *dat);
t_data				*data_storage(t_data *data);

#endif
