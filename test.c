#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    int data;

    struct tree *left;
    struct tree *right;
} t_tree;

t_tree *node_create(int data)
{
    t_tree *node = malloc(sizeof(t_tree));
    if (!node)
        return (NULL);
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

void    insert(t_tree **root, t_tree *node)
{
    t_tree *p = *root;
    t_tree *p2 = NULL;
    if(!*root)
    {
        *root = node;
        return;
    }
    while (p)
    {
        p2 = p;
        if (p->data > node->data)
            p = p->left;
        else if (p->data < node->data)
            p = p->right;
        else 
            return ;
    }
    if (node->data < p2->data)
        p2->left = node;
    else
        p2->right = node;
    return ;
}

void printTree(t_tree* root, int level, const char* prefix) {
    if (root == NULL) {
        return;
    }

    // Print the current node with indentation for the level
    printf("%*s%s%d\n", level * 4, "", prefix, root->data);

    // Recursively print left and right children with appropriate prefixes
    if (root->left != NULL || root->right != NULL) {
        if (root->left) {
            printTree(root->left, level + 1, "L--- ");
        } else {
            printf("%*sL--- None\n", (level + 1) * 4, "");
        }

        if (root->right) {
            printTree(root->right, level + 1, "R--- ");
        } else {
            printf("%*sR--- None\n", (level + 1) * 4, "");
        }
    }
}

int main ()
{
    int data[5]={66, 323, 15, 1120, 422};
    t_tree  *node;
    t_tree *root = NULL;
    for(int i = 0; i < 5;  i++)
    {
        node = node_create(data[i]);
        if (!node)
            return (1);
        insert(&root, node);
    }
    printTree(root, 0, "Root:");
    return (0);
}