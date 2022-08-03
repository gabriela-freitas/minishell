/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:49:25 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/02 19:00:34 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	ENV,
	EXIT,
	UNSET,
} BUILTIN;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_base
{
	t_env	*env;
	char	**paths; //se o user der unset no path isso fica nulo e nada funciona :(
}	t_base;

// minishell.c
void	inthandler(int sig);
void	read_loop(void);

// parsing.c
int     ft_isspace(char c);
int     ft_isBuiltIn(char *cmd);
void    parser(char *str);
int     check_cmd(char *str);
char    **get_path();


//environment.c
t_env *new_env(char *name, char *content);
void env_append(t_env **head, t_env *add_env);
void delone_env(t_env *one_env);
t_env *ini_env(char **env);
void env_clear(t_env **mini_env);





#endif
