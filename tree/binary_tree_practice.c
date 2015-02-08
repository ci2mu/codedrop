#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node* left;
    struct node* right;
};

// void insert(struct node* head, int val); // insert a node to the binary tree
struct node* insert(struct node* head, int val);
void preorder(struct node* head);  // preorder traversal of a tree
void inorder(struct node* head);   // inorder traversal of a tree
void free_tree_node(struct node* n);  // free the space of the tree

int main() {
    struct node* h = malloc(sizeof(struct node));
    h->val = 5;
    h->left = NULL;
    h->right = NULL;
    insert(h, 2);
    insert(h, 6);
    insert(h, 1);
    insert(h, 0);
    insert(h, 3);
    //printf("%d, %d, %d", h->val, h->left->val, h->right->val);
    //preorder(h);
    inorder(h);  // should print in ascending order b/c of a binary search tree
    free_tree_node(h);
    return 0;
}

// This insert() also works, but the code is longer than the other insert()
// void insert(struct node* head, int val) {
//     if (val> head->val) {
//         if (head->right==NULL) {
//             head->right = (struct node*) malloc(sizeof(struct node));
//             head->right->val = val;
//             head->right->left = NULL;
//             head->right->right = NULL;
//         }
//         else insert(head->right, val);
//     }
//     else {
//         if (head->left==NULL) {
//             head->left = (struct node*) malloc(sizeof(struct node));
//             head->left->val = val;
//             head->left->left = NULL;
//             head->left->right = NULL;
//         }
//         else insert(head->left, val);
//     }
// }

struct node* insert(struct node* head, int val) {
    if (head==NULL) {
        struct node* p = malloc(sizeof(struct node));
        p->val = val;
        p->left = NULL;
        p->right = NULL;
        return p;
    }
    else {
        if (val > head->val) head->right = insert(head->right, val);
        else head->left = insert(head->left, val);
        return head;
    }
}

void preorder(struct node* head) {
    if (head!=NULL) {
        printf("%d, ", head->val);
        preorder(head->left);
        preorder(head->right);
    }
}

void inorder(struct node* head) {
    if (head!=NULL) {
        inorder(head->left);
        printf("%d, ", head->val);
        inorder(head->right);
    }
}

void free_tree_node(struct node* n) {
    // Free the whole tree space with DFS
    if (n==NULL) return;
    free_tree_node(n->left);
    free_tree_node(n->right);
    free(n);
}
