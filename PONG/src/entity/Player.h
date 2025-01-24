#pragma once
#include <vector>

#include "Entity.h"

enum MOVES
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

class Player : public Entity
{
public:
	Player();
	void init();

    void processInput(MOVES action,float deltaTme);
    void windowCollision();

    int getScore();
    void setScore(int x);
    void addScore();

	virtual void render(Shader& shader) override;
    float m_width = 0.03f;
    float m_height = 0.6f;
private:
    int m_score = -1; 
    float m_speed = 3;

    float vertices[12] = {
       m_width,  m_height/2, 0.0f, // Top-right
      -m_width,  m_height/2, 0.0f, // Top-left
      -m_width, -m_height/2, 0.0f, // Bottom-left
       m_width, -m_height/2, 0.0f  // Bottom-right
    };
    unsigned int m_indices[6] = {
        0, 1, 2, // First triangle
        0, 2, 3  // Second triangle
    };
};

