/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:49:25 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/09 18:51:13 by gafreita         ###   ########.fr       */
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
	t_env	*env;
	char	**paths;
	char	*home;
	t_list	*cmds;
}	t_base;


// minishell.c
void	read_loop(void);

//environment.c
t_env	*new_env(char *name, char *content);
void	ini_env(char **env);
void	delone_env(t_env *one_env);
void	env_free(void);

//base.c
t_base	*base(void);
void	ini_paths(void);
void	base_free(void);

// first_parsing.c
void	first_parse(char *line);

// parsing_pipes.c
void	search_pipes(char *str);

// utils_parsing.c
int		ft_isquote(char c);
char	*ft_strchr_valid(const char *s, int c);
void	my_realloc(char ***split, int size);
void	add_split(char ***split, int *size, char *str);

//second_parse.c
int		ft_special_char(char c);
void	second_parse(void);

// utils.c
int ft_special_char(char c);
char	*find_env(char	*name);

//execute.c
int		exe_cmd(char **cmd);
int		execute(char **cmds);

//export.c
void	export(char **str);
void	unset(char *str);

// pwd.c
void	pwd();
void	update_env_pwd(char	*var);





// int     check_cmd(char *str);
char	**get_path();


//utils.c
void	error_message(char *cmd, char *error);

//utils_parsing.c
void my_realloc(char ***split, int size);

//utils_env.c
char	**convert_env_list(void);

//builtins.c
int		cd(char *str);
void	print_env(void);
void	ft_exit(char **str);


//env_alter.c
void	change_var(char *name, char *content);

void	ft_echo(char **str);
char	*ft_strchr_valid(const char *s, int c);

#endif
