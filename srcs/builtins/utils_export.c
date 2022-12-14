/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:58:19 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/31 15:44:01 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*formats the name and content to this format NAME="CONTENT"*/
static char	*format_output(t_env *aux)
{
	char	*var;
	char	*temp;

	var = ft_strjoin(aux->name, "=\"");
	temp = ft_strjoin(var, aux->content);
	free(var);
	var = ft_strjoin(temp, "\"");
	free(temp);
	return (var);
}

/*	converts the env list to a string's array
	return a allocated memory area, needs to be freed after
	with formated output*/
static char	**convert_env_list_export(void)
{
	t_env	*aux;
	char	**mini_env;
	char	*var;
	int		size;

	aux = base()->env;
	size = 0;
	mini_env = malloc(sizeof(char *) * 2);
	mini_env[0] = NULL;
	while (aux)
	{
		if (aux->content == NULL)
			var = ft_strdup(aux->name);
		else
			var = format_output(aux);
		add_split(&mini_env, &size, var);
		aux = aux->next;
	}
	return (mini_env);
}

/*	returns the env matrix adding "declare -x " in front, as in bash
	to be used next in ordenate_env*/
static char	**env_to_export(char	**env)
{
	char	**env_to_print;
	char	*temp;
	int		size;
	int		i;

	size = 0;
	env_to_print = malloc(sizeof(char *) * 2);
	env_to_print[0] = NULL;
	i = -1;
	while (env[++i])
	{
		temp = ft_strjoin("declare -x ", env[i]);
		add_split(&env_to_print, &size, temp);
	}
	free_split(env);
	return (env_to_print);
}

/*Ordenates in ASCII order the env, adding "declare -x " in front, as in bash*/
void	export_ordenate(void)
{
	char	**env;
	char	*temp;
	int		i;
	int		j;

	env = convert_env_list_export();
	i = -1;
	while (env[++i])
	{
		j = i;
		while (env[++j])
		{
			if (ft_strncmp(env[i], env[j], ft_strlen(env[i])) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
		}
	}
	env = env_to_export(env);
	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	free_split(env);
}
