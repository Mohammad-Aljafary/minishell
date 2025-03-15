/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 10:57:55 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/03/15 17:07:35 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int pwd()
{
    char    *path;

    path = getcwd(NULL, 0);
    if (!path)
    {
        perror(NULL);
        return (1);
    }
    printf("%s\n", path);
    free (path);
    return (0);
}

int cd(char *path, t_env **env)
{
    char    *current;
    t_env   *node;
    
    node = *env;
    if (path == NULL)
        path = search_env(node, "HOME");    
    current = getcwd(NULL, 0);
    if (!current)
    {
        perror(NULL);
        return (1);
    }
    if (chdir(path) == -1)
    {
        perror (path);
        return 1;
    }
    while (node)
    {
        if (ft_strcmp(node->key, "OLDPWD") == 0)
            break;
        node = node->next;
    }
    if (node)
    {
        free(node->value);
        node->value = ft_strdup(current);
        free(current);
    }
    node = *env;
    while (node)
    {
        if (ft_strcmp(node->key, "PWD") == 0)
            break;
        node = node->next;
    }
    if (node)
    {
        free(node->value);
        node->value = ft_strdup(path);
    }
    return 0;
}


void    exits(char *str)
{
    int n; 
    int i;

    i = 0;
    n = ft_atoi(str);
    if (n < 0)
        i = 1;
    printf("exit\n");
    while(str[i])
    {
        if(!ft_isdigit(str[i]))
        {
            ft_fprintf(2, "%s: numeric argument required\n", str);
            exit(2);
        }
        i++;
    }
    while (n >= 256)
        n -= 256;
    while (n < 0)
        n += 256;
    exit(n);
}

int main(int argc, char **argv, char **envp)
{
    int pwdd;
    t_env *env;

    env = NULL;
    create_list_env(&env, envp);

    pwdd = pwd();
    cd("../", env);
    pwd();
    exits("2aa");
    if (pwdd)
        return (1);
    return (0);
} 