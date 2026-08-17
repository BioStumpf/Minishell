/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_sigs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 13:14:41 by david             #+#    #+#             */
/*   Updated: 2026/08/17 17:02:56 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_SIGS_H
# define READLINE_SIGS_H

# include "structs.h"

void	sigint_handler(int sig);
void	read_terminal(t_data *dat);
void	read_stdin(t_data *dat);
void	setup_signal(int sig, void (*sigint)(int sig));
void	signal_newline(void);
int		readline_hook(void);

#endif
