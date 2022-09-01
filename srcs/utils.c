/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:09:23 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/01 18:55:36 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Function used to print errors in parsing: exit errors, parsing pipes
	and unfinished quotes. It also updates the errnumb*/
void	parse_error_message(char *cmd, char *error, int error_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	base()->errnumb = error_code;
}

/*Function to print errors during execution*/
void	error_message(char *cmd, char *arg, char *error, int error_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	base()->errnumb = error_code;
}

/*	Prints the error for command not found
	and updates the error number accordingly*/
void	command_not_found(char *cmd)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	base()->errnumb = 127;
}

int	ft_special_char(char c)
{
	if (c >= 34 && c <= 37)
		return (1);
	if (c >= 41 && c <= 47)
		return (1);
	if (c == 58 || c == 61 || c == '?' || c == 64)
		return (1);
	if (c == 91 || c == 93 || c == 93 || c == 94)
		return (1);
	if (c == 123 || c == 125 || c == 126 || c == 39)
		return (1);
	if (c == '\\')
		return (1);
	return (0);
}
