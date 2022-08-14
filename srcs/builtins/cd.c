/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:13:36 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/14 13:14:40 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int cd_home(char **str)
{
	char	*path;
	
	path = find_env("HOME");
	if (path)
		*str = ft_strdup(path);	
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		(base()->errnumb) = 1;
		return (0);
	}
	return (1);
}

static int cd_oldpwd(char **str)
{
	char	*path;
	
	path = find_env("OLDPWD");
	if (path)
		*str = ft_strdup(path);	
	else
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		(base()->errnumb) = 1;
		return (0);
	}
	return (1);
}


//returns zero (0) on success. -1 is returned on an error and errno is set appropriately
int	cd(char *str) /*Marta, juntar o cd_home e cd_oldpwd, em principio depois disto ja tem o numero de linhas maximo*/
{
	char *path;
	
	if (!str || !ft_strncmp("", str, 1))
	{
		if(!cd_home (&path))
			return (0);
	}
	else if (!ft_strncmp("-", str, 1))
	{
		if(!cd_oldpwd (&path))
			return (0);
	}
	else if (!ft_strncmp("~", str, 1))
		path = ft_strjoin(base()->home, &str[1]);
	else
		path = ft_strdup(str);
	update_env_pwd("OLDPWD");
	if (chdir(path) == -1)
	{
		(base()->errnumb) = errno;
		error_message("cd: ", path);
		free(path);
		return (-1);
	}
	free(path);
	(base()->errnumb) = 0;
	update_env_pwd("PWD");
	return (0);
}