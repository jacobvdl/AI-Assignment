#include "NodeMap.h"
#include <iostream>

void NodeMap::Initialise(std::vector<std::string> asciiMap, int cellSize)
{
	m_cellSize = cellSize;
	const char emptySq = '0';

	m_height = asciiMap.size();
	m_width = asciiMap[0].size();

	m_nodes = new Node * [m_width * m_height];

	for (int y = 0; y < m_height; y++) {
		std::string& line = asciiMap[y];

		if (line.size() != m_width)
			std::cout << "Mismatched line #" << y << " in ASCII map (" << line.size() << " instead of " << m_width << ")\n";

		for (int x = 0; x < m_width; x++) {
			char title = x < line.size() ? line[x] : emptySq;

			glm::vec2 pos = ((float)x + 0.5f) * m_cellSize;
			std::vector<Edge> connections = ((float)y + 0.5f) * m_cellSize;


			m_nodes[x + m_width * y] = title == emptySq ? nullptr


	}
}
