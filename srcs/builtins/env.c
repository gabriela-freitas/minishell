/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 17:09:35 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/01 18:56:55 by gafreita         ###   ########.fr       */
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

void	env(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		;
	if (i == 1)
		print_env();
	else
		error_message("env: ‘", args[1], "’: No such file or directory", 127);
}
