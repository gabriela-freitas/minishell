/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:58:19 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/08 19:35:22 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*returns the content of a env variable or NULL if it doesn't exists
searchs inside env list*/
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

/*converts the env list to a string's array
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
	mini_env[0] = '\0';
	while (aux)
	{
		temp = ft_strjoin(aux->name, "=");
		var = ft_strjoin(temp, aux->content);
		// printf("%s\n", var);
		free(temp);
		add_split(&mini_env, &size, var);
		aux = aux->next;
	}
	return (mini_env);
}
