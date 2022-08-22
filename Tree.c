#include "Tree.h"

//Working with tree functions
node *create(node *root) {
    node *tmp = (node *) malloc(sizeof(node));
    tmp->parent = NULL;
    tmp->key = 50;
    tmp->balance = 0;
    tmp->left = tmp->right = NULL;
    root = tmp;
    return root;
}

node *search(node *root, int key) {
    if (!root || root->key == key) {
        return root;
    }
    if (key < root->key) {
        return search(root->left, key);
    }
    else {
        return search(root->right, key);
    }
}

info *addItemToInfoList(info *infoListHead, char *information) {
    info *tmp = (info *) malloc(sizeof(info));
    tmp->info = (char *) malloc(strlen(information) * sizeof(char));
    tmp->info = strcpy(tmp->info, information);
    tmp->next = NULL;
    info *head = infoListHead;
    while (head->next){
        head = head->next;
    }
    head->next = tmp;
    return infoListHead;
}

node *add(node *root, int key, char *information) {
    node *currentNode = root, *previousNode = NULL;
    node *unbalancedNode = NULL;
    node *newNode = (node *) malloc(sizeof(node));
    newNode->key = key;
    newNode->balance = 0;
    while (currentNode) {
        previousNode = currentNode;
        if (key < currentNode->key) {
            currentNode = currentNode->left;
        }
        else if (key > currentNode->key) {
            currentNode = currentNode->right;
        }
        else {
            break;
        }
    }
    if (!currentNode) {
        newNode->info = (info *) malloc(sizeof(info));
        newNode->info->info = (char *)malloc(strlen(information)*sizeof(char));
        newNode->info->info = strcpy(newNode->info->info, information);
        newNode->info->next = NULL;
        newNode->parent = previousNode;
        newNode->left = NULL;
        newNode->right = NULL;
        if (previousNode && key <= previousNode->key) {
            previousNode->left = newNode;
        }
        else if (previousNode) {
            previousNode->right = newNode;
        }
        recountBalance(root);
        unbalancedNode = searchUnbalancedNode(newNode); //check if new node is unbalanced
        if (unbalancedNode != NULL) {
            printf("Tree is imbalanced in %d key with %d balance factor\n", unbalancedNode->key, unbalancedNode->balance);
            balance(unbalancedNode, &root);
            recountBalance(root);
        }
        else {
            printf("Tree is balanced\n");
        }
    }
    else {
        currentNode->info = addItemToInfoList(currentNode->info, information);
    }
    return root;
}

node *findMin(node *root) {
    node *min = root->right;
    while (min->left) {
        min = min->left;
    }
    return min;
}

node *findMax(node *root) {
    node *max = root;
    while (max->right){
        max = max->right;
    }
    return max;
}

int findFurthestItem(node *root, int key) {
    if (key - findMin(root)->key >= findMax(root)->key - key){
        return findMin(root)->key;
    }
    else {
        return findMax(root)->key;
    }
}

node *extract(node *root, int key) {
    node *nodeToDelete = search(root, key);
    node *nodeToDeleteParent = nodeToDelete->parent;
    node *unbalancedNode;
    //case 1
    if (!nodeToDelete->right && !nodeToDelete->left) {
        if (nodeToDeleteParent->right == nodeToDelete) {
            nodeToDeleteParent->right = NULL;
        }
        else {
            nodeToDeleteParent->left = NULL;
        }
        free(nodeToDelete);
        recountBalance(root);
        unbalancedNode = searchUnbalancedNode(nodeToDeleteParent);
        if (unbalancedNode) {
            printf("Tree is imbalanced in %d key with %d balance factor\n", unbalancedNode->key, unbalancedNode->balance);
            balance(unbalancedNode, &root);
        }
    }
    //case 2
    else if (!nodeToDelete->left && nodeToDelete->right) {
        if (nodeToDeleteParent->right == nodeToDelete){
            nodeToDeleteParent->right = nodeToDelete->right;
        }
        else {
            nodeToDeleteParent->left = nodeToDelete->right;
        }
        free(nodeToDelete);
        recountBalance(root);
        unbalancedNode = searchUnbalancedNode(nodeToDeleteParent->left);
        if (unbalancedNode) {
            printf("Tree is imbalanced in %d key with %d balance factor\n", unbalancedNode->key, unbalancedNode->balance);
            balance(unbalancedNode, &root);
        }
    }
    //case 3
    else if (!nodeToDelete->right && nodeToDelete->left) {
        if (nodeToDeleteParent->left == nodeToDelete) {
            nodeToDeleteParent->left = nodeToDelete->left;
        }
        else {
            nodeToDeleteParent->right = nodeToDelete->left;
        }
        recountBalance(root);
        unbalancedNode = searchUnbalancedNode(nodeToDeleteParent->left);
        if (unbalancedNode) {
            printf("Tree is imbalanced in %d key with %d balance factor\n", unbalancedNode->key, unbalancedNode->balance);
            balance(unbalancedNode, &root);
        }
    }
    //case 4
    else if (nodeToDelete->right && nodeToDelete->left) {
        node *minNode = findMin(nodeToDelete);
        node *minNodeParent = minNode->parent;
        if (nodeToDeleteParent->left == nodeToDelete) {
            nodeToDeleteParent->left = minNode;
        }
        else {
            nodeToDeleteParent->right = minNode;
        }
        node* buf = nodeToDelete;
        nodeToDelete = minNode;
        minNode->right = buf->right;
        minNode->left = buf->left;
        minNode->parent = buf->parent;
        minNode->left = NULL;
        recountBalance(root);
        unbalancedNode = searchUnbalancedNode(minNodeParent);
        if (unbalancedNode) {
            printf("Tree is imbalanced in %d key with %d balance factor\n", unbalancedNode->key, unbalancedNode->balance);
            balance(unbalancedNode, &root);
        }
    }
    return root;
}

int height(node *root) {
    if (!root) {
        return 0;
    }
    else {
        return 1 + max(height(root->left), height(root->right));
    }
}

void print(node *root, int lvl) {
    if (root) {
        print(root->right, lvl + 1);
        for (int i = 0; i < lvl; i++) {
            printf(" ");
        }
        printf("%d(%d)\n", root->key, root->balance);
        print(root->left, lvl + 1);
    }
}

//Balance functions
node *searchUnbalancedNode(node *leaf) {
    while (leaf->parent) {
        leaf = leaf->parent;
        if ((leaf->balance == 2) || (leaf->balance == -2)) {
            return leaf;
        }
    }
    return NULL;
}

int calculateNodeBalance(node *item) {
    return height(item->right) - height(item->left);
}

node *rotateRight(node *rotationNode, node **root) {
    node *rotationNodeLeft = rotationNode->left;
    rotationNode->left = rotationNodeLeft->right;
    rotationNodeLeft->right = rotationNode;
    if (rotationNode->parent) {
        if (rotationNode->parent->left == rotationNode) {
            rotationNode->parent->left = rotationNodeLeft;
        } else {
            rotationNode->parent->right = rotationNode;
        }
    }
    rotationNodeLeft->parent = rotationNode->parent;
    rotationNode->parent = rotationNodeLeft;
    rotationNodeLeft->balance = calculateNodeBalance(rotationNodeLeft);
    rotationNode->balance = calculateNodeBalance(rotationNode);
    if (!rotationNodeLeft->parent) {
        *root = rotationNodeLeft;
    }
    return rotationNodeLeft;
}

node *rotateLeft(node *rotationNode, node **root) {
    node *rotationNodeRight = rotationNode->right;
    rotationNode->right = rotationNodeRight->left;
    rotationNodeRight->left = rotationNode;
    if (rotationNode->parent) {
        if (rotationNode->parent->right == rotationNode) {
            rotationNode->parent->right = rotationNodeRight;
        } else {
            rotationNode->parent->left = rotationNodeRight;
        }
    }
    rotationNodeRight->parent = rotationNode->parent;
    rotationNode->parent = rotationNodeRight;
    rotationNode->balance = calculateNodeBalance(rotationNode);
    rotationNodeRight->balance = calculateNodeBalance(rotationNodeRight);
    if (!rotationNodeRight->parent) {
        *root = rotationNodeRight;
    }
    return rotationNodeRight;
}

node *balance(node *unbalancedNode, node **root) {
    if (calculateNodeBalance(unbalancedNode) == 2) {
        if (calculateNodeBalance(unbalancedNode->right) < 0) {
            unbalancedNode->right = rotateRight(unbalancedNode->right, root);
        }
        return rotateLeft(unbalancedNode, root);
    }
    else if (calculateNodeBalance(unbalancedNode) == -2) {
        if (calculateNodeBalance(unbalancedNode->left) > 0) {
            unbalancedNode->left = rotateLeft(unbalancedNode->left, root);
        }
        return rotateRight(unbalancedNode, root);
    }
    else {
        return unbalancedNode;
    }
}

void recountBalance(node *root) {
    if (!root) {
      return;
    }
    else {
        root->balance = calculateNodeBalance(root);
        recountBalance(root->left);
        recountBalance(root->right);
    }
}












