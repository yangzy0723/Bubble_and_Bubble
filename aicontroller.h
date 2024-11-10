#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <QGraphicsItem>

#include "physics.h"
#include "component.h"
#include "gameobject.h"
#include "imagetransform.h"


struct node
{
    int x,y;
    node(int _x, int _y)
    {
        x=_x;
        y=_y;
    }
    node(){};
};

class AIController:public Component
{
public:
    AIController(const char* upimage_route,
                 const char* downimage_route,
                 const char* leftimage_route,
                 const char* rightimage_route,
                 GameScene* gameScene);

    void onAttach() override;
    void onUpdate(float deltatime) override;

    bool judge_path(int i, int j);//寻路判断
    bool judge_danger(int i, int j);//危险判断
    bool judge_escape(int i, int j);//逃生判断
    bool judge_bomb();//找附近有没有炸弹，若有返回炸弹的爆炸范围，否则返回-1;若自己与炸弹重合，返回0

    bool check(int vec_to_be_set);//判断即将要到达的地方是不是软墙或人，可不可以炸
    void set_v_and_bomb();

private:
    char map[15][20];
    bool vis[15][20];
    node pre[15][20];
    std::queue<node> q;
    std::stack<int> s;

    Physics* phy;
    GameScene* gameScene;
    ImageTransform* image;
    QGraphicsItem *collider;
    const char* upimage_route;
    const char* downimage_route;
    const char* leftimage_route;
    const char* rightimage_route;
};

#endif // AICONTROLLER_H
