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

void	args_test(void)
{
	base()->num_pipes = 2;
	base()->pipes = malloc(sizeof(t_pipex) * base()->num_pipes);
	t_pipex *pipes = base()->pipes;


	pipes[0].cmds = malloc(sizeof (char *) * 3);
	pipes[0].cmds[0] = ft_strdup("grep");
	pipes[0].cmds[1] = ft_strdup("world");
	pipes[0].cmds[2] = NULL;
	pipes[0].heredoc = NULL;
	pipes[0].input = malloc(sizeof (char *) * 2);
	pipes[0].input[0] = ft_strdup("infile");
	pipes[0].input[1] = NULL;
	pipes[0].output = NULL;
	// pipes[0].output = malloc(sizeof (char *) * 2);
	// pipes[0].output[0] = ft_strdup("out");
	// pipes[0].output[1] = NULL;


	pipes[1].cmds = malloc(sizeof (char *) * 3);
	pipes[1].cmds[0] = ft_strdup("wc");
	pipes[1].cmds[1] = NULL;
	pipes[1].cmds[2] = NULL;
	pipes[1].heredoc = NULL;
	pipes[1].input = NULL;
	pipes[1].output = malloc(sizeof (char *) * 2);
	pipes[1].output[0] = ft_strdup("out");
	pipes[1].output[1] = NULL;
	// pipes[0].out_mode = (O_WRONLY | O_ASYNC | O_APPEND | O_CREAT);
	pipes[1].in_mode = -1;
}

void	args_clean(void)
{
	free_split(base()->pipes[0].cmds);
	free_split(base()->pipes[0].input);
	free_split(base()->pipes[0].output);
	free_split(base()->pipes[1].cmds);
	free_split(base()->pipes[1].output);
	free(base()->pipes);
	if (!access(TEMP_FILE, F_OK))
		unlink(TEMP_FILE);
}
/*	reads input from terminal and executes it,
ignoring ^C and exiting with ^D */
void	read_loop(void)
{
	char	*str;

	str = NULL;
	while (1)
	{
		if (str)
			free(str);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, inthandler);
		str = readline("minishell$: ");
		if (str == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (!ft_strncmp("", str, 1))
			continue ;
		add_history(str);
		if (first_parse(str))
		{
			second_parse();
			exec_all();
		}
		// args_test();
		// exec_all();
		// args_clean();
	}
	free(str);
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
