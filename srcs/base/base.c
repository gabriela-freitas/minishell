/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:50:37 by gafreita          #+#    #+#             */
/*   Updated: 2022/07/29 19:50:37 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Acts as global variable, returns the up-to-date base*/
t_base	*base(void)
{
	static t_base	base;

	return (&base);
}

/*	Initializes base()->base base()->home from the environment, where*/
void	ini_paths(void)
{
	char	*paths;
	
	paths = getenv("PATH");
	(base()->paths) = ft_split(paths, ':');
	(base()->home) = ft_strdup(getenv("HOME"));
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
