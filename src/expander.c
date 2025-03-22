
#include <minishell.h>

char    *search_env(t_env *env, char *key)
{
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
        {
            return (env->value);
        }
        env = env->next;
    }
    return (NULL);
}

/* void    expander(t_token *tok_lst, t_env *env_lst)
{
    char    *sub;
    char    *temp;
    char    *new_word;
    int     i, j;

    while (tok_lst)  
    {
        i = 0;
        while (tok_lst->word[i])
        {
            if (!ft_strchr(tok_lst->word, '"') && !ft_strchr(tok_lst->word, '\''))
            {
                while (tok_lst->word[i] && tok_lst->word[i] != '$')
                    i++;
                if (!tok_lst->word[i] || tok_lst->word[i] != '$')
                    break;
                j = ++i;
                while (tok_lst->word[j] && tok_lst->word[j] != ' ' && tok_lst->word[j] != '\t' && tok_lst->word[j] != '\0' && tok_lst->word[j] != '$')
                    j++;
                sub = ft_substr(tok_lst->word, i, j - i);
                temp = search_env(env_lst, sub);
                free(sub);

                if (temp)
                {
                    new_word = ft_strjoin(ft_substr(tok_lst->word, 0, i - 1), temp);
                    new_word = ft_strjoin(new_word, ft_substr(tok_lst->word, j, ft_strlen(tok_lst->word) - j));
                    free(tok_lst->word);
                    tok_lst->word = new_word;
                }
                else
                {
                    new_word = ft_substr(tok_lst->word, 0, i - 1);
                    free(tok_lst->word);
                    tok_lst->word = new_word;
                    i++;
                }
            }
            i++;
        }
        tok_lst = tok_lst->next;
    }
} */ 

void    replace_num(char **token, char *argv)
{
    char    *temp;
    char    *joined;

    if ((*token)[1] == '0')
        temp = ft_strdup(argv);
    else
        temp = ft_strdup("");
    if(!temp)
        return ;
    joined = ft_strjoin(temp, *token + 2);
    free(temp);
    free(*token);
    *token = joined;
}

void replace(t_token *p, t_env *envp, char *argv)
{
    int i, j;
    char *temp, *env, *new_word;

    while (p)
    {
        if (p->type == s_quote)
        {
            p = p->next;
            continue;
        }
        i = 0;
        while (p->word[i])
        {
            if (p->word[i] == '$')
            {
                j = i + 1;
                if (ft_isdigit(p->word[j]))
                {
                    replace_num(&p->word, argv);
                    break;
                }
                while (p->word[j] || p->word[j] == '_')
                    j++;
                if (j == i + 1)
                {
                    i++;
                    continue;
                }
                temp = ft_substr(p->word, i + 1, j - (i + 1)); 
                env = search_env(envp, temp);  
                free(temp);
                if(!env)
                    new_word = ft_strdup("");
                else
                    new_word = ft_strdup(env);
                free(p->word);
                p->word = new_word;
                i += ft_strlen(env ? env : "");
            }
            else
                i++;
        }
        p = p->next;
    }
} 

void    expander(t_token *tok_lst, t_env *env_lst, char *argv)
{
    t_token *p;

    p = NULL;
    while (tok_lst)
    {
        if (tok_lst->type == delimiter)
        {
            tok_lst = tok_lst->next;
            continue;
        }
        break_string(&p, tok_lst->word);
        replace(p, env_lst, argv);
        print_list(p);
        clear_list(&p);
        tok_lst = tok_lst->next;
    }
}
