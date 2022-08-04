/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:17:00 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/04 22:01:28 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*allocates a new size and copies the content for the new allocated area*/
char	**ft_my_realloc(char **ptr, size_t size)
{
	char		**temp;
	size_t		i;

	if (!ptr)
		return (malloc(size));
	temp = malloc(sizeof(char *) * size);
	i = -1;
	while (++i < (size - 1) && ptr[i])
		temp[i] = ptr[i];
	free(ptr);
	return (temp);
}
