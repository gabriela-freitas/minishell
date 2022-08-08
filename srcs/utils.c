/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:09:23 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/06 10:45:54 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipes(void)
{
	// t_list	*temp;

	// temp = base()->cmds;
	// while (temp)
	// {
	// 	base()->cmds = base()->cmds->next;
	// 	freerbase()->cmds);
	return ;
}

void	error_message(char *cmd, char *error)
{
	free_pipes();
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

void	error_message_1(char *cmd, char *error)
{
	char	*message;

	message = ft_strjoin(cmd, error);
	perror(message);
	free(message);
}
