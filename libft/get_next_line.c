/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:03:48 by dstumpf           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/11/26 15:20:29 by dstumpf          ###   ########.fr       */
=======
/*   Updated: 2026/06/23 13:56:33 by knajmech         ###   ########.fr       */
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
<<<<<<< HEAD
=======
#include "err.h"
#include "structs.h"

void	set_val(enum e_err value)
{
	t_data	*data_address;

	data_address = data_storage(NULL);
	set_error(data_address, value);
}
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc

char	*get_next_line(int fd)
{
	static t_fdlist	glob_stash[1024];
<<<<<<< HEAD
=======
	enum e_err		error_type;
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc
	t_fdlist		*stash;
	t_lineinfo		line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	stash = &glob_stash[fd];
	if (!init_line(&line))
<<<<<<< HEAD
		return (NULL);
	cpy_buff_to_line(stash, &line, fd);
	line.line = ft_realloc(stash, &line, line.line_i + 1);
=======
		return (set_val(ERR_MALLOC), NULL);
	error_type = cpy_buff_to_line(stash, &line, fd);
	if (error_type)
		return (set_val(error_type), NULL);
	line.line = ft_realloc(stash, &line, line.line_i + 1);
	if (line.line == NULL)
		return (set_val(ERR_MALLOC), NULL);
>>>>>>> 9416c658e3301417b663f3d8b7ce3077880516fc
	return (line.line);
}
