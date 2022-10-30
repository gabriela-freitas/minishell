/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:50:37 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/30 23:04:55 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*checks if c is ' or "*/
int	ft_isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

/*	reallocs split to have new size	*/
static void	my_realloc(char ***split, int size)
{
	char	**new_split;
	int		i;

	new_split = malloc(sizeof(char *) * size);
	if (!new_split)
		return ;
	i = 0;
	while ((*split)[i])
	{
		new_split[i] = ft_strdup((*split)[i]);
		i++;
	}
	new_split[i] = NULL;
	free_split(*split);
	*split = new_split;
}

/*	reallocs **split to size, size, increments it by one, and adds str as
	the last element of **split */
void	add_split(char ***split, int *size, char *str)
{
	int	k;

	k = *size;
	(*split)[k] = str;
	(*split)[++k] = NULL;
	my_realloc(split, k + 2);
	*size = k++;
}

int	ft_redirec(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	add_redirec(char redir, int flag, char *file, int index)
{
	base()->pipes[index].redir = TRUE;
	if (redir == '>')
	{
		add_split(&base()->pipes[index].output, &base()->pipes[index].output_nb, file);
		if (flag == 1)
			base()->pipes[index].out_mode = O_WRONLY | O_ASYNC | O_APPEND | O_CREAT;
		else
			base()->pipes[index].out_mode = O_WRONLY | O_ASYNC | O_TRUNC | O_CREAT;
	}
	else
	{
		if (flag == 1)
		{
			base()->pipes[index].heredoc = file;
		}
		else
		{
			add_split(&base()->pipes[index].input, &base()->pipes[index].input_nb, file);
			base()->pipes[index].in_mode = O_RDONLY | O_ASYNC;
		}
	}
	return (0);
}

void	check_redirec(char *str, int i, int index)
{
	int		redir;
	int		j;
	int		begin;
	char	*file;

	j = i + 1;
	redir = 0;
	if (str[j] && ft_redirec(str[j]))
	{
		redir = 1;
		j++;
	}
	begin = j;
	while (str[j] && !ft_isspace(str[j]) && !ft_redirec(str[j]))
		j++;
	if (str[j] && str[j + 1] && ft_redirec(str[j + 1]))
	{
		file = ft_substr(str, begin, j - begin);
		add_redirec(str[i], redir, file, index);
		ft_memmove(&str[i], &str[j], ft_strlen(&str[j - 1]) + 1);
		check_redirec(str, i, index);
	}
	else if (str[j] && ft_redirec(str[j]))
	{
		file = ft_substr(str, begin, j - begin);
		add_redirec(str[i], redir, file, index);
		ft_memmove(&str[i], &str[j], ft_strlen(&str[j - 1]) + 1);
		check_redirec(str, i, index);
	}
	else if (!str[j] || ft_isspace(str[j]))
	{
		file = ft_substr(str, begin, j - begin);
		add_redirec(str[i], redir, file, index);
		ft_memmove(&str[i], &str[j], ft_strlen(&str[j - 1]) + 1);
	}
}
