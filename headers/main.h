/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:52:11 by dstumpf           #+#    #+#             */
/*   Updated: 2026/05/06 11:00:27 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../env.h"

typedef struct s_data
{
//	t_ast	*ast;
//	t_envp	*envp;
	char			*input;
	char			**new_variable;
	t_env_tracker	*env_mp;
}			t_data;

#endif
