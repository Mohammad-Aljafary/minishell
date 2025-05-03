#include <minishell.h>

t_env   *create_node_env(char *key, char *value)
{
    t_env *node;

    node = malloc(sizeof(t_env));
    if (!node)
        return (NULL);
    if (key)
        node->key = ft_strdup(key);
    if (!node->key)
    {
        free(node);
        return (NULL);
    }
    if (value)
        node->value = ft_strdup(value);
    else
        node->value = ft_strdup("");
    if (!node->value)
    {
        free (node->key);
        free (node);
        return (NULL);
    }
    node->next = NULL;
    return (node);
}

void add_back_env(t_env **list, t_env *node)
{
    t_env *lst;

    if (!node)
        return;
    if (!*list)                 
    {
        *list = node;
        return;
    }
    lst = *list;
    while (lst->next)             
        lst = lst->next;
    lst->next = node;             
}

void    add_node_env(t_env **list, t_env *node, char *key)
{
    t_env   *lst;

    lst = *list;
    while (lst)
    {
        if (ft_strcmp(lst->key, key) == 0)
        {
            if (lst->value)
                free(lst->value);                 
            lst->value = ft_strdup(node->value);
            if (node->key)
                free(node->key);
            if (node->value)              
                free(node->value);              
            free(node);                     
            return;
        }
        lst = lst->next;
    }
    add_back_env(list, node);                
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

void    create_list_env(t_env **list, char **envp)
{
    int     i;
    char    **str;
    t_env   *node;

    i = -1;
    while (envp[++i])
    {
        str = ft_split(envp[i], '=');
        if (str && str[0])                                
        {
            if (str[1])
                node = create_node_env(str[0], str[1]);
            else
                node = create_node_env(str[0], "");
            if (!node)
            {
                clear_list_env(list);
                ft_free_split(str);
                return ;
            }
            add_back_env(list, node);
        }
        ft_free_split(str);
    }
}

void    create_list_exp(t_env *env, t_env **exp)
{
    t_env   *node;

    node = NULL;
    while (env)
    {
        if (env->value)
            node = create_node_env(env->key, env->value);
        else
            node = create_node_env(env->key, "");
        if (!node)
        {
            clear_list_env(exp);
            return ;
        }
        add_back_env(exp, node);
        env = env->next;
    }
}
