/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:50:37 by gafreita          #+#    #+#             */
/*   Updated: 2022/07/29 19:50:37 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *new_env(char *name, char *content)
{
	t_env *new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (0);
	new_env->name = ft_strdup(name);
	new_env->content = ft_strdup(content);
	new_env->next = NULL;
	return (new_env);
}

static void env_append(t_env **head, t_env *add_env)
{
	t_env *aux;
    t_env *new_envi;

    new_envi = new_env(add_env->name, add_env->content);
    free(add_env->name);
    free(add_env->content);
    free(add_env);
	if (!head || !*head)
        *head = new_envi;
	else
	{
		aux = *head;
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = new_envi;
        aux->next->next = NULL;
    }
}

void ini_env(char **env) //has more than 25 lines
{
    t_env   *aux_env;
    int     i;
    int     j;
    char    **split;

    base()->env = env;
    split = ft_split(env[0], '=');
    base()->env_split = new_env(split[0], split[1]);
    free(split[0]);
    free(split[1]);
    free(split);
    i = 0;
    while (env[++i])
    {
        split = ft_split(env[i], '=');
        aux_env = new_env(split[0], ft_strchr(env[i], '=') + 1);

        env_append(&(base()->env_split), aux_env);
        j = 0;
        while (split[j])
            free(split[j++]);
        free(split);
    }
}

void delone_env(t_env *one_env)
{
    free(one_env->name);
	free(one_env->content);
}

void env_free(void)
{
	t_env *aux;

    aux = (base()->env_split)->next;
    while (base()->env_split)
    {
        delone_env(base()->env_split);
        free(base()->env_split);
        (base()->env_split) = aux;
        if (base()->env_split)
            aux = (base()->env_split)->next;
    }
    free(base()->env_split);
}
