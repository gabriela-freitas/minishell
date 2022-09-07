/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:00:53 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/02 10:42:31 by mfreixo-         ###   ########.fr       */
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

/*	checks if there's more than one argument after exit */
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
	rl_clear_history();
	base_free();
	if (!check_alpha(args[1]))
	{
		error_message("exit: ", args[1], ": numeric argument required", 2);
		exit(2);
	}
	else
		exit(exit_status);
}
