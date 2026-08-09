/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reopen_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 12:48:25 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/09 09:18:53 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

static void	make_name(char name[24], int fd)
{
	char	num[11];

	ft_strlcpy(name, "/proc/self/fd/", 15);
	ft_itoa_buff(fd, num, 11);
	ft_strlcpy(name + 14, num, 11);
}

int	reopen_heredoc(int fd, int flag)
{
	char	proc_name[25];

	make_name(proc_name, fd);
	return (open(proc_name, flag));
}
