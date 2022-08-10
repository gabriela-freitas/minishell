/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:23:25 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/10 13:14:47 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(char	*name);
static void	export_one(char *str);

/*searches for name in env, if it doesnt exist creates it and adds it to the env
if it exists changes the content for the given one*/
void	change_var(char *name, char *content)
{
	t_env	*aux;
	t_env	*last;

	aux = base()->env;
	while (aux->next)
	{
		if (!ft_strncmp(name, aux->name, ft_strlen(name)))
		{
			free(aux->content);
			aux->content = ft_strdup(content);
			return ;
		}
		else if (!aux->next->next)
			break ;
		else
			aux = aux->next;
	}
	last = new_env(name, content);
	last->next = aux->next;
	aux->next = last;
}

/*	Simulates the export builtin, with no options:
	if no args: prints the env ASCII ordenated
	export the variables, one by one
	str[0] = "export"*/
void	export(char **str)
{
	int	i;

	if (!str[1])
		export_ordenate();
	i = 0;
	while (str[++i])
		export_one(str[i]);
}

//GABI uniformizar esse erro!!
//minishell: export: `a-=b': not a valid identifier
/*	check if is a valid identifier i.e
	exists and contains only valid characters: alphanumerics and '_'*/
static int	is_valid_identifier(char	*name)
{
	if (!name)
	{
		ft_printf("minishell: export: `=': not a valid identifier\n");
		return (0);
	}
	while (*name)
	{
		if (!(ft_isalnum(*name) || *name == '_'))
		{
			ft_printf("minishell: export: : not a valid identifier\n");
			return (0);
		}
		name++;
	}
	return (1);
}

/*	Exports one variable to env, checks if:
	it contains =, if not does nothing,
	its a valid identifier (is_valid_identfier),
	if it's PATH or HOME it will update our minishell struct (base())
*/
static void	export_one(char *str)
{
	char	**split;

	if (!ft_strchr(str, '='))
		return ;
	split = ft_split(str, '=');
	if (!is_valid_identifier(split[0]))
	{
		free_split(split);
		return ;
	}
	change_var(split[0], split[1]);
	if (!strncmp("PATH", split[0], 5))
	{
		free(base()->paths);
		(base()->paths) = ft_split(split[1], ':');
	}
	if (!strncmp("HOME", split[0], 5))
	{
		free(base()->home);
		base()->home = ft_strdup(split[1]);
	}
	free(split[0]);
	free(split);
}
