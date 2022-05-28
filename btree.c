#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Searching a key on a B-tree in C
#define MAX 3
#define MIN 2
#define N 100

typedef struct BTreeNode {
  int value[MAX + 1];
  int count;
  struct BTreeNode *child[MAX + 1];
}BTreeNode;

typedef struct{
    BTreeNode *root;
}BTree;

void initTree(BTree *tree){
    tree->root = NULL;
}

// Create a node
BTreeNode *createNode(int value, BTreeNode *root, BTreeNode *child) {
  BTreeNode *new = malloc(sizeof(BTreeNode));
  new->value[1] = value;
  new->count = 1;
  new->child[0] = root;
  new->child[1] = child;
  return new;
}

// Insert node
void insertNode(int value, int pos, BTreeNode *root, BTreeNode *child) {
  int j = root->count;
  while (j > pos) {
    root->value[j + 1] = root->value[j];
    root->child[j + 1] = root->child[j];
    j--;
  }
  root->value[j + 1] = value;
  root->child[j + 1] = child;
  root->count++;
}

// Split node
void splitNode(int value, int *pvalue, int pos, BTreeNode *node, BTreeNode *child, BTreeNode **newNode) {
  int median, j;

  if (pos > MIN)
    median = MIN + 1;
  else
    median = MIN;

  *newNode = malloc(sizeof(BTreeNode));
  j = median + 1;
  while (j <= MAX) {
    (*newNode)->value[j - median] = node->value[j];
    (*newNode)->child[j - median] = node->child[j];
    j++;
  }
  node->count = median;
  (*newNode)->count = MAX - median;

  if (pos <= MIN) {
    insertNode(value, pos, node, child);
  } else {
    insertNode(value, pos - median, *newNode, child);
  }
  *pvalue = node->value[node->count];
  (*newNode)->child[0] = node->child[node->count];
  node->count--;
}

// Set the value
int setValue(int value, int *pvalue, BTreeNode *node, BTreeNode **child) {
  int pos;
  if (!node) {
    *pvalue = value;
    *child = NULL;
    return 1;
  }

  if (value < node->value[1]) {
    pos = 0;
  } else {
    for (pos = node->count; (value < node->value[pos] && pos > 1); pos--);
    if (value == node->value[pos]) {
      printf("Duplicates are not permitted\n");
      return 0;
    }
  }
  if (setValue(value, pvalue, node->child[pos], child)) {
    if (node->count < MAX) {
      insertNode(*pvalue, pos, node, *child);
    } else {
      splitNode(*pvalue, pvalue, pos, node, *child, child);
      return 1;
    }
  }
  return 0;
}

// Insert the value
BTreeNode *insert(BTreeNode *root, int value) {
    int flag, i;
    BTreeNode *child;

    flag = setValue(value, &i, root, &child);
    if (flag)
        root = createNode(i, root, child);
    return root;
}

// Search node
void search(int value, int *pos, BTreeNode *root) {
  if (!root) {
    return;
  }

  if (value < root->value[1]) {
    *pos = 0;
  } else {
    for (*pos = root->count;
       (value < root->value[*pos] && *pos > 1); (*pos)--)
      ;
    if (value == root->value[*pos]) {
      printf("%d is found", value);
      return;
    }
  }
  search(value, pos, root->child[*pos]);

  return;
}

// Traverse then nodes
void printTree(BTreeNode *root) {
  int i;
  if (root) {
    for (i = 0; i < root->count; i++) {
      printTree(root->child[i]);
      printf("%d ", root->value[i + 1]);
    }
    printTree(root->child[i]);
  }
}

int main() {
    int val, ch;
    BTree tree;

    initTree(&tree);

    srand(time(NULL));
    for(int i = 0; i < N; i++)
        tree.root = insert(tree.root, rand());

    printTree(tree.root);

    printf("\n");
    search(11, &ch, tree.root);
}