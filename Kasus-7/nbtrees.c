#include <stdio.h>
#include "nbtrees.h"

static int findRoot(Isi_Tree P) {
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info != '\0' && P[i].ps_pr == 0)
            return i;
    }
    return 0;
}

void Create_tree(Isi_Tree X, int Jml_Node) {
    // Initialize all nodes
    for (int i = 1; i <= jml_maks; i++) {
        X[i].info = '\0';
        X[i].ps_fs = 0;
        X[i].ps_nb = 0;
        X[i].ps_pr = 0;
    }
    if (Jml_Node <= 0) return;

    // Input node info
    for (int i = 1; i <= Jml_Node; i++) {
        printf("Info node ke-%d: ", i);
        scanf(" %c", &X[i].info);
        X[i].ps_fs = 0;
        X[i].ps_nb = 0;
        X[i].ps_pr = 0;
    }

    // Input parent-child relationships
    for (int i = 2; i <= Jml_Node; i++) {
        int parent;
        printf("Parent dari node %c (indeks): ", X[i].info);
        scanf("%d", &parent);
        X[i].ps_pr = parent;
        if (X[parent].ps_fs == 0) {
            X[parent].ps_fs = i;
        } else {
            int sibling = X[parent].ps_fs;
            while (X[sibling].ps_nb != 0) {
                sibling = X[sibling].ps_nb;
            }
            X[sibling].ps_nb = i;
        }
    }
}

boolean IsEmpty (Isi_Tree P) {
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info != '\0') return false;
    }
    return true;
}

// PreOrder traversal: Parent, fs, nb
static void PreOrderRec(Isi_Tree P, int idx) {
    if (idx == 0 || P[idx].info == '\0') return;
    printf("%c ", P[idx].info);
    PreOrderRec(P, P[idx].ps_fs);
    PreOrderRec(P, P[idx].ps_nb);
}
void PreOrder (Isi_Tree P) {
    int root = findRoot(P);
    PreOrderRec(P, root);
    printf("\n");
}

// InOrder traversal: fs, Parent, sisa anak lain
static void InOrderRec(Isi_Tree P, int idx) {
    if (idx == 0 || P[idx].info == '\0') return;
    if (P[idx].ps_fs != 0)
        InOrderRec(P, P[idx].ps_fs);
    printf("%c ", P[idx].info);
    if (P[idx].ps_fs != 0) {
        int sibling = P[P[idx].ps_fs].ps_nb;
        while (sibling != 0) {
            InOrderRec(P, sibling);
            sibling = P[sibling].ps_nb;
        }
    }
}
void InOrder (Isi_Tree P) {
    int root = findRoot(P);
    InOrderRec(P, root);
    printf("\n");
}

// PostOrder traversal: fs, nb, Parent
static void PostOrderRec(Isi_Tree P, int idx) {
    if (idx == 0 || P[idx].info == '\0') return;
    PostOrderRec(P, P[idx].ps_fs);
    PostOrderRec(P, P[idx].ps_nb);
    printf("%c ", P[idx].info);
}
void PostOrder (Isi_Tree P) {
    int root = findRoot(P);
    PostOrderRec(P, root);
    printf("\n");
}

// Level order traversal
void Level_order(Isi_Tree X, int Maks_node) {
    int queue[jml_maks+1], front = 0, rear = 0;
    int root = findRoot(X);
    if (root == 0) return;
    queue[rear++] = root;
    while (front < rear) {
        int idx = queue[front++];
        printf("%c ", X[idx].info);
        int child = X[idx].ps_fs;
        while (child != 0) {
            queue[rear++] = child;
            child = X[child].ps_nb;
        }
    }
    printf("\n");
}

void PrintTree (Isi_Tree P) {
    printf("Isi Tree:\n");
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info != '\0') {
            printf("Idx: %d, Info: %c, fs: %d, nb: %d, pr: %d\n", i, P[i].info, P[i].ps_fs, P[i].ps_nb, P[i].ps_pr);
        }
    }
}

// Search for a node with value X
boolean Search (Isi_Tree P, infotype X) {
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info == X) return true;
    }
    return false;
}

// Count number of elements
int nbElmt (Isi_Tree P) {
    int count = 0;
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info != '\0') count++;
    }
    return count;
}

// Count number of leaves
static int nbDaunRec(Isi_Tree P, int idx) {
    if (idx == 0 || P[idx].info == '\0') return 0;
    if (P[idx].ps_fs == 0) return 1;
    int count = 0;
    int child = P[idx].ps_fs;
    while (child != 0) {
        count += nbDaunRec(P, child);
        child = P[child].ps_nb;
    }
    return count;
}
int nbDaun (Isi_Tree P) {
    int root = findRoot(P);
    return nbDaunRec(P, root);
}

// Find level of node X
static int LevelRec(Isi_Tree P, int idx, infotype X, int level) {
    if (idx == 0 || P[idx].info == '\0') return -1;
    if (P[idx].info == X) return level;
    int res = LevelRec(P, P[idx].ps_fs, X, level+1);
    if (res != -1) return res;
    return LevelRec(P, P[idx].ps_nb, X, level);
}
int Level (Isi_Tree P, infotype X) {
    int root = findRoot(P);
    return LevelRec(P, root, X, 0);
}

// Find depth (height) of tree
static int DepthRec(Isi_Tree P, int idx) {
    if (idx == 0 || P[idx].info == '\0') return 0;
    int maxDepth = 0;
    int child = P[idx].ps_fs;
    while (child != 0) {
        int d = DepthRec(P, child);
        if (d > maxDepth) maxDepth = d;
        child = P[child].ps_nb;
    }
    return maxDepth + 1;
}
int Depth (Isi_Tree P) {
    int root = findRoot(P);
    if (root == 0) return 0;
    return DepthRec(P, root) - 1;
}

int Max (infotype Data1, infotype Data2) {
    return (Data1 > Data2) ? Data1 : Data2;
}
