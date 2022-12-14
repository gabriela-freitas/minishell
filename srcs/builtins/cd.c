/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:01:16 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/02 10:44:50 by mfreixo-         ###   ########.fr       */
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
	{
		*str = ft_strdup(path);
		if (!ft_strncmp("OLDPWD", var, 7))
			printf("%s\n",*str);
	}
	else
	{
		error_message("cd: ", var, " not set", 1);
		return (0);
	}
	return (1);
}

/*	Expands the path for
	cd - ; cd ~ ; cd ~/path ; cd
*/
static char	*find_path(char *str)
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
int	cd(char **args)
{
	char	*path;
	int		i;

	i = 0;
	while (args[i])
		i ++;
	if (i > 2)
	{
		parse_error_message("cd", ": too many arguments", 1);
		return (-1);
	}
	path = find_path(args[1]);
	if (!path)
		return (0);
	update_env_pwd("OLDPWD");
	if (chdir(path) == -1)
	{
		error_message("cd: ", path, ": No such file or directory", 1);
		free(path);
		return (-1);
	}
	free(path);
	(base()->errnumb) = 0;
	update_env_pwd("PWD");
	return (0);
}
