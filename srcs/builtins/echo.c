/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:13:36 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/30 22:28:28 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Check if there's a flag (-n).
	Returns FALSE if the flag is valid and a new line should not be printed
	and TRUE otherwise (default)
	Accepts -n with multiples 'n' (i.e. -nnnnnn) as in bash*/
static int	check_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		while (str[++i] && str[i] == 'n')
			;
		if (!str[i])
			return (FALSE);
	}
	return (TRUE);
}

/*	simulates echo builtin from bash
	printf array of strigns separated by ' ' (space)
*/
void	ft_echo(char **str)
{
	int	new_line;
	int	pid;

	if (base()->num_pipes == 1)
		exec_setup_one(base()->pipes);
	pid = fork();
	if (pid == 0)
	{
		if (!str || !str[1])
		{
			printf("\n");
			return ;
		}
		if (*str)
			str++;
		new_line = check_flag(*str);
		if (!new_line)
			str++;
		while (*str)
		{
			printf("%s", *str);
			str++;
			if (*str)
				printf(" ");
		}
		if (new_line)
			printf("\n");
		exit(1);
	}
	else
	{
		// if (base()->pipes[0].fd[OUT] != STD)
		// 	close(base()->pipes[0].fd[OUT]);
		// if (base()->pipes[0].fd[IN] != STD)
		// 	close(base()->pipes[0].fd[IN]);
		signal(SIGINT, sig_block_nl);
		waitpid(pid, NULL, 0);
		exit(1);
	}
}
