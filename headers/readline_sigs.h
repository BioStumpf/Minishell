/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_sigs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 13:14:41 by david             #+#    #+#             */
/*   Updated: 2026/07/07 14:43:12 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_SIGS_H
# define READLINE_SIGS_H

# include "structs.h"

void	sigquit_execute(int sig);
void	sigint_execute(int sig);
void	sigint_readline(int sig);
void	read_terminal(t_data *dat);
void	read_stdin(t_data *dat);
void	setup_signals(void (*sigquit)(int sig), void (*sigint)(int sig));

#endif
