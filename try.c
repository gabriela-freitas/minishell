#include "minishell.h"
# include "libft/include/libft.h"


t_env *new_env(char *name, char *content)
{
	t_env *new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (0);
	new_env->name = ft_strdup(name);
	new_env->content = ft_strdup(content);
	new_env->next = NULL;
	return (new_env);
}

void env_append(t_env **head, t_env *add_env)
{
	t_env *aux;
    t_env *new_envi;

    new_envi = new_env(add_env->name, add_env->content);
    free(add_env->name);
    free(add_env->content);
    free(add_env);
	if (!head || !*head)
        *head = new_envi;
	else
	{
		aux = *head;
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = new_envi;
        aux->next->next = NULL;
    }
}

t_env delone_env(t_env *one_env)
{
    free(one_env->name);
	free(one_env->content);
}

t_env *ini_env(char **env)
{
    t_env   *mini_env;
    t_env   *aux_env;
    int     i;
    int     j;
    char    **split;

    split = ft_split(env[0], '=');
    mini_env = new_env(split[0], split[1]);
    free(split[0]);
    free(split[1]);
    free(split);
    i = 0;
    while (env[++i])
    {
        split = ft_split(env[i], '=');
        aux_env = new_env(split[0], ft_strchr(env[i], '='));
        env_append(&mini_env, aux_env);
        j = 0;
        while (split[j])
            free(split[j++]);
        free(split);
    }
    return (mini_env);
}

void env_clear(t_env **mini_env)
{
	t_env *aux;

    aux = (*mini_env)->next;
    while (*mini_env)
    {
        delone_env(*mini_env);
        free(*mini_env);
        (*mini_env) = aux;
        if (*mini_env)
            aux = (*mini_env)->next;
    }
}


int	main(int argc, char **argv, char **env)
{
    t_env *first_env;
    t_env *second_env;
    t_env *third_env;
    t_env *aux;
    char **split;
    int i;
    int j;



    // split = ft_split(env[0], '=');
    // first_env = new_env(split[0], split[1]);
    // free(split[0]);
    // free(split[1]);
    // free(split);

    // i = 0;
    // while (env[++i])
    // {
    //     split = ft_split(env[i], '=');
    //     aux = new_env(split[0], ft_strchr(env[i], '='));
    //     env_append(&first_env, aux);
    //     j = 0;
    //     while (split[j])
    //     {
    //         free(split[j++]);
    //     }
    //     free(split);
    // }
    // aux = first_env;
    // while (aux)
    // {
    //     printf("name = %s, content = %s\n", aux->name, aux->content);
    //     aux = aux->next;
    // }
    // printf("%d\n", i);

    // second_env = new_env("secomini_envnd", "second env content");
    // third_env = new_env("third", "third env content");
    first_env = NULL;
    first_env = ini_env(env);



    // env_append(&first_env, second_env);
    // env_append(&first_env, third_env);

    env_clear(&first_env);


    // aux = first_env->next;

    // delone_env(first_env);
    // free(first_env);

    // first_env = aux;
    // aux = first_env->next;
    // delone_env(first_env);
    // free(first_env);

    // first_env = aux;
    // aux = first_env->next;
    // delone_env(first_env);
    free(first_env);
	return (0);
}
