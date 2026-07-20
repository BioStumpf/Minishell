/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 10:55:51 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/20 15:18:34 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

# include <stdbool.h>
# include "structs.h"
# include <signal.h>

extern volatile sig_atomic_t	g_ret;

//error handling
void				set_error(t_data *dat, enum e_err status);
bool				status_ok(t_data *dat);
bool				fatal_error(t_data *dat);
t_data				*data_storage(t_data *data);
void				cleanup(t_data *data);

#endif
