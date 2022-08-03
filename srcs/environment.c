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

void env_append(t_env **head, t_env *add_env)
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

void delone_env(t_env *one_env)
{
    free(one_env->name);
	free(one_env->content);
}

t_env *ini_env(char **env)
{
    t_env   *mini_env;
    t_env   *aux_env;
    int     i;
    int     j;
    char    **split;

    split = ft_split(env[0], '=');
    mini_env = new_env(split[0], split[1]);
    free(split[0]);
    free(split[1]);
    free(split);
    i = 0;
    while (env[++i])
    {
        split = ft_split(env[i], '=');
        aux_env = new_env(split[0], ft_strchr(env[i], '=') + 1);
        env_append(&mini_env, aux_env);
        j = 0;
        while (split[j])
            free(split[j++]);
        free(split);
    }
    return (mini_env);
}

void env_clear(t_env **mini_env)
{
	t_env *aux;

    aux = (*mini_env)->next;
    while (*mini_env)
    {
        delone_env(*mini_env);
        free(*mini_env);
        (*mini_env) = aux;
        if (*mini_env)
            aux = (*mini_env)->next;
    }
}