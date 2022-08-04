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

t_base	*base(void)
{
	static t_base	base;

	return (&base);
}

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
		first_parse(str);
		parser(str);
		free(str);
		signal(SIGQUIT, SIG_IGN); //apanha o ctrl \\*
		signal(SIGINT, inthandler);
		str = readline("minishell$: ");
	}
	free(str);
	printf("exit\n");
}

t_env *new_env(char *name, char *content)
{
	t_env *new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (0);
	new_env->name = ft_strdup(name);
	new_env->content = ft_strdup(content);
	new_env->next = NULL;
	return (new_env);
}

void env_append(t_env **head, t_env *new_env)
{
	t_env *aux;

	if (!*head)
		*head = new_env;
	else
	{
		aux = *head;
		while (aux)
		{
			aux = aux->next;
		}
		new_env->next = NULL;
		aux = new_env;
	}
}

t_env *ini_env(char **env)
{
	char	**split;
	t_env	*mini_env;
	t_env	*aux;
	int		i;

	if (env[0])
		split = ft_split(env[0], '=');
	if (split[0] && split[1])
		mini_env = new_env(split[0], split[1]);
	i = 1;
	while (env[i])
	{
		free(split);
		split = ft_split(env[i], '=');
		aux = new_env(split[0], split[1]);
		env_append(&mini_env, aux);
		free(aux->name);
		free(aux->content);
		free(aux); //criar funcao para libertar memoria de um env para nao ter estas 3 linhas no ciclo
		i++;
	}
	return (mini_env);
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;
	// t_env	*mini_env;

	// mini_env = ini_env(env);
	// while(mini_env)
	// {
	// 	printf("name = %s, content = %s\n", mini_env->name, mini_env->content);
	// 	mini_env = mini_env->next;
	// }
	read_loop();
	rl_clear_history();
	return (0);
}
