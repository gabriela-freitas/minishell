/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:23:25 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/09 21:04:27 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*searches for name in env, if it doesnt exist creates it and adds it to the env
if it exists changes the content for the given one*/
void	change_var(char *name, char *content)
{
	t_env	*aux;
	t_env	*last;

	aux = base()->env;
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

/*GABI export without args, is ordered ASCII
	and join declare -x  in the beginnig*/
// GABI falta checar aqueles caracteres invalidos no name
void	export_one(char *str)
{
	char	**split;

	if (!ft_strchr(str, '='))
		return ;
	split = ft_split(str, '=');
	if (!split[0])
	{
		ft_printf("minishell: export: `=': not a valid identifier\n");
		free_split(split);
		return ;
	}
	change_var(split[0], split[1]);
	if (!strncmp("PATH", split[0], 5))
	{
		free(base()->paths);
		(base()->paths) = ft_split(split[1], ':');
	}
	if (!strncmp("HOME", split[0], 5))
	{
		free(base()->home);
		base()->home = ft_strdup(split[1]);
	}
	free(split[0]);
	free(split);
}

//str[0] = export
void	export(char **str) //Esse o execute vai chamar GABI
{
	int	i;

	if (!str[1])
		export_ordenate();
	i = 0;
	while (str[++i])
		export_one(str[i]);
}
