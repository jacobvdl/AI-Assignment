#pragma once
#include "NodeMap.h"
#include "Behaviour.h"
#include "PathAgent.h"
#include <raylib.h>
class Agent
{
public:
	Agent();
	Agent(NodeMap* _nm, Behaviour* _behaviour) : m_current(_behaviour), m_nm(_nm), m_color({ 255,255,0,255 }) {}
	~Agent() { delete m_current; }

	void Update(float dt);
	void Draw();
	void GoTo(glm::vec2 point);

private:
	PathAgent m_pa;
	Behaviour* m_current;
	NodeMap* m_nm;
	Color m_color;
};

