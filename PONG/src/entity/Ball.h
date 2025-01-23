#pragma once

#include "Entity.h"

class Ball : public Entity
{
public:
    Ball();
    void init();

    void OnUpdate(float deltaTime);
    void windowCollision();

    float getVelX();
    float getVelY();
    void setVelX(float x);
    void setVelY(float y);
    void swapVelX();
    void swapVelY();

    void setLeftCol(bool x);
    bool getLeftCol();
    void setRightCol(bool x);
    bool getRightCol();

    virtual void render(Shader& shader) override;

    float m_height = 0.1f;
private:
private:
    bool m_leftCOL, m_rightCOL;
    float m_velocityX = 1,m_velocityY= 1;
    float m_speed = 1.7f;

    float vertices[12] = {
       m_height / 2,  m_height / 2, 0.0f, // Top-right
      -m_height / 2,  m_height / 2, 0.0f, // Top-left
      -m_height / 2, -m_height / 2, 0.0f, // Bottom-left
       m_height / 2, -m_height / 2, 0.0f  // Bottom-right
    };
    unsigned int indices[6] = {
        0, 1, 2, // First triangle
        0, 2, 3  // Second triangle
    };
};

