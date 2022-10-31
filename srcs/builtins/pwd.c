/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:13:36 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/31 17:25:26 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pwd_aux(void)
{
	char	*path;
	int		length;

	length = 100;
	path = malloc(sizeof(char) * length);
	getcwd(path, length);
	printf("%s\n", path);
	free(path);
	exit(1);
}

/*	simulates pwd builtin
	printf current directory
*/
void	pwd(void)
{
	int	pid1;
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (base()->num_pipes == 1)
			exec_setup_one(base()->pipes);
		pid1 = fork();
		if (pid1 == 0)
			pwd_aux();
		else
		{
			signal(SIGINT, sig_block_nl);
			waitpid(pid1, NULL, 0);
			exit(0);
		}
	}
	else
	{
		signal(SIGINT, sig_block_nl);
		waitpid(pid, NULL, 0);
		(base()->errnumb) = 0;
	}
}

/*	sets the variable OLDPWD or PWD, according
	it has to be called before and after changing current directory (eg. with cd)
*/
void	update_env_pwd(char	*var)
{
	char	*path;
	int		length;

	length = 100;
	path = malloc(sizeof(char) * length);
	getcwd(path, length);
	change_var(var, path);
	free(path);
}
