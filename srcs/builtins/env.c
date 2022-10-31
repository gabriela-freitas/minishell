/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 17:09:35 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/31 15:44:58 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*prints env variables*/
static void	print_env(void)
{
	t_env	*aux;

	aux = (base()->env);
	while (aux)
	{
		if (aux->content)
			printf("%s=%s\n", aux->name, aux->content);
		else if (aux->content != NULL)
			printf("%s=\n", aux->name);
		aux = aux->next;
	}
}

static void	env_aux(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		;
	if (i == 1)
		print_env();
	else
		error_message("env: ‘", args[1], "’: No such file or directory", 127);
	exit(1);
}

/* function that simulates env builtin */
void	env(char **args)
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
			env_aux(args);
		else
		{
			signal(SIGINT, sig_block_nl);
			waitpid(pid1, NULL, 0);
			exit(1);
		}
	}
	else
	{
		signal(SIGINT, sig_block_nl);
		waitpid(pid, NULL, 0);
		(base()->errnumb) = 0;
	}
}

/*	converts the env list to a string's array
	return a allocated memory area, needs to be freed after*/
char	**convert_env_list(void)
{
	t_env	*aux;
	char	**mini_env;
	char	*temp;
	char	*var;
	int		size;

	aux = base()->env;
	size = 0;
	mini_env = malloc(sizeof(char *) * 2);
	mini_env[0] = NULL;
	while (aux)
	{
		temp = ft_strjoin(aux->name, "=");
		var = ft_strjoin(temp, aux->content);
		free(temp);
		add_split(&mini_env, &size, var);
		aux = aux->next;
	}
	return (mini_env);
}

/*returns the content of a env variable or NULL if it doesn't exists*/
char	*find_env(char	*name)
{
	t_env	*aux;

	aux = base()->env;
	while (aux->next)
	{
		if (!ft_strncmp(name, aux->name, ft_strlen(name)))
			return (aux->content);
		aux = aux->next;
	}
	return (NULL);
}
