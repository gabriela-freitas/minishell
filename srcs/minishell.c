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

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, inthandler);
	str = readline("minishell$: ");
	while (str != NULL)
	{
		add_history(str);
		// first_parse(str);
		parser(str);
		free(str);
		signal(SIGQUIT, SIG_IGN); //apanha o ctrl \\*
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
	(void) env;
	t_env	*mini_env;

	mini_env = NULL;
	mini_env = ini_env(env);
	read_loop();
	rl_clear_history();
	env_clear(&mini_env);
	return (0);
}
