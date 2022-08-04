/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:13:36 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/04 17:44:30 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns zero (0) on success. -1 is returned on an error and errno is set appropriately
int cd(char *str) //function has more than 25 lines
{
	char    *new_path;

	old_pwd();
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
	if (!ft_strncmp("~", str, 1))
		new_path = ft_strjoin(getenv("HOME"), &str[1]);
	if (chdir(new_path) == -1)
	{
		error_message("cd: ", str);
		free(new_path);
		return (-1);
	}
	free(new_path);
	return (0);
}
