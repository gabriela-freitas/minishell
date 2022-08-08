/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:23:25 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/08 19:53:26 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// searches for name in env, if it doesnt exist creates it and adds it to the env
// if it exists changes the content for the given one
void change_var(char *name, char *content)
{
	t_env *aux;
	t_env *last;

	aux = base()->env;
	while (aux->next)
	{
		if (!ft_strncmp(name, aux->name, ft_strlen(name)))
		{
			free(aux->content);
			aux->content = ft_strdup(content);
			return ;
		}
		else if(!aux->next->next)
			break;
		else
			aux = aux->next;
	}
	last = new_env(name, content);
	last->next = aux->next;
	aux->next = last;
}

void    export_one(char *str) //GABI export without args, is ordered ASCII and join declare -x  in the beginnig
{							//export with arguments but without = or value in front of = crashes
	char *name;
	char *content;

	name = ft_substr(str, 0, ft_strlen(str) - ft_strlen(ft_strchr(str, '=')));
	content = ft_strchr(str, '=') + 1;
	change_var(name, content);
	if (!strncmp("PATH", name, 5))  //GABI if we unset the PATHS, we have to set base()->PATHS to NULL
	{
		free(base()->paths);
		base()->paths = ft_split(content, ':');
	}
	if (!strncmp("HOME", name, 5))  //GABI if we unset the PATHS, we have to set base()->PATHS to NULL
	{
		free(base()->home);
		base()->home = ft_strdup(content);
	}
	free(name);
}

void export(char **str) //Esse o execute vai chamar GABI
{
    // if (!str[1])
    // //Create a function to convert env list to char **
    // //ordenate this in ASCII code
    // //print
    //     export_ordenate();
	//str[0] = export
	export_one(str[1]);
}
