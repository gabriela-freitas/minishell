/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:23:25 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/31 16:58:23 by gafreita         ###   ########.fr       */
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

//GABI uniformizar esse erro!!
//minishell: export: `a-=b': not a valid identifier
/*	check if is a valid identifier i.e
	exists and contains only valid characters: alphanumerics and '_'*/
static int	is_valid_identifier(char	*name)
{
	if (!name || *name == '=')
	{
		(base()->errnumb) = EPERM;
		return (0);
	}
	while (*name)
	{
		if (!(ft_isalnum(*name) || *name == '_'))
		{
			(base()->errnumb) = EPERM;
			return (0);
		}
		name++;
	}
	return (1);
}

/*	adaptation of split to be used in the builtin - export
	if the first value of str is =, instead of having split[0]
	equal to whats after =, split[0] is set to ""
*/
char	**export_split(char *str)
{
	char	**split;
	char	*eq_pos;

	eq_pos = ft_strchr(str, '=');
	if (!eq_pos)
		return (NULL);
	split = malloc(sizeof(char *) * 3);
	split[0] = ft_substr(str, 0, (size_t)eq_pos - (size_t)str);
	split[1] = ft_substr(eq_pos, 1, ft_strlen(eq_pos));
	split[2] = '\0';
	if (split[0][0] == '\0' || !is_valid_identifier(split[0]))
	{
		error_message("export: `", str, "': not a valid identifier");
		base()->errnumb = 1;
		free_split(split);
		return (NULL);
	}
	return (split);
}

/*	Exports one variable to env, checks if:
	it contains =, if not does nothing,
	its a valid identifier (is_valid_identfier),
	if it's PATH or HOME it will update our minishell struct (base())
*/
static void	export_one(char *str)
{
	char	**split;

	split = export_split(str);
	if (!split)
		return ;
	change_var(split[0], split[1]);
	if (!strncmp("PATH", split[0], 5))
	{
		free(base()->paths);
		(base()->paths) = ft_split(split[1], ':');
	}
	if (!strncmp("HOME", split[0], 5))
	{
		free(base()->home);
		(base()->home) = ft_strdup(split[1]);
	}
	free_split(split);
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
