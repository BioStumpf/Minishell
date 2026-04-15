/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 18:01:36 by dstumpf           #+#    #+#             */
/*   Updated: 2026/04/14 18:02:35 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdio.h>
#include "libft.h"

Test(print, string) {
    cr_assert_eq(ft_atoi("1"), 0);
}
