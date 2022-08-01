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

void	inthandler(int sig);

void	inthandler(int sig)
{
	signal(sig, SIG_IGN);
	if (sig == SIGINT)
	{
		printf("\n");
		write(1, "mini$: ", 7);
	}
	signal(SIGINT, inthandler);
	
}


void	read_loop(void)
{
	char	*str;

	while (str != NULL)
	{
		write(1, "mini$: ", 7);
		signal(SIGQUIT, inthandler);
		signal(SIGINT, inthandler);
		str = get_next_line(0);
	}
	printf("\n");
}

int	main(void)
{
	read_loop();
	printf("oioi\n");
	return (0);
}
