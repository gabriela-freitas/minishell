/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:50:37 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/02 09:52:46 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		parse_error_message("", "parse error near `|'", 2);
		base()->errnumb = 2;
		return (0);
	}
	if (**begin == '|')
		*begin = *begin + 1;
	sub_str = ft_substr(*begin, 0, (size_t)pipe - (size_t)(*begin));
	*begin = pipe;
	ft_lstadd_back(&base()->div_pipes,
		ft_lstnew((void *)ft_strtrim(sub_str, " ")));
	free(sub_str);
	return (1);
}

/*	Auxiliar function to make search_pipes pass the norminette */
static int	search_aux(char **str, char **begin, int *pipe)
{
	while (**str)
	{
		if (!**str)
			continue ;
		if (ft_isquote(**str))
			*str = ft_strchr(*str + 1, **str);
		if (!*str)
		{
			ft_lstclear(&base()->div_pipes, free);
			return (0);
		}
		if (**str == '|')
		{
			*pipe = TRUE;
			if (!parse_pipe(*str, begin))
				return (0);
		}
		(*str)++;
	}
	return (1);
}

/*searchs for the pipes ignoring quotes*/
int	search_pipes(char *str)
{
	char	*begin;
	char	*sub_str;
	int		pipe;

	pipe = FALSE;
	begin = str;
	if (!search_aux(&str, &begin, &pipe))
		return (0);
	if ((size_t)str - (size_t)(begin) <= 2)
	{
		if (!ft_isalpha(*begin) && (!(*(begin + 1))
				|| ft_isspace(*(begin + 1))))
		{
			ft_lstclear(&base()->div_pipes, free);
			return (0);
		}
	}
	if (!pipe)
		sub_str = ft_substr(begin, 0, (size_t)str - (size_t)(begin));
	else
		sub_str = ft_substr(begin, 1, (size_t)str - (size_t)(begin));
	ft_lstadd_back(&base()->div_pipes,
		ft_lstnew((void *)ft_strtrim(sub_str, " ")));
	free(sub_str);
	return (1);
}
