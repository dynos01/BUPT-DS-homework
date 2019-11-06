/*
 * License: GPLv3
 * BUPT DS homework: Binary tree
 * Author: Yinuo Deng <i@dyn.im>
*/

#include <cstdio>
#include <iostream>

typedef char Type;
typedef struct Node {
    Type data;
    Node *lchild, *rchild;
} Node, *BiTree;
typedef struct {
    Type *data;
    size_t size;
} Vector;

BiTree createNode(Type x);
BiTree createFromIL(Type *in, Vector level, size_t L, size_t R);
void visit(BiTree x);
void printTree(BiTree x);
void printPreOrder(BiTree x);
void printInOrder(BiTree x);
void printPostOrder(BiTree x);
void printLevelOrder(BiTree x);
unsigned getCount(BiTree x);
unsigned getHeight(BiTree x);
bool verifyOrder(BiTree x);
BiTree copyTree(BiTree x);
BiTree invertTree(BiTree x);
void deleteValue(BiTree &t, Type x);
void destroyTree(BiTree &x);

int main(void) {
    size_t size;
    scanf("%zu", &size);
    Vector level;
    Type *in = new Type[size];
    level.data = new Type[size], level.size = size;
    for (size_t i = 0; i < size; i++) std::cin >> level.data[i];
    for (size_t i = 0; i < size; i++) std::cin >> in[i];
    BiTree root = createFromIL(in, level, 0, size - 1);
    delete [] in;
    printTree(root);
    printf("Tree height: %u\n", getHeight(root));
    if (verifyOrder(root)) puts("The tree DOES satisfy the given condition.");
    else puts("The tree DOES NOT satisfy the given condition.");
    BiTree t1 = copyTree(root);
    invertTree(t1);
    puts("Copying and inverting the initial tree...");
    printTree(t1);
    printf("Please input the element to be deleted: ");
    Type x;
    std::cin >> x;
    deleteValue(root, x);
    puts("The new tree is: ");
    printTree(root);
    destroyTree(root);
    return 0;
}

BiTree createNode(Type x) {
    Node *node = new Node;
    node->lchild = node->rchild = NULL, node->data = x;
    return node;
}

BiTree createFromIL(Type *in, Vector level, size_t L, size_t R) {
    size_t size = level.size, temp;
    if (size == 0) return NULL;
    BiTree root = createNode(level.data[0]);
    for (temp = L; temp <= R && level.data[0] != in[temp]; temp++);
    Vector lLevel, rLevel;
    lLevel.data = new Type[size], rLevel.data = new Type[size];
    lLevel.size = rLevel.size = 0;
    for (size_t i = 1; i < size; i++) {
        bool isLeft = false;
        for (size_t j = L; j < temp; j++) if (level.data[i] == in[j]) {
            isLeft = true;
            break;
        }
        if (isLeft) lLevel.data[lLevel.size++] = level.data[i];
        else rLevel.data[rLevel.size++] = level.data[i];
    }
    root->lchild = createFromIL(in, lLevel, L, temp - 1);
    root->rchild = createFromIL(in, rLevel, temp + 1, R);
    return root;
}

void visit(BiTree x) {
    printf("%c ", x->data);
}

void printTree(BiTree x) {
    printf("Pre order traversal: ");
    printPreOrder(x);
    printf("\nIn order traversal: ");
    printInOrder(x);
    printf("\nPost order traversal: ");
    printPostOrder(x);
    printf("\nLevel order traversal: ");
    printLevelOrder(x);
    printf("\n");
}

void printPreOrder(BiTree x) {
    if (x == NULL) return;
    visit(x);
    printPreOrder(x->lchild);
    printPreOrder(x->rchild);
}

void printInOrder(BiTree x) {
    if (x == NULL) return;
    printInOrder(x->lchild);
    visit(x);
    printInOrder(x->rchild);
}

void printPostOrder(BiTree x) {
    if (x == NULL) return;
    printPostOrder(x->lchild);
    printPostOrder(x->rchild);
    visit(x);
}

void printLevelOrder(BiTree x) {
    if (x == NULL) return;
    BiTree *q = new BiTree[getCount(x)];
    int front = -1, rear = 0;
    q[rear] = x;
    while (front != rear) {
        front++;
        visit(q[front]);
        if (q[front]->lchild != NULL) rear++, q[rear] = q[front]->lchild;
        if (q[front]->rchild != NULL) rear++, q[rear] = q[front]->rchild;
    }
    delete [] q;
}

unsigned getCount(BiTree x) {
    if (x == NULL) return 0;
    unsigned lCount = getCount(x->lchild), rCount = getCount(x->rchild);
    return lCount + rCount + 1;
}

unsigned getHeight(BiTree x) {
    if (x == NULL) return 0;
    unsigned lHeight = getHeight(x->lchild), rHeight = getHeight(x->rchild);
    return lHeight > rHeight ? lHeight + 1 : rHeight + 1;
}

bool verifyOrder(BiTree x) {
    static bool ordered = true;
    if (x->lchild != NULL) {
        if (x->lchild->data < x->data) ordered = false;
        (void) verifyOrder(x->lchild);
    }
    if (x->rchild != NULL) {
        if (x->rchild->data < x->data) ordered = false;
        (void) verifyOrder(x->rchild);
    }
    return ordered;
}

BiTree copyTree(BiTree x) {
    if (x == NULL) return NULL;
    Node *node = new Node;
    node->lchild = copyTree(x->lchild), node->rchild = copyTree(x->rchild);
    node->data = x->data;
    return node;
}

BiTree invertTree(BiTree x) {
    if (x == NULL) return NULL;
    BiTree temp = x->lchild;
    x->lchild = invertTree(x->rchild), x->rchild = invertTree(temp);
    return x;
}

void deleteValue(BiTree &t, Type x) {
    if (t == NULL) return;
    if (t->data == x) {
        destroyTree(t), t = NULL;
        return;
    }
    deleteValue(t->lchild, x);
    deleteValue(t->rchild, x);
}

void destroyTree(BiTree &x) {
    if (x == NULL) return;
    destroyTree(x->lchild);
    destroyTree(x->rchild);
    delete x;
    x = NULL;
}