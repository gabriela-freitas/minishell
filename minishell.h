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
#include <errno.h>

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

typedef enum
{
	BEGINNING,
	PIPE,
	AND,
	OR,
} OPERATORS;

# define FALSE 0
# define TRUE 1

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_args
{
	char			**cmds;
	int				operator;
	struct s_args	*next;
}	t_args;

typedef struct s_base
{
	t_env	*env;
	char	**paths; //se o user der unset no path isso fica nulo e nada funciona :(
	char	*home;
	t_args	*args;
}	t_base;

// minishell.c
void	inthandler(int sig);
void	read_loop(void);
t_base	*base(void);

// parsing.c
int     ft_isBuiltIn(char *cmd);
void    parser(char *str);
// int     check_cmd(char *str);
char    **get_path();

//base.c
void	ini_paths(void);
void	base_free(void);

//environment.c
void	ini_env(char **env);
void	env_free(void);
t_env	*new_env(char *name, char *content);
void	delone_env(t_env *one_env);


//builtins.c
int cd(char *str);
void pwd();
void old_pwd(void);
void print_env(void);

//env_alter.c
void change_var(char *name, char *content);

//export.c
void export(char *str);
void unset(char *str);

#endif
