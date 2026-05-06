/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdnup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 11:45:28 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/05 16:38:28 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, char delimitter)
{
	size_t	len;
	char	*out;

	len = ft_strlen_char((char *) s, delimitter) + 1;
	if (s[len] != delimitter)
		return (NULL);
	out = malloc(len);
	if (!out)
		return (0);
	ft_strlcpy(out, s, len);
	return (out);
}
