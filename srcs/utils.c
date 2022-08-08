/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:09:23 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/06 10:45:54 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_message(char *cmd, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

void	error_message_1(char *cmd, char *error)
{
	char	*message;

	message = ft_strjoin(cmd, error);
	perror(message);
	free(message);
}

int	ft_special_char(char c)
{
	if (c == 34 || c == 37 || c == 35)
		return (1);
	if (c >= 41 && c <= 47)
		return (1);
	if (c == 58 || c == 61 || c == 63 || c == 64)
		return (1);
	if (c == 91 || c == 93 || c == 93 || c == 94)
		return (1);
	if (c == 123 || c == 125 || c == 126)
		return (1);
	return (0);
}

//expand variables from env
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