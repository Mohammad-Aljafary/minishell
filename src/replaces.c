#include <minishell.h>

int    replace_num(char **token, char *minishell_file)
{
    char    *temp;
    char    *joined;

    if ((*token)[1] == '0')
        temp = ft_strdup(minishell_file);
    else
        temp = ft_strdup("");
    if(!temp)
        return (0);
    joined = ft_strjoin(temp, *token + 2);
    free(temp);
    if (!joined)
        return (0);
    free(*token);
    *token = joined;
    return (1);
}

int     replace_exit_status(char **token, int exit_status)
{
    char    *temp;
    char    *joined;

    temp = ft_itoa(exit_status);
    if(!temp)
        return (0);
    joined = ft_strjoin(temp, *token + 2);
    free(temp);
    if (!joined)
        return (0);
    free(*token);
    *token = joined;
    return (1);
}

int replace_env (t_token *p, t_env *envp, int *i, int *j)
{
    char    *temp;
    char    *new_word;
    char    *env;

    temp = ft_substr(p->word, *i + 1, *j - (*i + 1));
    if (!temp)
        return (0); 
    env = search_env(envp, temp);  
    free(temp);
    if (!env)
        new_word = ft_strdup("");
    else
        new_word = ft_strdup(env);
    if (!new_word)
        return (0);
    free(p->word);
    p->word = new_word;
    *i += ft_strlen(env);
    p->expaneded = 1;
    return (1);
}
