#pragma once
#include <GameObject.h>
class QbertObject;

class LivesObject : public StreamEngine::GameObject
{
public:
	LivesObject(std::weak_ptr<QbertObject> pQbertObject);
	void Init();
	void Render() override;
private:
	std::weak_ptr<QbertObject> m_pQbertObject;
};

