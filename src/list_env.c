/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:02:52 by malja-fa          #+#    #+#             */
/*   Updated: 2025/03/08 15:57:11 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env *create_node_env(char *key, char *value)
{
    t_env *node;

    node = malloc(sizeof(t_env));
    if (!node)
        return (NULL);
    node->key = key ? ft_strdup(key) : ft_strdup("");     // Handle NULL keys
    node->value = value ? ft_strdup(value) : ft_strdup(""); // Handle NULL values
    node->next = NULL;
    return (node);
}


void add_back_env(t_env **list, t_env *node)
{
    t_env *lst;

    if (!node)                     // Protect against null node
        return;
    if (!*list)                    // Handle empty list case
    {
        *list = node;
        return;
    }
    lst = *list;
    while (lst->next)              // Traverse to last node
        lst = lst->next;
    lst->next = node;              // Link the new node
}


void    clear_list_env(t_env **list)
{
    t_env *temp;
    while (*list)
    {
        temp = *list;
        *list = (*list)->next;
        free(temp->key);      // Free the key string
        free(temp->value);    // Free the value string
        free(temp);           // Free the node itself
    }
}


void    add_node_env(t_env **list, t_env *node, char *key)
{
    t_env   *lst;

    lst = *list;
    while (lst)
    {
        if (ft_strcmp(lst->key, key) == 0)
        {
            free(lst->value);                 // Free the old value
            lst->value = ft_strdup(node->value); // Update with the new value
            free(node->key);                 // Free unused key in new node
            free(node->value);               // Free unused value in new node
            free(node);                      // Free the temporary node
            return;
        }
        lst = lst->next;
    }
    add_back_env(list, node);                // Add new node if key not found
}

void    delete_node_env(t_env **list, char *key)
{
    t_env   *lst;
    t_env   *temp;

    lst = *list;
    if (lst && ft_strcmp(lst->key, key) == 0)
    {
        *list = lst->next;
        free(lst->key);
        free(lst->value);
        free(lst);
        return;
    }
    while (lst && lst->next)
    {
        if (ft_strcmp(lst->next->key, key) == 0)
        {
            temp = lst->next;
            lst->next = temp->next;
            free(temp->key);
            free(temp->value);
            free(temp);
            return;
        }
        lst = lst->next;
    }
}


void create_list_env(t_env **list, char **envp)
{
    int     i;
    char    **str;
    t_env   *node;

    i = 0;
    while (envp[i])
    {
        str = ft_split(envp[i], '=');
        if (str && str[0])                                 // Check split success
        {
            node = create_node_env(str[0], str[1] ? str[1] : "");
            if (node)
                add_back_env(list, node);
        }
        ft_free(str);                                      // Free split array
        i++;
    }
}

void print_env_list(t_env *list)
{
    while (list)
    {
        if (list->value)
            printf("%s=%s\n", list->key, list->value);
        else
            printf("%s=\n", list->key);           // Print empty value case
        list = list->next;
    }
}
