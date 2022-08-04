/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:49:25 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/04 15:51:17 by gafreita         ###   ########.fr       */
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

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_cmds
{
	char			**cmds; //separados do pipe
	int				operator;
	struct s_args	*next;
}	t_cmds;

typedef struct s_args
{
	char			*args; //com pipe

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

// parsing.c
int		ft_isspace(char c);
int		ft_is_builtin(char *cmd);
void	parser(char *str);
int		check_cmd(char *str);
char	**get_path();
void	first_parse(char *line);

#endif
