/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:13:36 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/13 15:38:56 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns zero (0) on success. -1 is returned on an error and errno is set appropriately
int	cd(char *str) /*Marta, refazer o cd, ter em conta os erros, e os unsets do HOME e do OLDPWD*/
{
	char	*new_path;
	char	*aux;

	new_path = str;
	if (!str)
		str = ft_strdup("");
	if (!ft_strncmp("", str, 1) || !ft_strncmp("-", str, 1))
	{
		if (!ft_strncmp("", str, 1))
			aux = ft_strdup("HOME");
		else if (!ft_strncmp("-", str, 1))
			aux = ft_strdup("OLDPWD");
		new_path = ft_strjoin(find_env(aux), &str[1]);
		if (!new_path)
		{
			error_message_1("cd: ", aux, " not set");
			free(aux);
			free(new_path);
			(base()->errnumb) = EPERM;
			return (-1);
		}
	}
	else if (!ft_strncmp("~", str, 1))
		new_path = ft_strdup(base()->home);
	update_env_pwd("OLDPWD");
	if (chdir(new_path) == -1)
	{
		(base()->errnumb) = errno;
		error_message("cd: ", str);
		return (-1);
	}
	(base()->errnumb) = 0;
	update_env_pwd("PWD");
	return (0);
}




/*
int	cd(char *str)
{
	char	*new_path;

	new_path = str;
	if (!ft_strncmp("", str, 1))
	{
		new_path = ft_strdup(base()->home);
		if (!new_path)
		{
			ft_putstr_fd("sh: cd: HOME not set\n", 2);
			(base()->errnumb) = EPERM;
			return (-1);
		}
	}
	else if (!ft_strncmp("~", str, 1))
		new_path = ft_strjoin(find_env("HOME"), &str[1]);
	else if (!ft_strncmp("-", str, 1))
		new_path = ft_strjoin(find_env("OLDPWD"), &str[1]);
	update_env_pwd("OLDPWD");
	if (chdir(new_path) == -1)
	{
		//new_path = ft_strjoin(str, ": No such file or directory");
		//error_message("cd: ", new_path);
		//free(new_path);
		(base()->errnumb) = errno;
		error_message("cd: ", str);
		return (-1);
	}
	(base()->errnumb) = 0;
	update_env_pwd("PWD");
	return (0);
}
*/