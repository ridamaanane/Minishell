/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:36:08 by rmaanane          #+#    #+#             */
/*   Updated: 2025/07/30 12:15:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*name_already_exist(t_env *env, char *name_of_variable)
{
	while (env)
	{
		if (ft_strcmp(name_of_variable, env->name_of_variable) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	display_export(t_env *env)
{
	if (!env)
		return (0);
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->name_of_variable, env->value);
		else
			printf("declare -x %s\n", env->name_of_variable);
		env = env->next;
	}
	return (0);
}

int	add_new_env_variable(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->name_of_variable = key;
	new->value = value;
	new->next = NULL;
	if (!(*env))
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

int	handle_export_argument(char *arg, t_env **env)
{
	int		j;
	char	*key;
	char	*value;
	t_env	*exist;

	j = 0;
	while (arg[j] && arg[j] != '=')
		j++;
	if (arg[j] != '=')
		return (0);
	key = ft_substr(arg, 0, j);
	value = ft_substr(arg, j + 1, ft_strlen(arg) - j - 1);
	exist = name_already_exist(*env, key);
	if (exist)
	{
		free(exist->value);
		exist->value = value;
		free(key);
	}
	else
	{
		if (add_new_env_variable(env, key, value))
			return (1);
	}
	return (0);
}
int is_valid_format(char *str)
{
    int i = 0;

    if (!str || !str[0])
        return (0);
    if (!(ft_isalpha(str[0]) || str[0] == '_'))
        return (0);
    while (str[i] && str[i] != '=')
    {
        if (!(ft_isalnum(str[i]) || str[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}

int	do_export(char **argv, t_env **env)
{
	int	i;
	int flag = 1;

	if (!argv[1])
	{
		if (!*env) //(par exemple: *env == NULL) check west list khawya
			return (0);
		return (display_export(*env));
	}
	i = 1;
	while (argv[i])
	{
		if (!is_valid_format(argv[i]))
		{
			write(2, "minishell: export: `", 21);
			write(2, argv[i], ft_strlen(argv[i]));
			write(2, "`: not a valid identifier\n", 27);
			flag = 0;
			i++;//go to next arg
			continue; // kat3awd while mn lowel bla matkmel 7it khasna chechiw arg tani tahowa
		}
		if (handle_export_argument(argv[i], env))
			return (1);
		i++;
	}	
	if (flag == 0)
		status_set(1);
	else
		status_set(0);
	return (status_get());
}
