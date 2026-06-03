/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:52:11 by dstumpf           #+#    #+#             */
/*   Updated: 2026/05/17 18:36:16 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#ifndef MAIN_H
# define MAIN_H

// # define QUIT 1
// # define CONTINUE 1
# define NOCHAR 0
# define NOWORD NULL

enum e_err
{
    OK,
    ERR_MALLOC,
    // PARSE_ERR_INVALID_CHAR,
    PARSE_ERR_UNCLOSED_QUOTES
};

typedef struct s_data
{
	// char	quit;
	char		*input;
	enum e_err	err;
	int			ret_code;
//	t_ast	*ast;
//	t_envp	*envp;
}			t_data;

// typedef struct s_err
// {
// 	char		c;
// 	enum e_err	status;
// }				t_err;

//error handling
// void				set_error(enum e_err status, char c);
void				set_error(t_data *dat, enum e_err status);
bool				status_ok(t_data *dat);
bool				fatal_error(t_data *dat);
// t_err				*fetch_error(void);
// int					get_and_print_error(void);
// enum e_err			evaluate_state(void);

#endif
