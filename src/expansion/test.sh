# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dstumpf <dstumpf@student.42vienna.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/23 17:18:00 by dstumpf           #+#    #+#              #
#    Updated: 2026/06/23 17:57:36 by dstumpf          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

showargs() {
    local i=0
    for arg; do
        printf 'arg[%d] = <%s>\n' "$((i++))" "$arg"
    done
}

var="a b "

showargs "i"$var" hello"
#a b " hello"
