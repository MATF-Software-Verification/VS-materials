#include <stdint.h>
#include <stdlib.h>

#include <assert.h>
#include <stdio.h>

uint8_t nondet_uint8_t(void);

/* We are going to be working with (ordered) binary search trees. */

typedef struct _tree {
    uint8_t value;
    struct _tree *left;
    struct _tree *right;
} tree;

/* 1. Consider the two find functions.  Does the choice of which to
 * use effect the run-time of the prover?  If so, why?
 */

tree *find1(tree *t, uint8_t v) {
    if (t == NULL) {
        return NULL;

    } else {

        if ((v < t->value) && (t->left != NULL)) {
            return find1(t->left, v);

        } else if ((v > t->value) && (t->right != NULL)) {
            return find1(t->right, v);

        } else {
            return t;
        }
    }
}

tree *find2(tree *t, uint8_t v) {
    if (t == NULL) {
        return NULL;

    } else {
        tree *recValue;

        if ((v < t->value) && (t->left != NULL)) {
            recValue = t->left;

        } else if ((v > t->value) && (t->right != NULL)) {
            recValue = t->right;

        } else {
            return t;
        }

        return find2(recValue, v);
    }
}

/* 2. Write an insert method for the tree and prove that a fixed
 * number of insertions gives an ordered binary search tree.
 */

void insert(tree **ad_tree, int x) {
    if (*ad_tree == NULL) {
        *ad_tree = malloc(sizeof(tree));
        if (*ad_tree == NULL)
            exit(EXIT_FAILURE);
        (*ad_tree)->value = x;
        (*ad_tree)->left = (*ad_tree)->right = NULL;
        return;
    }

    // to make sure that function has tail-recursion
    tree **target_subtree_addr = NULL;

    if ((*ad_tree)->value > x)
        target_subtree_addr = &(*ad_tree)->left;
    else
        target_subtree_addr = &(*ad_tree)->right;

    return insert(target_subtree_addr, x);
}

int ordered(tree *t) {
    if (t == NULL)
        return 1;

    if (t->left != NULL) {
        if (t->left->value > t->value)
            return 0;
    }

    if (t->right != NULL) {
        if (t->right->value < t->value)
            return 0;
    }

    return ordered(t->left) && ordered(t->right);
}

void ispisi(tree *t) {
    if (t == NULL)
        return;

    ispisi(t->left);
    printf("%d ", t->value);
    ispisi(t->right);
}

void insertharness() {
    int i;
    tree *Tree = NULL;
    for (i = 0; i < 5; i++)
        insert(&Tree, nondet_uint8_t());

    // ispisi(Tree);
    assert(ordered(Tree) == 1);
}

/* 3. Write a lookup method for the tree and prove (for trees up to a
 * fixed size) that lookup only returns true when the number is
 * contained in the tree.
 */
