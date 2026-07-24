/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 17:05:45 by david             #+#    #+#             */
/*   Updated: 2026/07/27 16:36:43 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <err.h>

void	sigint_readline(int sig)
{
	g_ret = (128 + sig) % 256;
}

void	sigint_exec(int sig)
{
	g_ret = (128 + sig) % 256;
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

void	sigquit_handler(int sig)
{
	g_ret = (128 + sig) % 256;
	write(STDOUT_FILENO, "Quit\n", 5);
}

void	setup_signal(int sig, void (*sig_func)(int sig))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sig_func;
	sigaction(sig, &sa, NULL);
}
