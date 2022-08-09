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

/*	ignores ^C and prints prompt in a new line	*/
static void	inthandler(int sig)
{
	(void) sig;
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

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, inthandler);
	str = readline("minishell$: ");
	while (str != NULL)
	{
		add_history(str);
		first_parse(str);
		second_parse();
		free(str);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, inthandler);
		str = readline("minishell$: ");
	}
	free(str);
	printf("exit\n");
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	ini_env(env);
	ini_paths();
	read_loop();
	rl_clear_history();
	base_free();
	return (0);
}
