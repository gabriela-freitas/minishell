/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:13:36 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/20 17:59:27 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Searches for the path of var (it can be HOME or OLDPWD) and changes str to
	its value, or prints the error and sets errnum to 1 (OPERARTION NOT PERMITTED)
*/
static int	cd_oldpwd(char **str, char *var)
{
	char	*path;

	path = find_env(var);
	if (path)
		*str = ft_strdup(path);
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd(" not set\n", 2);
		(base()->errnumb) = 1;
		return (0);
	}
	return (1);
}

char	*find_path(char *str)
{
	char	*path;

	if (!str || !ft_strncmp("", str, 2))
	{
		if (!cd_oldpwd (&path, "HOME"))
			return (0);
	}
	else if (!ft_strncmp("-", str, 2))
	{
		if (!cd_oldpwd (&path, "OLDPWD"))
			return (0);
	}
	else if (!ft_strncmp("~", str, 2))
		path = ft_strjoin(base()->home, &str[1]);
	else
		path = ft_strdup(str);
	return (path);
}

/*	Simulates cd builtin*/
int	cd(char *str)
{
	char	*path;

	path = find_path(str);
	if (!path)
		return (0);
	update_env_pwd("OLDPWD");
	if (chdir(path) == -1)
	{
		(base()->errnumb) = 1;
		error_message("cd: ", path);
		free(path);
		return (-1);
	}
	free(path);
	(base()->errnumb) = 0;
	update_env_pwd("PWD");
	return (0);
}
