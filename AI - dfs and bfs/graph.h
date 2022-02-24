#pragma once

struct Graph {
    int numVertices;
    struct Node** adjLists;
};

struct Graph* createGraph(int vertices) {
    struct Graph* graph = new Graph;
    if (graph != NULL) {
        graph->numVertices = vertices;
        graph->adjLists = new Node* [vertices];
        int i;
        for (i = 0; i < vertices; i++) {
            graph->adjLists[i] = NULL;
        }
    }

    return graph;
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        while (graph->adjLists[i] != NULL) {
            Node* next = graph->adjLists[i]->next;
            delete graph->adjLists[i];
            graph->adjLists[i] = next;
        }
    }
    delete[] graph->adjLists;
    delete graph;
}

// граф считается неориентированным
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}
