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

void ls()
{
	char    *path;
	int     length;

	length = 100;
	path = malloc(sizeof(char) * length);
	getcwd(path, length);
	printf("%s\n", path);

}

//returns zero (0) on success. -1 is returned on an error and errno is set appropriately
int cd(char *str) //has more than 25 lines
{
	char    *path;
	int     length;
	char    *new_path;

	length = 100;
	path = malloc(sizeof(char) * length);
	getcwd(path, length);
	new_path = str;
	if (!ft_strncmp("..", str, 3))
	{
		new_path = ft_substr(path, 0, ft_strlen(path) - ft_strlen(ft_strrchr(path, '/')));
		free(path);
	}
	else if (!ft_strncmp("", str, 1))
		new_path = base()->home;
	if (chdir(new_path) == -1)
	{
		if (errno == ENOENT)
		{
			printf("cd: No such file or directory\n"); //usar perror!!
			free(new_path);
			return (-1);
		}
		if (errno == EACCES)
		{
			printf("cd: %s: Permission denied\n", str);
			free(new_path);
			return (-1);
		}
	}
	return (0);
}


