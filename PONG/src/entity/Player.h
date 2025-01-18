#pragma once
#include <vector>

#include "Entity.h"

enum MOVES
{
    UP,
    DOWN
};

class Player : public Entity
{
public:
	Player();
	void init();

    void processInput(MOVES action,float deltaTme);
	virtual void OnUpdate() override;
    void windowCollision();

	virtual void render(Shader& shader) override;
private:
    float speed = 3;
    float height = 0.6;

    float vertices[12] = {
       0.03f,  height/2, 0.0f, // Top-right
      -0.03f,  height/2, 0.0f, // Top-left
      -0.03f, -height/2, 0.0f, // Bottom-left
       0.03f, -height/2, 0.0f  // Bottom-right
    };
    unsigned int indices[6] = {
        0, 1, 2, // First triangle
        0, 2, 3  // Second triangle
    };
};

