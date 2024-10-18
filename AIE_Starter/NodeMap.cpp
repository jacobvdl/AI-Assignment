#include "NodeMap.h"
#include <glm/glm.hpp>
#include <iostream>
#include "raylib.h"

void NodeMap::Initialise(std::vector<std::string> asciiMap, int cellSize)
{
	m_cellSize = cellSize;
	const char emptySqr = '0';

	m_height = asciiMap.size();
	m_width = asciiMap[0].size();

	m_nodes = new Node * [m_width * m_height];

	for (int y = 0; y < m_height; y++) {
		std::string& line = asciiMap[y];
		if (line.size() != m_width)
			std::cout << "Mismatched line #" << y << " in ASCII map (" << line.size() << " instead of " << m_width << ")\n";

		for (int x = 0; x < m_width; x++) {
			char tile = 0 < line.size() ? line[x] : emptySqr;

			m_nodes[x + m_width * y] = tile == emptySqr ? nullptr : new Node(((float)x + 0.5f) * m_cellSize, ((float)y + 0.5f) * m_cellSize);
		}
	}

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			Node* node = GetNode(x, y);
			if (node) {
				Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
				if(nodeWest) {
					node->ConnectTo(nodeWest, 1);
					nodeWest->ConnectTo(node, 1);
				}

				Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
				if (nodeSouth) {
					node->ConnectTo(nodeSouth, 1);
					nodeSouth->ConnectTo(node, 1);
				}
			}
		}
	}
}

void NodeMap::Draw()
{
	Color cellColor;
	cellColor.a = 255;
	cellColor.r = 255;
	cellColor.g = 0;
	cellColor.b = 0;

	Color lineColor;
	lineColor.a = 255;
	lineColor.r = 0;
	lineColor.g = 255;
	lineColor.b = 0;

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			Node* node = GetNode(x, y);
			if (node == nullptr) {
				DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize),
					(int)m_cellSize - 1, (int)m_cellSize - 1, cellColor);
			}
			else {
				for (int i = 0; i < node->connections.size(); i++) {
					Node* other = node->connections[i].target;
					DrawLine((x + .5f) * m_cellSize, (y + .5f) * m_cellSize,
						(int)other->position.x, (int)other->position.y,
						lineColor);
				}
			}
		}
	}
}

std::vector<Node*> NodeMap::DijkstrasSearch(Node* startNode, Node* endNode)
{
	if (!startNode || !endNode)
		std::cerr << "NULL";


	return std::vector<Node*>();
}
