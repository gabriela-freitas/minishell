/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:00:53 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/31 16:47:24 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	A valid input is a error number, so check if the input is valid
	i.e contais only digits*/
static int	check_alpha(char *s)
{
	int	i;

	if (!s)
		return (TRUE);
	i = -1;
	while (s[++i])
	{
		if (ft_isalpha(s[i]))
			return (FALSE);
	}
	return (TRUE);
}

static	int	too_many_args(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		;
	if (i > 2 && check_alpha(args[1]))
	{
		printf("exit\n");
		parse_error_message("exit: ", "too many arguments", 1);
		return (TRUE);
	}
	return (FALSE);
}

/*	Exits the program with the status code specified by the user,
	if it's valid*/
void	ft_exit(char **args)
{
	int	exit_status;

	if (too_many_args(args))
		return ;
	if (args[1])
		exit_status = ft_atoi(args[1]);
	else
		exit_status = 0;
	printf("exit\n");
	if (!check_alpha(args[1]))
	{
		error_message("exit: ", args[1], ": numeric argument required");
		exit(2);
	}
	else
		exit(exit_status);
}
