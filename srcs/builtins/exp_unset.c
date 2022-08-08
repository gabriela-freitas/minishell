/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:50:37 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/08 18:30:44 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//only prints variables with value
void	print_env(void)
{
	t_env	*aux;

	aux = (base()->env);
	while (aux)
	{
		if (aux->content)
			printf("%s=%s\n", aux->name, aux->content);
		aux = aux->next;
	}
}

// searches for name in env, if it doesnt exist creates it and adds it to the env
// if it exists changes the content for the given one
void	change_var(char *name, char *content)
{
	t_env	*aux;
	t_env	*last;

	aux = (base()->env);
	while (aux->next)
	{
		if (!ft_strncmp(name, aux->name, ft_strlen(name)))
		{
			free(aux->content);
			aux->content = ft_strdup(content);
			return ;
		}
		else if (!aux->next->next)
			break ;
		else
			aux = aux->next;
	}
	last = new_env(name, content);
	last->next = aux->next;
	aux->next = last;
}

void	export(char *str)//GABI export without args, is ordered ASCII and join declare -x  in the beginnig
{							//export with arguments but without = or value in front of = crashes
	char	*name;
	char	*content;

	name = ft_substr(str, 0, ft_strlen(str) - ft_strlen(ft_strchr(str, '=')));
	content = ft_strchr(str, '=') + 1;
	change_var(name, content);
	if (!strncmp("PATH", name, 5)) //GABI if we unset the PATHS, we have to set base()->PATHS to NULL
	{
		free(base()->paths);
		(base()->paths) = ft_split(content, ':');
	}
	if (!strncmp("HOME", name, 5)) //GABI if we unset the PATHS, we have to set base()->PATHS to NULL
	{
		free(base()->home);
		(base()->home) = ft_strdup(content);
	}
	free(name);
}

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
	if (!strncmp("HOME", str, 5)) //GABI if we unset the PATHS, we have to set base()->PATHS to NULL
		base()->home = NULL;
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
