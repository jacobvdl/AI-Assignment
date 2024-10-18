#include "Pathfinding.h"

AIForGames::Node::Node()
{
}

AIForGames::Node::Node(float x, float y)
{
	position = glm::vec2(x, y);
}

void AIForGames::Node::ConnectTo(Node* other, float cost)
{
	connections.push_back(Edge(other, cost));
}
