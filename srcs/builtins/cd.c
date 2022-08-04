/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:13:36 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/02 17:43:24 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns zero (0) on success. -1 is returned on an error and errno is set appropriately
int cd(char *str) //function has more than 25 lines
{
    char    *new_path;
    char    *path;
    int     length;
    
    length = 100;
    path = malloc(sizeof(char) * length);
    getcwd(path, length);
    old_pwd();
    new_path = str;
    if (!ft_strncmp("", str, 1))
        new_path = base()->home;
    if (chdir(new_path) == -1)
    {
        if (errno == ENOENT)
        {
            printf("cd: %s: No such file or directory\n", str);
            free(path);
            return (-1);
        }            
        if (errno == EACCES)
        {
            printf("cd: %s: Permission denied\n", str);
            free(path);
            return (-1);
        }
    }
    free(path);
    return (0);
}
