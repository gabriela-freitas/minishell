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
#include <errno.h>



void	inthandler(int sig)
{
	(void) sig;
    printf("\n"); // Move to a new line
    rl_on_new_line(); // Regenerate the prompt on a newline
    rl_replace_line("", 0); // Clear the previous text
    rl_redisplay();
}


void	read_loop(void)
{
	char	*str;

	while (str != NULL)
	{
		//write(1, "minishell$: ", 7);
		signal(SIGQUIT, SIG_IGN); //apanha o ctrl \\*
		signal(SIGINT, inthandler);
		str = readline("minishell$:");
		free(str);
	}
	printf("\n");
}

int	main(void)
{
	read_loop();
	return (0);
}
