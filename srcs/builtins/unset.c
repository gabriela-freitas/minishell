/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:50:37 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/02 10:41:22 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//unset also receives more than one value
static void	delete_var(char	*name)
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

/*	checks if the variable we are trying to unset
	has only alphanumeric characters or _	
*/
static int	is_valid_name(char *name)
{
	int	i;

	i = -1;
	while (name[++i])
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
		{
			error_message("unset: `", name, "': not a valid identifier", 1);
			return (0);
		}
	}
	return (1);
}

/*
	unsets a single variable
	removes from base()->env the variable with name = *str
*/
static void	unset_one(char *name)
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

// Simulates unset builtins
void	unset(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[++i])
		unset_one(cmds[i]);
}
