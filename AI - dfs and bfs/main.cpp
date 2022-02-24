#include <stdio.h>
#include <deque>
#include "node.h"
#include "graph.h"

using namespace std;

void printDeque(deque<int> q) {
    for (int i = 0; i < q.size(); i++) {
        printf("%d ", q[i]);
    }
}

bool dequeContainsElement(deque<int> deque, int element) {
    for (int i = 0; i < deque.size(); i++) {
        if (deque[i] == element) return true;
    }
    return false;
}

deque<int> bfs(struct Graph* graph, int startVertex, int target) {
    deque<int> open;
    deque<int> closed;
    open.push_back(startVertex);
    while (true) {
        if (open.empty()) {
            printf_s("Target cannot be reached.\n");
            closed.clear();
            return closed;
        }
        int x = open.front();
        closed.push_back(x);
        open.pop_front();
        if (x == target) {
            printf_s("Target reached.\n");
            deque<int> path;
            path.push_back(x);
            int lastAdded = x;
            for (int i = closed.size() - 2; i >= 0; i--) {
                int v = closed[i];
                if (v == startVertex) break;
                Node* adjList = graph->adjLists[lastAdded];
                while (adjList) {
                    if (adjList->vertex == v) {
                        path.push_front(v);
                        lastAdded = v;
                        break;
                    }
                    adjList = adjList->next;
                }
            }
            return path;
        }
        Node* sons = graph->adjLists[x];
        while (sons) {
            if (!dequeContainsElement(open, sons->vertex) && !dequeContainsElement(closed, sons->vertex)) {
                open.push_back(sons->vertex);
            }
            sons = sons->next;
        }
    }
}

deque<int> dfs(struct Graph* graph, int startVertex, int target) {
    deque<int> open;
    deque<int> closed;
    open.push_back(startVertex);
    while (true) {
        if (open.empty()) {
            printf_s("Target cannot be reached.\n");
            closed.clear();
            return closed;
        }
        int x = open.front();
        closed.push_back(x);
        open.pop_front();
        if (x == target) {
            printf_s("Target reached.\n");
            deque<int> path;
            path.push_back(x);
            int lastAdded = x;
            for (int i = closed.size() - 2; i >= 0; i--) {
                int v = closed[i];
                if (v == startVertex) break;
                Node* adjList = graph->adjLists[lastAdded];
                while (adjList) {
                    if (adjList->vertex == v) {
                        path.push_front(v);
                        lastAdded = v;
                        break;
                    }
                    adjList = adjList->next;
                }
            }
            return path;
        }
        Node* sons = graph->adjLists[x];
        while (sons) {
            if (!dequeContainsElement(open, sons->vertex) && !dequeContainsElement(closed, sons->vertex)) {
                open.push_front(sons->vertex);
            }
            sons = sons->next;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        FILE* in = NULL;
        fopen_s(&in, argv[1], "r");
        if (in != NULL) {
            int vertNum = 0, v = 0, adj = 0, start = 0;
            if (!feof(in)) {
                fscanf_s(in, "%d", &vertNum);
                if (vertNum) {
                    struct Graph* graph = createGraph(vertNum);
                    while (!feof(in)) {
                        fscanf_s(in, "%d:", &v);
                        if (!start) start = v;
                        char c;
                        do {
                            fscanf_s(in, "%d", &adj);
                            fscanf_s(in, "%c", &c, 1);
                            addEdge(graph, v - 1, adj - 1);
                        } while (c != '\n');
                    }
                    fclose(in);
                    printf_s("Enter search target: ");
                    int target = 0;
                    scanf_s("%d", &target);
                    if (target) {
                        printf_s("BFS\n");
                        deque<int> path = bfs(graph, start - 1, target - 1);
                        printf_s("Path: ");
                        for (int i = 0; i < path.size(); i++) {
                            printf_s("%d ", path[i] + 1);
                        }
                        printf_s("\nDFS\n");
                        path = dfs(graph, start - 1, target - 1);
                        printf_s("Path: ");
                        for (int i = 0; i < path.size(); i++) {
                            printf_s("%d ", path[i] + 1);
                        }
                    } else {
                        printf_s("No target");
                        return 1;
                    }
                    freeGraph(graph);
                } else {
                    fclose(in);
                    printf_s("Empty graph");
                    return 1;
                }
            } else {
                fclose(in);
                printf_s("Unexpected end of file");
                return 1;
            }
        } else {
            printf_s("Cannot open file %s", argv[1]);
            return 1;
        }
    } else {
        printf_s("Usage: program.exe graph.txt\n");
        printf_s("Graph file format:\n");
        printf_s("number_of_vertices\n");
        printf_s("vertex: adjecent_vertex[, adjecent_vertex[...]]\n");
        printf_s("vertex: adjecent_vertex[, adjecent_vertex[...]]\n");
        printf_s("...\n");
        printf_s("EOF\n");
        printf_s("Notes:\n");
        printf_s("1. Vertices MUST be numbers (or single characters)");
        printf_s("2. No zeros allowed");
        printf_s("3. Vertices must be consequential and start with 1");
        return 1;
    }
    return 0;
}
