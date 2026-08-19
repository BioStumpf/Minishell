/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 18:46:18 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 18:46:19 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <err.h>

void	sigint_handler(int sig)
{
	g_ret = (128 + sig) % 256;
}

void	signal_newline(void)
{
	if (g_ret == 128 + SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}

int	readline_hook(void)
{
	if (g_ret == (128 + SIGINT) % 256)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (0);
}

void	setup_signal(int sig, void (*sig_func)(int sig))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sig_func;
	sigaction(sig, &sa, NULL);
}
