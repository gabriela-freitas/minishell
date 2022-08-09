/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:13:36 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/09 18:51:46 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns zero (0) on success. -1 is returned on an error and errno is set appropriately
int	cd(char *str)
{
	char	*new_path;

	update_env_pwd("OLDPWD");
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
		new_path = ft_strjoin(getenv("HOME"), &str[1]);
	if (chdir(new_path) == -1)
	{
		new_path = ft_strjoin(str, ": No such file or directory");
		error_message("cd: ", new_path);
		free(new_path);
		return (-1);
	}
	update_env_pwd("PWD");
	// free(new_path);
	return (0);
}
