#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))

typedef struct AvlNode {
    int data;
    // 이 노드를 루트로 하는 subtree의 높이
    int Height;
    struct AvlNode* leftChild;
    struct AvlNode* rightChild;
} AvlNode;

AvlNode* rotateLL(AvlNode* parent);
AvlNode* rotateRR(AvlNode* parent);
AvlNode* rotateLR(AvlNode* parent);
AvlNode* rotateRL(AvlNode* parent);
AvlNode* avlAdd(AvlNode* root, int data);
AvlNode* avlDelete(AvlNode* root, int data);
void inorderTraveling(AvlNode* root);

int height(AvlNode* node) {
    if (node == NULL) {
        return -1;
    }
    return node->Height;
}

AvlNode* rotateLL(AvlNode* parent) {
    AvlNode* child = parent->leftChild;
    parent->leftChild = child->rightChild;
    child->rightChild = parent;

    parent->Height = MAX(height(parent->leftChild), height(parent->rightChild)) + 1;
    child->Height  = MAX(height(child->leftChild), parent->Height) + 1;
    return child;
}

AvlNode* rotateRR(AvlNode* parent) {
    AvlNode* child = parent->rightChild;
    parent->rightChild = child->leftChild;
    child->leftChild = parent;

    parent->Height = MAX(height(parent->leftChild), height(parent->rightChild)) + 1;
    child->Height  = MAX(parent->Height, height(child->rightChild)) + 1;
    return child;
}

AvlNode* rotateLR(AvlNode* parent) {
    parent->leftChild = rotateRR(parent->leftChild);
    return rotateLL(parent);
}

AvlNode* rotateRL(AvlNode* parent) {
    parent->rightChild = rotateLL(parent->rightChild);
    return rotateRR(parent);
}

AvlNode* avlAdd(AvlNode* root, int data) {
    if (root == NULL) {
        root = (AvlNode*)malloc(sizeof(AvlNode));
        if (root == NULL) {
            fprintf(stderr, "메모리 할당 오류\n");
            exit(1);
        }
        root->data = data;
        root->Height = 0;
        root->leftChild = root->rightChild = NULL;
        return root;
    }
    if (data < root->data) {
        root->leftChild = avlAdd(root->leftChild, data);
        if (height(root->leftChild) - height(root->rightChild) == 2) {
            if (data < root->leftChild->data) {
                // LL case
                root = rotateLL(root);
            } else {
                // LR case
                root = rotateLR(root);
            }
        }
    }
    else if (data > root->data) {
        root->rightChild = avlAdd(root->rightChild, data);
        if (height(root->rightChild) - height(root->leftChild) == 2) {
            if (data > root->rightChild->data) {
                // RR case
                root = rotateRR(root);
            } else {
                // RL case
                root = rotateRL(root);
            }
        }
    }
    else {
        printf("중복 키 삽입 오류: %d\n", data);
        exit(1);
    }

    root->Height = MAX(height(root->leftChild), height(root->rightChild)) + 1;
    return root;
}

AvlNode* findMinNode(AvlNode* node) {
    if (node == NULL) return NULL;
    while (node->leftChild != NULL) {
        node = node->leftChild;
    }
    return node;
}

AvlNode* avlDelete(AvlNode* root, int data) {
    if (root == NULL) {
        printf("키 %d를 찾을 수 없습니다.\n", data);
        return NULL;
    }

    if (data < root->data) {
        // 왼쪽 서브트리에서 삭제
        root->leftChild = avlDelete(root->leftChild, data);
        // 삭제 후 균형 검사
        if (height(root->rightChild) - height(root->leftChild) == 2) {
            // 오른쪽이 더 높으므로 RR 또는 RL
            if (height(root->rightChild->rightChild) >= height(root->rightChild->leftChild)) {
                root = rotateRR(root);
            } else {
                root = rotateRL(root);
            }
        }
    }
    else if (data > root->data) {
        // 오른쪽 서브트리에서 삭제
        root->rightChild = avlDelete(root->rightChild, data);
        // 삭제 후 균형 검사
        if (height(root->leftChild) - height(root->rightChild) == 2) {
            // 왼쪽이 더 높으므로 LL 또는 LR
            if (height(root->leftChild->leftChild) >= height(root->leftChild->rightChild)) {
                root = rotateLL(root);
            } else {
                root = rotateLR(root);
            }
        }
    }
    else {
        // 삭제할 노드를 찾음
        if (root->leftChild && root->rightChild) {
            // 양쪽 자식이 모두 있을 때: 오른쪽 서브트리에서 최소값을 찾아 대체
            AvlNode* minRight = findMinNode(root->rightChild);
            root->data = minRight->data;
            root->rightChild = avlDelete(root->rightChild, minRight->data);
            // 위에서 이미 균형 검사를 하지 않았으므로, 아래에서 한 번 더 검사
            if (height(root->leftChild) - height(root->rightChild) == 2) {
                if (height(root->leftChild->leftChild) >= height(root->leftChild->rightChild)) {
                    root = rotateLL(root);
                } else {
                    root = rotateLR(root);
                }
            }
        }
        else {
            // 자식이 하나 이하일 때
            AvlNode* temp = root;
            if (root->leftChild == NULL) {
                root = root->rightChild;
            } else {
                root = root->leftChild;
            }
            free(temp);
        }
    }

    if (root != NULL) {
        // 높이 갱신
        root->Height = MAX(height(root->leftChild), height(root->rightChild)) + 1;
    }
    return root;
}

void inorderTraveling(AvlNode* root) {
    if (root == NULL) {
        return;
    }
    inorderTraveling(root->leftChild);
    printf("%d ", root->data);
    inorderTraveling(root->rightChild);
}

int main() {
    AvlNode* root = NULL;

    root = avlAdd(root, 7);    
    root = avlAdd(root, 8);
    root = avlAdd(root, 9);
    root = avlAdd(root, 2);
    root = avlAdd(root, 1);
    root = avlAdd(root, 5);
    root = avlAdd(root, 3);
    root = avlAdd(root, 6);
    root = avlAdd(root, 4);

    inorderTraveling(root);
    printf("\nRoot node: %d (h = %d)\n", root->data, root->Height);

    root = avlDelete(root, 8);
    inorderTraveling(root);
    printf("\nRoot node: %d (h = %d)\n", root->data, root->Height);

    root = avlDelete(root, 2);
    inorderTraveling(root);
    printf("\nRoot node: %d (h = %d)\n", root->data, root->Height);
    
    return 0;
}