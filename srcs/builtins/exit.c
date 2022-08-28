/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:00:53 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/28 20:36:07 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **str)
{
	int	exit_status;
	if (str[1])
		exit_status = ft_atoi(str[1]);
	else
		exit_status = 0;
	exit(exit_status);
}
