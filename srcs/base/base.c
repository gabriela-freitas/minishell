/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:50:37 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/14 10:42:12 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Acts as global variable, returns the up-to-date base*/
t_base	*base(void)
{
	static t_base	base;

	return (&base);
}

/*	Initializes all varibles from base()*/
void	ini_base(char **env)
{
	char	*paths;

	ini_env(env);
	paths = getenv("PATH");
	(base()->paths) = ft_split(paths, ':');
	(base()->home) = ft_strdup(getenv("HOME"));
	(base()->errnumb) = 0;
	(base()->oldpwd) = ft_strdup(find_env("OLDPWD"));
}

/*frees everything from struct base*/
void	base_free(void) //ir atualizando esta funcao a medida que adicionamos coisas no base
{
	env_free();
	//args_free();
	free(base()->home);
	free_split(base()->paths);
	ft_lstclear(&base()->cmds, free);
}
