#pragma once

class particle
{
public:
    float x = 0;
    float y = 0;
    int Flag = 0;
    int ALPHA = 0;
    float speedX = 0;
    float speedY = 0;
    float ExtRate = 0;
    int aliveCount = 0;
    float gravity = 0;
    float speed = 0;
    float angle = 0;
};

class jampParticle : public particle
{
public:
    int count = 0;
    int countFlag = 0;
    void countUpdate();
};

class deathParticle : public particle
{
public:
    int deathFlag = 0;
    float speed = 0;
    float angle = 0;
};

class hanabi
{
public:
    float hX = 0;
    float hY = 0;
    int hFlag = 0;
    int hALPHA = 0;
    float hspeed = 0;
    float hangle = 0;
    int hanabiSpeed = 0;
};

//class aitemu
//{
//public:
//    float apX = 0;
//    float apY = 0;
//    int apFlag = 0;
//    int apALPHA = 0;
//    float apspeed = 0;
//    float apangle = 0;
//    int apaliveCount = 0;
//    float apgravity = 0;
//    float apExtRate = 0;
//};