/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:13:36 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/15 13:28:23 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	simulates echo builtin from bash
	printf array of strigns separated by ' ' (space)
*/
void	ft_echo(char **str)
{
	int	new_line;

	new_line = TRUE;
	if (!str || !str[1])
	{
		printf("\n");
		return ;
	}
	if (*str)
		str++;
	if (!ft_strncmp(*str, "-n", 3))
	{
		new_line = FALSE;
		str++;
	}
	while (*str)
	{
		printf("%s ", *str);
		str++;
	}
	if (new_line)
		printf("\n");
	(base()->errnumb) = 0;
}
