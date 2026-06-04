/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 10:55:51 by dstumpf           #+#    #+#             */
/*   Updated: 2026/06/04 10:56:08 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "structs.h"

#ifndef ERR_H
# define ERR_H

# define NOWORD NULL

//error handling
// void				set_error(enum e_err status, char c);
void				set_error(t_data *dat, enum e_err status);
bool				status_ok(t_data *dat);
bool				fatal_error(t_data *dat);

#endif
