/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_sigs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 18:39:31 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 18:39:31 by dstumpf          ###   ########.fr       */
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
