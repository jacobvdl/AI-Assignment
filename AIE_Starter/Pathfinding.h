#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace AIForGames
{

    struct Node;

    struct Edge {
        Node* target;
        float cost;


        Edge() { target = nullptr; cost = 0; }
        Edge(Node* _target, float _cost) : target(_target), cost(_cost) {}

    };

    struct Node {
        glm::vec2 position;
        std::vector<Edge> connections;
        int gScore;
        
        Node();
        Node(float x, float y);
        

        Node* previous = nullptr;

        void ConnectTo(Node* other, float cost);

    };

}
