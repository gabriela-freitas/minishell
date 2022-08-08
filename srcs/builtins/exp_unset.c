/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:50:37 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/08 19:40:17 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//only prints variables with value
void print_env(void)
{
	t_env *aux;

	aux = base()->env;
	while (aux)
	{
		if (aux->content)
			printf("%s=%s\n", aux->name, aux->content);
		aux = aux->next;
	}
}

 //GABI if we unset the PATHS, we have to set base()->PATHS to NULL
void	unset(char *str)
{
	t_env *aux;
	t_env *aux_next;

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
			break;
		}
		aux = aux_next;
		aux_next = aux_next->next;
	}
}
