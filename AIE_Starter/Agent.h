#pragma once
#include "NodeMap.h"
#include "Behaviour.h"
#include "PathAgent.h"
#include <raylib.h>
#include <glm/glm.hpp>
class Agent
{
public:
	Agent();
	Agent(NodeMap* _nm, Behaviour* _behaviour) : m_current(_behaviour), m_nm(_nm), m_color({ 255,255,0,255 }) {
		m_pa.SetNodeMap(_nm);
	}
	~Agent() { delete m_current; }


	void Update(float dt);
	void Draw();
	void GoTo(glm::vec2 point);
	void SetNode(Node* n);
	void SetSpeed(float spd);
	void SetTarget(Agent* target);
	Agent* GetTarget() { return m_target; }
	PathAgent* GetPathAgent() { return &m_pa; }
	NodeMap* GetNodeMap() { return m_nm; }
	glm::vec2 GetPosition() { return m_pa.GetPosition(); }
	bool PathComplete();

private:
	PathAgent m_pa;
	Behaviour* m_current;
	NodeMap* m_nm;
	Color m_color;
	Agent* m_target;
};

