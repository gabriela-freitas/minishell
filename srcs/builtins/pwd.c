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

void pwd() //saber ser e para devolver erro
{
    char    *path;
    int     length;
    
    length = 100;
    path = malloc(sizeof(char) * length);
    getcwd(path, length);
    printf("%s\n", path);
    free(path);
}

void old_pwd(void)
{
    char    *path;
    int     length;
    
    length = 100;
    path = malloc(sizeof(char) * length);
    getcwd(path, length);
    change_env("OLDPWD", path);
    free(path);
}