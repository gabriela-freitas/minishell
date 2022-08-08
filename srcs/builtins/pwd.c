/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:13:36 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/08 18:31:17 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	simulates pwd builtin
	printf current directory
*/
void	pwd(void)
{
	char	*path;
	int		length;

	length = 100;
	path = malloc(sizeof(char) * length);
	getcwd(path, length);
	printf("%s\n", path);
	free(path);
}

/*	sets the variable OLDPWD, in env to the current directory
	it has to be called before changing current directory (eg. with cd)	
*/
void	old_pwd(void)
{
	char	*path;
	int		length;

	length = 100;
	path = malloc(sizeof(char) * length);
	getcwd(path, length);
	change_var("OLDPWD", path);
	free(path);
}
