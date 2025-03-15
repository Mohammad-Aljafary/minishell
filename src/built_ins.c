/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 10:57:55 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/03/15 11:42:31 by taabu-fe         ###   ########.fr       */
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

int cd(char *path)
{
    int valid_dir;

    valid_dir = chdir(path);
    if (valid_dir == -1)
    {
        perror(path);
        return (1);
    }
    return (0);
}

void    exits(char *str)
{
    char n; 
    int i;

    i = 0;
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
    
    exit(n);
}

int main()
{
    int pwdd;

    pwdd = pwd();
    cd("../");
    pwd();
    exits("2aa");
    if (pwdd)
        return (1);
    return (0);
} 