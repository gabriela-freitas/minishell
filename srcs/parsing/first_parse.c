/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:42:29 by gafreita          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/03 19:45:49 by gafreita         ###   ########.fr       */
=======
/*   Updated: 2022/08/04 19:50:46 by gafreita         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_spaces(const char *str);
static int	check_pipes(const char *str);
static int	parse_pipe(char *pipe, char **begin);
static void	search_pipes(char *str);

/*Removes extra spaces outside ' ' and " "
	Checks whether the pipe is valid and
	fills the command list (base()->cmds)*/
void	first_parse(char *line)
{
	remove_spaces(line);
	search_pipes(line);
}

//remove extra spaces outside " " and ' '
static void	remove_spaces(const char *str)
{
	size_t	i;
	size_t	j;
	char	*aux;

	j = -1;
	while(ft_isspace(str[++j]));
	ft_memmove((void *)str, (void *)&str[j], ft_strlen(&str[j]) + 1);
	i = -1;
	while (str[++i])
	{
		j = i;
		while(ft_isspace(str[j]) && str[j + 1] && ft_isspace(str[j + 1]))
			j++;
		ft_memmove((void *)&str[i], (void *)&str[j], ft_strlen(&str[j]) + 1);
		if (str[i] == '\"' || str[i] == '\'')
		{
			aux = ft_strchr(&(str[i + 1]), str[i]);
			if (aux)
				i += (size_t)aux - (size_t)(&str[i]);
		}
	}
}

/*check if it's a valid pipe*/
static int	check_pipes(const char *str)
{
	while (ft_isspace(*(++str)))
	{
		if (*(str + 1) == '|')
		{
			return (0);
		}
	}
	return (1);
}

/*fills the commands list*/
static int	parse_pipe(char *pipe, char **begin)
{
	char			*sub_str;

	if (!check_pipes(pipe))
	{
		if (!check_pipes(str))
		{
			printf("parse error near `||'\n");
			return (0);
		}
			//create a new list;
	}
	if (**begin == '|')
		*begin = *begin + 1;
	sub_str = ft_substr(*begin, 0, (size_t)pipe - (size_t)(*begin));
	*begin = pipe;
	ft_lstadd_back(&base()->cmds, ft_lstnew((void *)ft_strtrim(sub_str, " ")));
	free(sub_str);
	printf("cmd:%s\n", (char *)ft_lstlast(base()->cmds)->content);
	return (1);
}

/*searchs for the pipes ignoring quotes*/
static void	search_pipes(char *str)
{
	char	*begin;
	char	*sub_str;

	begin = str;
	while (*str)
	{
		if (*str == '\"')
		{
			if (!parse_pipe(str, &begin))
				return ;
		}
		if (*str == '|')
			parse_pipe(str, begin);
		str++;
	}
	sub_str = ft_substr(begin, 1, (size_t)str - (size_t)(begin));
	ft_lstadd_back(&base()->cmds, ft_lstnew((void *)ft_strtrim(sub_str, " ")));
	free(sub_str);
	printf("cmd:%s\n", (char *)ft_lstlast(base()->cmds)->content);
}
