#include "Entity.h"

Entity::Entity()
{
}

void Entity::setPosition(glm::vec3 pos)
{
	m_position = pos;
}

glm::vec3 Entity::getPosition()
{
	return m_position;
}
