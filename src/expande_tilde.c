
#include "../include/minishell.h"

char    *search_env(t_env *env, char *key)
{
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

char *expand_tilde_both(char *word, t_env *env, char c)
{
    char    *value;
    char    *expanded;
    
    expanded = NULL;
    if(c == '-')
        value = search_env(env, "OLDPWD");
    else if (c == '+')
        value = search_env(env, "PWD");
    if (!value)
        return (NULL);
    if (word[2] == '/')
    {
        expanded = malloc(strlen(value) + strlen(&word[2]) + 1);
        if (expanded)
        {
            ft_strlcpy(expanded, value, ft_strlen(value));
            ft_strlcat(expanded, &word[2], ft_strlen(expanded) + ft_strlen(&word[2]));
            free(value);
            return (expanded);
        }
    }
    else if (word[2] == '\0')
        if (value)
            return (strdup(value));
    return (NULL);
}

char *expand_home(char *word, t_env *env)
{
    char *value;
    char *expanded;
    int counter;
    char *sub;

    value = search_env(env, "HOME");
    if (!value)
        return (NULL);
    expanded = NULL;
    counter = 1;
    sub = NULL;
    if (word[1] && word[1] != '/')
    {
        while (word[counter] && word[counter] != '/')
            counter++;
        sub = ft_substr(word, 1, counter - 1);
        if (!sub)
            return (NULL);
        if (ft_strcmp(search_env(env, "USER"), sub) == 0)
        {
            free(sub);
            expanded = malloc(strlen(value) + strlen(&word[counter]) + 1);
            if (expanded)
            {
                ft_strlcpy(expanded, value, strlen(value) + 1);
                ft_strlcat(expanded, &word[counter], strlen(expanded) + strlen(&word[counter]) + 1);
                return (expanded);
            }
        }
        free(sub);
    }
    else
    {
        expanded = malloc(strlen(value) + strlen(&word[1]) + 1);
        if (expanded)
        {
            ft_strlcpy(expanded, value, strlen(value) + 1);
            ft_strlcat(expanded, &word[1], strlen(expanded) + strlen(&word[1]) + 1);
            return (expanded);
        }
    }
    return (NULL);
}

int   expand_tilde(t_token **token, t_env *env)
{
    char    *new_value;
    char    *tmp;

    new_value = NULL;
    tmp = NULL;
    if (ft_strchr((*token)->word, '\"') || ft_strchr((*token)->word, '\''))
        return (0);
    if (ft_strncmp((*token)->word, "~+", 2) == 0)
        new_value = expand_tilde_both((*token)->word, env, '+');
    else if (ft_strncmp((*token)->word, "~-", 2) == 0)
        new_value = expand_tilde_both((*token)->word, env, '-');
    else if (ft_strncmp((*token)->word, "~", 1) == 0)
        new_value = expand_home((*token)->word, env);
    if (new_value)
    {
        free((*token)->word);
        (*token)->word = new_value;
        return (1);
    }
    return (0);
}
