#include <bits/stdc++.h>

bool check_if_bipartite(std::vector<std::pair<int, int> > edges) {
    struct ColoredEdge {
        int vrtx_1 = -1;
        int color_1 = -1;
        int vrtx_2 = -1;
        int color_2 = -1;
    };
    std::vector<ColoredEdge> colored_edges;
    ColoredEdge colored_edge;
    for (auto edge: edges){ 
        colored_edge.vrtx_1 = edge.first;
        colored_edge.vrtx_2 = edge.second;
        colored_edges.push_back(colored_edge);
    }

    long long unsigned int n_edges = edges.size();

    colored_edges[0].color_1 = 1;
    colored_edges[0].color_2 = 0;

    bool is_bipartite = true;

    for (long long unsigned int i = 1; i < n_edges; i++) {
        colored_edge = colored_edges[i];
        if (((colored_edge.color_1 == 0) && (colored_edge.color_2 == 0)) ||
             ((colored_edge.color_1 == 1) && (colored_edge.color_2 == 1))) {
            is_bipartite = false;
            break;
        }
        else if ((colored_edge.color_1 == -1) && (colored_edge.color_2 == -1)) {
            colored_edges[i].color_1 = 1;
            colored_edges[i].color_2 = 0;
        }
        else if (colored_edge.color_1 == -1) {
            colored_edges[i].color_1 = (colored_edge.color_2 == 0);
        }
        else if (colored_edge.color_2 == -1) {
            colored_edges[i].color_2 = (colored_edge.color_1 == 0);
        }
    }
    return is_bipartite;
}

int main(){
    std::vector<std::pair<int, int> > edges = {
        {1, 5}, {1, 7}, {1, 8}, {2, 6}, {2, 7}, 
        {3, 5}, {3, 8}, {4, 6}, {4, 7}
    };
    bool is_bipartite = check_if_bipartite(edges);
    assert(is_bipartite == true);
    std::cout << "graph is " << is_bipartite << "\n";

    std::vector<std::pair<int, int> > edges_2 = { {1, 2}, {2, 3}, {1, 3}};
    assert(check_if_bipartite(edges_2) == false);
    std::cout << "graph is " << check_if_bipartite(edges_2) << "\n";

    std::cout << "\n";
    return 0;
}

