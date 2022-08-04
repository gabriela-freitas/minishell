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

//only prints variables with value
void print_env(void)
{
    t_env *aux;

    aux = base()->env_split;
    while (aux)
    {
        if (aux->content)
            printf("%s=%s\n", aux->name, aux->content);
        aux = aux->next;
    }
}

// searches for name in env, if it doesnt exist creates it and adds it to the env
// if it exists changes the content for the given one
void change_var(char *name, char *content)
{
    t_env *aux;
    t_env *last;

    aux = base()->env_split;
    while (aux->next)
    {
        if (!ft_strncmp(name, aux->name, ft_strlen(name)))
        {
            free(aux->content);
            aux->content = ft_strdup(content);
            return ;
        }
        else if(!aux->next->next)
            break;
        else
            aux = aux->next;
    }
    last = new_env(name, content);
    last->next = aux->next;
    aux->next = last;
}

void    export(char *str)
{
    char *name;
    char *content;

    name = ft_substr(str, 0, ft_strlen(str) - ft_strlen(ft_strchr(str, '=')));
    content = ft_strchr(str, '=') + 1;
    change_var(name, content);
    free(name);
}

void    unset(char *str)
{
    t_env *aux;
    t_env *aux_next;

    aux = base()->env_split;
    if (!aux->next)
        return ;
    aux_next = aux->next;
    if (!strncmp("HOME", str, 5))
        base()->home = NULL;
    if (!strncmp(str, aux->name, ft_strlen(str)))
    {
        delone_env(aux);
        free(aux);
        base()->env_split = aux_next;
        return ;
    }
    while (aux_next)
    {
        if (!strncmp(str, aux_next->name, ft_strlen(str)))
        {
            aux->next = aux_next->next;
            delone_env(aux_next);
            free(aux_next);
            break;
        }
        aux = aux_next;
        aux_next = aux_next->next;
    }
}
