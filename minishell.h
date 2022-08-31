/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:49:25 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/31 16:47:24 by gafreita         ###   ########.fr       */
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
# include <sys/wait.h>
# include <fcntl.h>

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

/*	HOME directory is in base, because when HOME
	is unset cd ~ still goes to HOME directory
	defined in the begining

	base has paths, so it's not needed to search for PATH
	in env before executing each command
*/
typedef struct s_pipex
{
	char	***cmds;
	int		num_cmds;
}	t_pipex;

typedef struct s_base
{
	t_env	*env;
	t_list	*cmds;
	char	**paths;
	char	*home;
	char	*oldpwd;
	int		errnumb;
	t_list	*div_pipes;
	t_pipex	pipe;
}	t_base;

// minishell.c
void	read_loop(void);

//environment.c
t_env	*new_env(char *name, char *content);
void	ini_env(char **env);
void	delone_env(t_env *one_env);
void	env_free(void);

//base.c
void	ini_base(char **env);
t_base	*base(void);
void	free_command_line(void);
void	base_free(void);

// first_parsing.c
int		first_parse(char *line);

// parsing_pipes.c
int	search_pipes(char *str);

// utils_parsing.c
int		ft_isquote(char c);
char	*ft_strchr_valid(const char *s, int c);
void	my_realloc(char ***split, int size);
void	add_split(char ***split, int *size, char *str);

//second_parse.c
int		ft_special_char(char c);
void	second_parse(void);
char	*next_arg(char *str);

// utils.c
int		ft_special_char(char c);
void	command_not_found(char *cmd);

//execute.c
int		execute(char **cmds, int fd);

//export.c
void	export(char **str);
void	unset(char **cmds);

// pwd.c
void	pwd(void);
void	update_env_pwd(char	*var);

// expanding.c
void	expand_str(char *str);
void	*expand(char *str);

// int     check_cmd(char *str);
char	**get_path(void);

//utils.c
void	parse_error_message(char *cmd, char *error, int error_code);
void	error_message(char *cmd, char *arg, char *error);

//utils_parsing.c
void	my_realloc(char ***split, int size);

//utils_env.c
char	**convert_env_list(void);
void	export_ordenate(void);
char	*find_env(char	*name);
void	print_env(void);

//builtins.c
int		cd(char *str);
void	ft_exit(char **args);

//env_alter.c
void	change_var(char *name, char *content);

void	ft_echo(char **str);
char	*ft_strchr_valid(const char *s, int c);

//pipex.c
void	exec_all(void);
void	exec_pipe(int stdin_fd, int stdout_fd, int cmd, int *pipes);

//redir.c
void	ini_redir(char **str, int pipe_no);

#endif
