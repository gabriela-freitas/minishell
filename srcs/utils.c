/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:09:23 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/04 19:38:11 by gafreita         ###   ########.fr       */
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
	// 	free(temp->content);
	// 	free(temp);
	// 	temp = base()->cmds;
	// }
	// ft_lstclear(&base()->cmds, free);
	// free(base()->cmds);
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

