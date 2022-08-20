/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:42:29 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/06 20:28:20 by mfreixo-         ###   ########.fr       */
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
		error_message("", "parse error near `|'");
		return (0);
	}
	if (**begin == '|')
		*begin = *begin + 1;
	sub_str = ft_substr(*begin, 0, (size_t)pipe - (size_t)(*begin));
	*begin = pipe;
	ft_lstadd_back(&base()->div_pipes, ft_lstnew((void *)ft_strtrim(sub_str, " ")));
	free(sub_str);
	// printf("cmd:%s\n", (char *)ft_lstlast(base()->div_pipes)->content);
	return (1);
}


/*searchs for the pipes ignoring quotes*/
void	search_pipes(char *str) //Marta, corrigir a norminette disto
{
	char	*begin;
	char	*sub_str;
	int		pipe;
	int		back_slash;

	pipe = FALSE;
	begin = str;
	back_slash = 0;
	while (*str)
	{
		while (*str == '\\' && str++)
			back_slash++;
		if (ft_isquote(*str) && back_slash % 2 == 0)
			str = ft_strchr_valid(str + 1, *str) + 1;
		if (!str)
		{
			ft_lstclear(&base()->div_pipes, free);
			return ;
		}
		if (*str == '|')
		{
			pipe = TRUE;
			if (!parse_pipe(str, &begin)) //str = posicao do fim do comando, begin posicao do pipe ou do inicio do input
				return ;
		}
		str++;
		back_slash = 0;
	}
	if ((size_t)str - (size_t)(begin) <= 2) //Gabi, adicionei isto para termos em conta o caso de o input acabar com pipe
	{
		if(!(*(begin + 1)) || ft_isspace(*(begin + 1)))
		{
			ft_lstclear(&base()->div_pipes, free);
			return ;
		}
	}
	if (!pipe)
		sub_str = ft_substr(begin, 0, (size_t)str - (size_t)(begin));
	else
		sub_str = ft_substr(begin, 1, (size_t)str - (size_t)(begin));
	ft_lstadd_back(&base()->div_pipes, ft_lstnew((void *)ft_strtrim(sub_str, " ")));
	free(sub_str);
	// printf("cmd:%s\n", (char *)ft_lstlast(base()->div_pipes)->content);
}

// /*searchs for the pipes ignoring quotes*/
// void	search_pipes(char *str) //Marta, corrigir a norminette disto
// {
// 	char	*begin;
// 	char	*sub_str;
// 	int		pipe;

// 	pipe = FALSE;
// 	begin = str;
// 	while (*str)
// 	{
// 		if (*str == '\\')
// 		{
// 			str++;
// 			if (ft_isquote(*str))
// 				str++;
// 		}
// 		if (*str == '\"' || *str == '\'')
// 			str = ft_strchr_valid(str + 1, *str);
// 		if (!str)
// 		{
// 			ft_lstclear(&base()->div_pipes, free);
// 			return ;
// 		}
// 		if (*str == '|')
// 		{
// 			pipe = TRUE;
// 			if (!parse_pipe(str, &begin))
// 				return ;
// 		}
// 		str++;
// 	}
// 	if ((size_t)str - (size_t)(begin) <= 2) //Gabi, adicionei isto para termos em conta o caso de o input acabar com pipe
// 	{
// 		if(!(*(begin + 1)) || ft_isspace(*(begin + 1)))
// 		{
// 			ft_lstclear(&base()->div_pipes, free);
// 			return ;
// 		}
// 	}
// 	if (!pipe)
// 		sub_str = ft_substr(begin, 0, (size_t)str - (size_t)(begin));
// 	else
// 		sub_str = ft_substr(begin, 1, (size_t)str - (size_t)(begin));
// 	ft_lstadd_back(&base()->div_pipes, ft_lstnew((void *)ft_strtrim(sub_str, " ")));
// 	free(sub_str);
// 	// printf("cmd:%s\n", (char *)ft_lstlast(base()->div_pipes)->content);
// }
