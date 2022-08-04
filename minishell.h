/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:49:25 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/04 18:19:00 by gafreita         ###   ########.fr       */
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
# include <errno.h>

enum	e_builtins
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	ENV,
	EXIT,
	UNSET,
};

enum e_operators
{
	NONE,
	PIPE,
	AND,
	OR,
};

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
	char	*home;
	t_list	*cmds;
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
void	first_parse(char *line);

//base.c
void	ini_paths(void);
void	base_free(void);

//environment.c
void	ini_env(char **env);
void	env_free(void);

//cd.c
int cd(char *str);

//utils.c
void	error_message(char *cmd, char *error);

void ls();

#endif
