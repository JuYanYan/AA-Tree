/*
 |    Summary: AA Tree
 |       Date: 2019-04-24
 | Programmer: JuYan
 |    Version: 1.1
 +--------------------------------------
  MIT License

  Copyright (c) 2019 JuYan

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#include <stdio.h>
#include <stdlib.h>
#include "AATree.h"

static AATreeNode *mallocNode()
{
    AATreeNode *p;
    p = (AATreeNode*)malloc(sizeof(AATreeNode));
    return p;
}

static AATree Skew(AATree t)
{
    AATree l;
    if (t == NULL)
        return NULL;
    if (t->left == NULL)
        return t;
    if (t->left->level == t->level)
    {
        l = t->left;
        t->left = l->right;
        l->right = t;
        return l;
    }
    return t;
}

static AATree Split(AATree t)
{
    AATree r;
    if (t == NULL)
        return NULL;
    if (t->right == NULL || t->right->right == NULL)
        return t;
    if (t->right->right->level == t->level)
    {
        r = t->right;
        t->right = r->left;
        r->left = t;
        r->level++;
        return r;
    }
    return t;
}

static AATreeNode *Predecessor(AATreeNode *curNode)
{
    curNode = curNode->left;
    while (curNode->right != NULL)
    {
        curNode = curNode->right;
    }
    return curNode;
}

static AATreeNode *Successor(AATreeNode *curNode)
{
    curNode = curNode->right;
    while (curNode->left != NULL)
    {
        curNode = curNode->left;
    }
    return curNode;
}

static AATree Decrease_level(AATree t)
{
    int wdo;
    if (t->left != NULL && t->right != NULL)
    {
        wdo = __min(t->left->level, t->right->level) + 1;
        if (wdo < t->level)
        {
            t->level = wdo;
            if (t->right != NULL && wdo < t->right->level)
            {
                t->right->level = wdo;
            }
        }
    }
    return t;
}

static AATree _InsertData(AATree t, int key, const treeData *data)
{
    if (t == NULL)
    {
        t = mallocNode();                                   // A empty node, we can allocate it.
        t->key = key;
        t->data = *data;
        t->left = NULL;
        t->right = NULL;
        t->level = 1;
        return t;
    }
    else if (key < t->key)                                  // Find position to insert node.
        t->left = _InsertData(t->left, key, data);
    else if (key > t->key)
        t->right = _InsertData(t->right, key, data);
    t = Skew(t);                                            // Follow the path fron the new node to node.
    t = Split(t);                                           // We should perform the following: Skew and Split.
    return t;
}

static AATree _DeleteData(AATree t, int key)
{
    AATree m;
    if (t == NULL)
        return NULL;
    if (key < t->key)                                       // Firstly, Find the node that you want to delete.
    {
        t->left = _DeleteData(t->left, key);
    }
    else if (key > t->key)
    {
        t->right = _DeleteData(t->right, key);
    }
    else {                                                  // key == t->key
        if (t->left == NULL && t->right == NULL)            // The node has not child tree.We can remove it without other followings.
        {
            free(t);
            return NULL;                                    // Empty
        }
        if (t->left == NULL)                                // Only has it right child tree.
        {
            AATree l;
            l = Successor(t);
            t->key = l->key;                                // Exchange position.
            t->data = l->data;
            t->right = _DeleteData(t->right, l->key);       // Delete successor node.
        }
        else {
            AATree l;
            l = Predecessor(t);
            t->key = l->key;                                // Similar to the above.
            t->data = l->data;
            t->left = _DeleteData(t->left, l->key); 
        }
    }
    t = Decrease_level(t);
    t = Skew(t);
    m = t->right;
    t->right = Skew(m);
    if (m != NULL && m->right != NULL)
    {
        t->right->right = Skew(m->right);
    }
    t = Split(t);
    t->right = Split(m);
    return t;
}

extern void aat_insertData(AATree *t, int key, const treeData *data)
{
    *t = _InsertData(*t, key, data);                        // To make code simple, using a tiny function to call _InsertData.
}

extern void aat_deleteData(AATree *t, int key)
{
    *t = _DeleteData(*t, key);
}

extern void aat_searchData(AATree bst, int key, treeData **data)
{
    AATree  i;
    i = bst;
    while (i != NULL)
    {
        if (key == i->key)
        {
            *data = &(i->data);
            return;
        }
        if (key > i->key)
            i = i->right;
        else
            i = i->left;
    }
    *data = NULL;                                           // Not found.
}

extern void aat_deleteTree(AATree *t)
{
    if (*t == NULL)
        return;
    aat_deleteTree(&(*t)->left);
    aat_deleteTree(&(*t)->right);
    free(*t);
    *t = NULL;
}

extern void aat_printTree(FILE *f, AATree tree, int level)
{
    int i;
    if (!tree)
        return;
    aat_printTree(f, tree->right, level + 1);
    for (i = 0; i < level; i++)
        fprintf(f, "    ");
    fprintf(f, "%d\r\n", tree->key);
    aat_printTree(f, tree->left, level + 1);
}
