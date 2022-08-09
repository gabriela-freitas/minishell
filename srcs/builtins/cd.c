/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:13:36 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/09 20:08:03 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns zero (0) on success. -1 is returned on an error and errno is set appropriately
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
		error_message("cd: ", str);
		return (-1);
	}
	update_env_pwd("PWD");
	return (0);
}
