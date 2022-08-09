/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:50:37 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/09 15:57:43 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//unset also receives more than one value

/*
	Simulates unset builtins
	removes from base()->env the variable with name = *str
*/
void	unset(char *str) /*Marta, TOO MANY LINES*/
{
	t_env	*aux;
	t_env	*aux_next;

	aux = base()->env;
	if (!aux->next)
		return ;
	aux_next = aux->next;
	if (!strncmp("PATH", str, 5))
	{
		free_split(base()->paths);
		base()->paths = NULL;
	}
	if (!strncmp("HOME", str, 5))
	{
		free(base()->home);
		base()->home = NULL;
	}
	if (!strncmp(str, aux->name, ft_strlen(str)))
	{
		delone_env(aux);
		free(aux);
		base()->env = aux_next;
		return ;
	}
	while (aux_next)
	{
		if (!strncmp(str, aux_next->name, ft_strlen(str)))
		{
			aux->next = aux_next->next;
			delone_env(aux_next);
			free(aux_next);
			break ;
		}
		aux = aux_next;
		aux_next = aux_next->next;
	}
}
