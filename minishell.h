/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:49:25 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/06 17:34:01 by mfreixo-         ###   ########.fr       */
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
# include <sys/wait.h>

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

# define FALSE 0
# define TRUE 1

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_base
{
	char	**env;
	t_env	*env_split;
	char	**paths; //se o user der unset no path isso fica nulo e nada funciona :(
	char	*home;
	t_list	*cmds;
}	t_base;


// minishell.c
void	inthandler(int sig);
void	read_loop(void);
t_base	*base(void);

// parsing.c
int		exe_builtin(char **cmd);
void	parser(char *str);
// int     check_cmd(char *str);
char	**get_path();
void	first_parse(char *line);

//base.c
void	ini_paths(void);
void	base_free(void);

//environment.c
void	ini_env(char **env);
void	env_free(void);
t_env	*new_env(char *name, char *content);
void	delone_env(t_env *one_env);

//utils.c
void	error_message(char *cmd, char *error);

//utils_parsing.c
char	**ft_my_realloc(char **ptr, size_t size);

//builtins.c
int		cd(char *str);
void	pwd();
void	old_pwd(void);
void	print_env(void);

//env_alter.c
void	change_var(char *name, char *content);

//export.c
void	export(char *str);
void	unset(char *str);

//execute.c
int		exe_builtin(char **cmd);
int		ft_execve(char *path, char **cmd);
int		exe_cmd(char **cmd);
int		execute(char **cmds);

//second_parse.c
void	second_parse(void);

int ft_isquote(char c);

void	ft_echo(char **str);
char	*ft_strchr_valid(const char *s, int c);

#endif
