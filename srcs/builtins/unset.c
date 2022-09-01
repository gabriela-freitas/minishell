/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:50:37 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/01 18:57:36 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//unset also receives more than one value
void	delete_var(char	*name)
{
	t_env	*aux;
	t_env	*aux_next;

	aux = base()->env;
	if (!aux->next)
		return ;
	aux_next = aux->next;
	if (!strncmp(name, aux->name, ft_strlen(name)))
	{
		delone_env(aux);
		base()->env = aux_next;
		return ;
	}
	while (aux_next)
	{
		if (!strncmp(name, aux_next->name, ft_strlen(name)))
		{
			aux->next = aux_next->next;
			delone_env(aux_next);
			break ;
		}
		aux = aux_next;
		aux_next = aux_next->next;
	}
}

int	is_valid_name(char *name)
{
	int	i;

	i = -1;
	while (name[++i])
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
		{
			error_message("unset: `", name,"': not a valid identifier", 1);
			return (0);
		}
	}
	return (1);
}

//Gabi uniformizar esse erro!!
/*
	Simulates unset builtins
	removes from base()->env the variable with name = *str
*/
void	unset_one(char *name)
{
	if (!is_valid_name(name))
		return ;
	if (!strncmp("PATH", name, 5))
	{
		free_split(base()->paths);
		base()->paths = NULL;
	}
	delete_var(name);
}

void	unset(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[++i])
		unset_one(cmds[i]);
}
