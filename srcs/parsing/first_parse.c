/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:42:29 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/06 20:28:20 by mfreixo-         ###   ########.fr       */
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
	if (*line == '|')
	{
		error_message("", "parse error near `|'");
		return ;
	}
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
	while (ft_isspace(str[++j]))
		;
	ft_memmove((void *)str, (void *)&str[j], ft_strlen(&str[j]) + 1);
	i = -1;
	while (str[++i])
	{
		j = i;
		while (ft_isspace(str[j]) && str[j + 1] && ft_isspace(str[j + 1]))
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
		;
	if (*str == '|')
		return (0);
	return (1);
}


/*fills the commands list*/
static int	parse_pipe(char *pipe, char **begin)
{
	char			*sub_str;

	if (!check_pipes(pipe))
	{
		error_message("", "parse error near `|'");
		return (0);
	}
	if (**begin == '|')
		*begin = *begin + 1;
	sub_str = ft_substr(*begin, 0, (size_t)pipe - (size_t)(*begin));
	*begin = pipe;
	ft_lstadd_back(&base()->cmds, ft_lstnew((void *)ft_strtrim(sub_str, " ")));
	free(sub_str);
	// printf("cmd:%s\n", (char *)ft_lstlast(base()->cmds)->content);
	return (1);
}

char	*ft_strchr_valid(const char *s, int c) //se tiver o \ entao o que esta a frente vai ser ativado
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
		{
			if (s[i - 1] && s[i - 1] != '\\')
				return ((char *)&s[i]);
            else if (s[i - 1] && s[i - 2] && s[i - 2] == '\\')
                return ((char *)&s[i]);
		}
		i ++;
	}
	if (c == 0)
		return ((char *)&s[i]);
	return (0);
}

/*searchs for the pipes ignoring quotes*/
static void	search_pipes(char *str)
{
	char	*begin;
	char	*sub_str;
	int		pipe;

	pipe = FALSE; //Se nao existir pipe nenhum ignoramos a primeira letra do comando, por isso criei esta variavel
	begin = str;
	while (*str)
	{
		if (*str == '\\')
		{
			str++;
			if (ft_isquote(*str))
				str++;
		}
		if (*str == '\"' || *str == '\'')
			str = ft_strchr_valid(str + 1, *str);
		if (!str)
		{
			ft_lstclear(&base()->cmds, free);
			return ;
		}
		if (*str == '|')
		{
			pipe = TRUE;
			if (!parse_pipe(str, &begin))
				return ;
		}
		str++;
	}
	if ((size_t)str - (size_t)(begin) <= 2) //Gabi, adicionei isto para termos em conta o caso de o input acabar com pipe
	{
		if(!(*(begin + 1)) || ft_isspace(*(begin + 1)))
		{
			ft_lstclear(&base()->cmds, free);
			return ;
		}
	}
	if (!pipe)
		sub_str = ft_substr(begin, 0, (size_t)str - (size_t)(begin));
	else
		sub_str = ft_substr(begin, 1, (size_t)str - (size_t)(begin));
	ft_lstadd_back(&base()->cmds, ft_lstnew((void *)ft_strtrim(sub_str, " ")));
	free(sub_str);
	// printf("cmd:%s\n", (char *)ft_lstlast(base()->cmds)->content);
}