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
	// char	c;
	signal(sig, SIG_IGN);
	printf("\n");
	signal(SIGINT, inthandler);
	write(1, "mini$: ", 7);
}

void	read_loop(void)
{
	char	*str;

	while (str != NULL)
	{
		write(1, "mini$: ", 7);
		signal(SIGINT, inthandler);
		str = get_next_line(0);
	}
	printf("\n");
}

int	main(void)
{
	// char	*str;
	// int		size;
	//	str = get_next_line(0);
	//	if (str)
	//	   printf("%s\n", str);
	read_loop();
	return (0);
}
