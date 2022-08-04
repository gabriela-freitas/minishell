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

void print_env(void)
{
    t_env *aux;

    aux = base()->env;
    while (aux)
    {
        printf("%s=%s\n", aux->name, aux->content);
        aux = aux->next;
    }
}

// searches for name in env, if it doesnt exist creates it and adds it to the env
// if it exists changes the content for the given one
void change_env(char *name, char *content)
{
    t_env *aux;
    t_env *last;

    aux = base()->env;
    while (aux->next && aux->next->next)
    {
        if (!ft_strncmp(name, aux->name, ft_strlen(name)))
        {
            free(aux->content);
            aux->content = ft_strdup(content);
            return ;
        }
        aux = aux->next;
    }
    last = new_env(name, content);
    last->next = aux->next;
    aux->next = last;
}
