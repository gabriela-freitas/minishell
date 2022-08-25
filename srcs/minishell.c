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

/*	ignores ^C and prints prompt in a new line
	and sets errnum to errno (130)
	*/
static void	inthandler(int sig)
{
	(void) sig;
	(base()->errnumb) = EOWNERDEAD;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*	reads input from terminal and executes it,
ignoring ^C and exiting with ^D */
void	read_loop(void)
{
	char	*str;

	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, inthandler);
		str = readline("minishell$: ");
		if (str == NULL)
			break ;
		if (!ft_strncmp("", str, 1))
		{
			free(str);
			continue ;
		}
		add_history(str);
		if (first_parse(str))
			second_parse();
		free(str);
	}
	free(str);
	printf("exit\n");
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	ini_base(env);
	read_loop();
	rl_clear_history();
	base_free();
	return (0);
}
