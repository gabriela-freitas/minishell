/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:50:37 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/26 17:09:27 by gafreita         ###   ########.fr       */
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
	char	*shlvl;

	ini_env(env);
	if (find_env("SHLVL"))
		shlvl = ft_itoa(ft_atoi(find_env("SHLVL")) + 1);
	else
		shlvl = ft_itoa(1);
	change_var("SHLVL", shlvl);
	free(shlvl);
	paths = getenv("PATH");
	(base()->paths) = ft_split(paths, ':');
	(base()->home) = ft_strdup(getenv("HOME"));
	(base()->errnumb) = 0;
	(base()->oldpwd) = ft_strdup(find_env("OLDPWD"));
}

/*frees everything from struct base*/
void	base_free(void)
{
	env_free();
	//args_free();
	free(base()->home);
	free_split(base()->paths);
	ft_lstclear(&base()->div_pipes, free);
}
