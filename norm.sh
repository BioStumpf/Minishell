# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    norm.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: david <dstumpf@student.42vienna.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/07 12:04:04 by david             #+#    #+#              #
#    Updated: 2026/07/07 12:16:51 by david            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/sh
	# \( -path "./tests" -o -path "./src/builtins" -o -path "./src/cmd" -o -path "./src/env" \) -prune -o \

output=$(find . \
	\( -path "./tests" \) -prune -o \
	\( -name "*.c" -o -name "*.h" \) \
	! -name "test.c" ! -name "to_delete_later.c" \
	-exec norminette {} +)

# Remove the allowed error
filtered=$(printf "%s\n" "$output" | grep "Error")

if [ -z "$filtered" ]; then
    exit 0
fi

printf "%s\n" "$filtered"
exit 1
