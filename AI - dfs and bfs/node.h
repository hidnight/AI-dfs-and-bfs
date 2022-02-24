#pragma once

struct Node {
    int vertex;
    struct Node* next;
};

struct Node* createNode(int v) {
    struct Node* newNode = new Node;
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}
