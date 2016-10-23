#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

const int MAX_LEVEL = 8;

struct SkipNode
{
    int key;
    int value;
    int level;
    struct SkipNode* next;
    struct SkipNode* down;
};

SkipNode* newnode(int key, int value, int level)
{
    SkipNode* node = (SkipNode*)malloc(sizeof(SkipNode));
    node->key = key;
    node->value = value;
    node->level = level;
    node->next = NULL;
    node->down = NULL;
    return node;
}

SkipNode* init_skiplist()
{
    SkipNode* top = newnode(-1, -1, MAX_LEVEL);
    SkipNode* p = top;
    for (int i = MAX_LEVEL - 1; i >= 1; --i)
    {
        p->down = newnode(-1, -1, i);
        p = p->down;
    }
    return top;
}

void insert_skiplist(SkipNode *top, SkipNode *node)
{
    SkipNode *p = top;
    SkipNode *q;
    for (int i = MAX_LEVEL; i > p->level; --i)
    {
        p = p->down;
    }
    
    // insert
    while (p->next != NULL && p->next->key < node->key)
    {
        p = p->next;
    }

    if (p->next != NULL && p->next->key == node->key)
    {
        p = p->next;
        while (p != NULL)
        {
            p->value = node->value;
            p = p->down;
        }
        return;
    }
    else
    {
        int key = node->key;
        int value = node->value;
        int level = node->level;
        SkipNode *tmp = p;

        // next ptr
        while (p != NULL)
        {
            q = newnode(key, value, level--);
            q->next = p->next;
            p->next = q;
            p = p->down;
        }
        // down ptr
        p = tmp;
        while (p->down != NULL)
        {
            p->next->down = p->down->next;
            p = p->down;
        }
    }
}

SkipNode* search_skiplist(SkipNode *top, int key)
{
    SkipNode *p = top;
    while (p != NULL)
    {
        while (p->next != NULL && p->next->key < key)
        {
            p = p->next;
        }
    
        // search in level
        if (p->next != NULL && p->next->key == key)
        {
            return p->next;
        }
        else
        {
            p = p->down;
        }
    }
    return NULL;
}

int main()
{
    int n;
    int m;
    int key;
    int value;
    int level;
    SkipNode* p;
    SkipNode* top = init_skiplist();
    
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> key >> value;
        level = rand() % MAX_LEVEL + 1;
        p = newnode(key, value, level);
        insert_skiplist(top, p);
    }

    std::cin >> m;
    for (int i = 0; i < m; ++i)
    {
        std::cin >> key;
        p = search_skiplist(top, key);
        if (p == NULL)
        {
            std::cout << key << " no value" << std::endl;
        }
        else
        {
            std::cout << key << " with value: " << p->value 
                    << " in level: " << p->level << std::endl;
        }
    }
    return 0;
}
