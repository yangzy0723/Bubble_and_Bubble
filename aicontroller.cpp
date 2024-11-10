#include "aicontroller.h"

#include "bomb.h"
#include "fire.h"
#include "player.h"
#include "pushprop.h"
#include "hardwall.h"
#include "softwall.h"
#include "gamescene.h"
#include "speedprop.h"
#include "numplusprop.h"
#include "rangeplusprop.h"

AIController::AIController(const char* upimage_route,
                           const char* downimage_route,
                           const char* leftimage_route,
                           const char* rightimage_route,
                           GameScene* gameScene)
{
    this -> upimage_route = upimage_route;
    this -> downimage_route = downimage_route;
    this -> leftimage_route = leftimage_route;
    this -> rightimage_route = rightimage_route;
    this -> gameScene = gameScene;
}

void AIController::onAttach()
{
    this -> phy = this -> gameObject -> getComponent<Physics>();
    Q_ASSERT(phy != nullptr);
    this -> image = this -> gameObject -> getComponent<ImageTransform>();
    Q_ASSERT(image != nullptr);
    this -> collider = dynamic_cast<QGraphicsItem*>(this -> image);
    Q_ASSERT(collider != nullptr);
}

void AIController::onUpdate(float deltaTime)
{
    if(phy->get_vx()==0 && phy->get_vy()==0)
    {
        node start;
        for(int i = 0; i < 15; i++)
            for(int j = 0; j < 20; j++)
            {
                QGraphicsItem* item = gameScene -> itemAt(20+40*j,20+40*i,QTransform());
                if(item != nullptr)
                {
                    while(item->parentItem() != nullptr)
                        item = item -> parentItem();
                    auto transform = dynamic_cast<Transform *>(item);
                    auto gameObject = transform->getParentGameObject();
                    if(gameObject -> getComponent<Fire>() != nullptr)
                    {
                        for(auto items_down_fire : item -> collidingItems())
                        {
                            while (items_down_fire->parentItem() != nullptr)
                                items_down_fire = items_down_fire->parentItem();
                            auto down_fire_transform = dynamic_cast<Transform *>(items_down_fire);
                            if (down_fire_transform == nullptr)
                                continue;
                            auto down_fire_objects = down_fire_transform->getParentGameObject();
                            if(down_fire_objects -> getComponent<ImageTransform>() == this -> image)
                            {
                                start = node(i,j);
                                map[i][j] = 'P';
                                break;
                            }//记录自己的位置
                            else
                                map[i][j] = 'f';
                        }
                    }//判断火焰位置,若自己在火焰下,优先判断自己,否则判断火焰
                    else if(gameObject -> getComponent<NumPlusProp>()!= nullptr
                            ||gameObject -> getComponent<PushProp>()!= nullptr
                            ||gameObject -> getComponent<SpeedProp>()!= nullptr
                            ||gameObject -> getComponent<RangePlusProp>()!= nullptr)
                    {
                        for(auto items_down_prop : item -> collidingItems())
                        {
                            while (items_down_prop->parentItem() != nullptr)
                                items_down_prop = items_down_prop->parentItem();
                            auto down_prop_transform = dynamic_cast<Transform *>(items_down_prop);
                            if (down_prop_transform == nullptr)
                                continue;
                            auto down_prop_objects = down_prop_transform->getParentGameObject();
                            if(down_prop_objects -> getComponent<ImageTransform>() == this -> image)
                            {
                                start = node(i,j);
                                map[i][j] = 'P';
                                break;
                            }//记录自己的位置
                            else if(down_prop_objects -> getComponent<Fire>() != nullptr)
                            {
                                map[i][j] = 'f';
                                break;
                            }
                            else
                                map[i][j] = '1';
                        }
                    }//判断道具位置,若自己在道具下,优先判断自己,若火焰在道具下，优先判断火焰，否则判断道具
                    else if(gameObject -> getComponent<ImageTransform>() == this -> image)
                    {
                        start = node(i,j);
                        map[i][j] = 'P';
                    }//记录自己的位置
                    else if(gameObject -> getComponent<Player>()!=nullptr)
                        map[i][j] = 'p';                      //其他人是小写p，要追杀的
                    else if(gameObject -> getComponent<Hardwall>() != nullptr)
                        map[i][j] = 'h';
                    else if(gameObject -> getComponent<Softwall>() != nullptr)
                        map[i][j] = 's';
                    else
                        map[i][j] = ' ';
                }
            }
        for(int i = 0; i < 15; i++)
            for(int j = 0; j < 20; j++)
            {
                QGraphicsItem* item = gameScene -> itemAt(20+40*j,20+40*i,QTransform());
                if(item != nullptr)
                {
                    while(item->parentItem() != nullptr)
                        item = item -> parentItem();
                    auto transform = dynamic_cast<Transform *>(item);
                    auto gameObject = transform->getParentGameObject();
                    if(gameObject -> getComponent<Bomb>()!= nullptr)
                    {
                        int range = gameObject -> getComponent<Bomb>() ->get_bomb_range();
                        for(int k = 1; k <= range; k++)
                            if(judge_danger(i+k, j))
                                map[i+k][j] = 'd';
                        for(int k = 1; k <= range; k++)
                            if(judge_danger(i-k, j))
                                map[i-k][j] = 'd';
                        for(int k = 1; k <= range; k++)
                            if(judge_danger(i, j+k))
                                map[i][j+k] = 'd';
                        for(int k = 1; k <= range; k++)
                            if(judge_danger(i, j-k))
                                map[i][j-k] = 'd';
                        for(auto items_down_bomb : item -> collidingItems())
                        {
                            while (items_down_bomb->parentItem() != nullptr)
                                items_down_bomb = items_down_bomb->parentItem();
                            auto down_bomb_transform = dynamic_cast<Transform *>(items_down_bomb);
                            if (down_bomb_transform == nullptr)
                                continue;
                            auto down_bomb_objects = down_bomb_transform->getParentGameObject();
                            if(down_bomb_objects -> getComponent<ImageTransform>() == this -> image)
                            {
                                start = node(i,j);
                                map[i][j] = 'P';
                                break;
                            }//记录自己的位置，并把周围设置成危险区
                            else
                                map[i][j] = 'b';//d表示危险的地方，能经过，不能停留；逃跑的时候可以走，寻路的时候不能走
                        }
                    }//判断炸弹位置,若自己在炸弹下,优先判断自己,否则判断炸弹，且将炸弹四周置为不安全的位置
                }
            }//最后研究炸弹位置，是为了及时确定哪些空格有危险，哪些没有，方便寻路和逃跑

//        for(int i = 0; i < 15; i++)
//        {
//            printf("\n");
//            for(int j = 0; j < 20; j++)
//                printf("%c", map[i][j]);
//        }//打印这个扫描出来的数组

        if(!s.empty())
            set_v_and_bomb();
        else if(judge_bomb())
        {
            node goal;
            bool if_find_goal = false;
            for(int i = 0; i < 15; i++)//初始化
                for(int j = 0; j < 20; j++)
                    vis[i][j] = false;
            while (!q.empty()) q.pop();//初始化
            while (!s.empty()) s.pop();//初始化

            q.push(start);
            while(!q.empty())
            {
                node cur = q.front();
                q.pop();
                int x = cur.x;
                int y = cur.y;
                vis[x][y] = true;
                if(map[x][y] == ' ')
                {
                    if_find_goal = true;
                    goal = node(x,y);
                    break;
                }
                if (judge_escape(x+1, y))
                {
                    pre[x+1][y] = node(x, y);
                    vis[x+1][y] = true;
                    q.push(node(x+1, y));
                }
                if (judge_escape(x-1, y))
                {
                    pre[x-1][y] = node(x, y);
                    vis[x-1][y] = true;
                    q.push(node(x-1, y));
                }
                if (judge_escape(x, y-1))
                {
                    pre[x][y-1] = node(x, y);
                    vis[x][y-1] = true;
                    q.push(node(x, y-1));
                }
                if (judge_escape(x, y+1))
                {
                    pre[x][y+1] = node(x, y);
                    vis[x][y+1] = true;
                    q.push(node(x, y+1));
                }
            }
            if(if_find_goal)
            {
                while(goal.x != start.x || goal.y != start.y)
                {
                    node temp = pre[goal.x][goal.y];
                    if(goal.x - temp.x== -1)
                        s.push(0);
                    else if(goal.x - temp.x == 1)
                        s.push(1);
                    else if(goal.y-temp.y == -1)
                        s.push(2);
                    else
                        s.push(3);
                    goal = temp;
                }
            }
        }
        else
        {
            node goal;
            bool if_find_goal = false;   //初始化
            for(int i = 0; i < 15; i++)//初始化
                for(int j = 0; j < 20; j++)
                    vis[i][j] = false;
            while (!q.empty()) q.pop();//初始化
            while (!s.empty()) s.pop();//初始化

            q.push(start);
            while(!q.empty())
            {
                node cur = q.front();
                q.pop();
                int x = cur.x;
                int y = cur.y;
                vis[x][y] = true;
                if(map[x][y] == '1' || map[x][y] == 'p')
                {
                    if_find_goal = true;
                    goal = node(x,y);
                    break;
                }
                if (judge_path(x + 1, y))
                {
                    pre[x + 1][y] = node(x, y);
                    vis[x + 1][y] = true;
                    q.push(node(x + 1, y));
                }
                if (judge_path(x - 1, y))
                {
                    pre[x - 1][y] = node(x, y);
                    vis[x - 1][y] = true;
                    q.push(node(x - 1, y));
                }
                if (judge_path(x, y - 1))
                {
                    pre[x][y - 1] = node(x, y);
                    vis[x][y - 1] = true;
                    q.push(node(x, y - 1));
                }
                if (judge_path(x, y + 1))
                {
                    pre[x][y + 1] = node(x, y);
                    vis[x][y + 1] = true;
                    q.push(node(x, y + 1));
                }
            }
            if(if_find_goal)
            {
                while(goal.x != start.x || goal.y != start.y)
                {
                    node temp = pre[goal.x][goal.y];
                    if(goal.x - temp.x== -1)
                        s.push(0);
                    else if(goal.x - temp.x == 1)
                        s.push(1);
                    else if(goal.y-temp.y == -1)
                        s.push(2);
                    else
                        s.push(3);
                    goal = temp;
                }
            }
        }
    }
}

bool AIController::judge_path(int i, int j)
{
    if(vis[i][j] == true ||
            !(i >= 0 && i <= 14 && j >= 0 && j <= 19) ||
            map[i][j] == 'h' || map[i][j] == 'f'||map[i][j] == 'd')
        return false;
    return true;
}

bool AIController::judge_danger(int i, int j)
{
    if(i >= 14 || i <= 0 || j >= 19 || j <= 0||
            map[i][j] == 'h' || map[i][j] == 'p' || map[i][j] == 's' || map[i][j] == 'f')
        return false;
    else
        return true;
}

bool AIController::judge_escape(int i, int j)
{
    if((map[i][j] == ' ' || map[i][j] == 'd')&&vis[i][j] == false)
        return true;
    return false;
}


bool AIController::judge_bomb()//判断附近有没有炸弹
{
    int x = image -> x();
    int y = image -> y();

    QGraphicsItem* item = gameScene -> itemAt(x,y,QTransform());
    while(item->parentItem() != nullptr)
        item = item -> parentItem();
    auto transform = dynamic_cast<Transform *>(item);
    auto gameObject = transform->getParentGameObject();
    if(gameObject -> getComponent<Bomb>() != nullptr)
        return true;

    item = gameScene -> itemAt(x+40,y,QTransform());
    while(item->parentItem() != nullptr)
        item = item -> parentItem();
    transform = dynamic_cast<Transform *>(item);
    gameObject = transform->getParentGameObject();
    if(gameObject -> getComponent<Bomb>() != nullptr)
        return true;

    item = gameScene -> itemAt(x-40,y,QTransform());
    while(item->parentItem() != nullptr)
        item = item -> parentItem();
    transform = dynamic_cast<Transform *>(item);
    gameObject = transform->getParentGameObject();
    if(gameObject -> getComponent<Bomb>() != nullptr)
        return true;

    item = gameScene -> itemAt(x,y+40,QTransform());
    while(item->parentItem() != nullptr)
        item = item -> parentItem();
    transform = dynamic_cast<Transform *>(item);
    gameObject = transform->getParentGameObject();
    if(gameObject -> getComponent<Bomb>() != nullptr)
        return true;

    item = gameScene -> itemAt(x,y-40,QTransform());
    while(item->parentItem() != nullptr)
        item = item -> parentItem();
    transform = dynamic_cast<Transform *>(item);
    gameObject = transform->getParentGameObject();
    if(gameObject -> getComponent<Bomb>() != nullptr)
        return true;

    return false;
}

void AIController::set_v_and_bomb()
{
    if(s.top() == 0)
    {
        if(check(0))
        {
            this->gameObject->getComponent<Player>()->set_bomb();
            while (!s.empty()) s.pop();
        }
        else
        {
            this -> phy ->setVelocity(0,-2);
            this -> image -> setImage(upimage_route);
            s.pop();
        }
    }
    else if(s.top() == 1)
    {
        if(check(1))
        {
            this->gameObject->getComponent<Player>()->set_bomb();
            while (!s.empty()) s.pop();
        }
        else
        {
            this -> phy ->setVelocity(0,2);
            this -> image -> setImage(downimage_route);
            s.pop();
        }
    }
    else if(s.top() == 2)
    {
        if(check(2))
        {
            this->gameObject->getComponent<Player>()->set_bomb();
            while (!s.empty()) s.pop();
        }
        else
        {
            this -> phy ->setVelocity(-2,0);
            this -> image -> setImage(leftimage_route);
            s.pop();
        }
    }
    else
    {
        if(check(3))
        {
            this->gameObject->getComponent<Player>()->set_bomb();
            while (!s.empty()) s.pop();
        }
        else
        {
            this -> phy ->setVelocity(2,0);
            this -> image -> setImage(rightimage_route);
            s.pop();
        }
    }
}

bool AIController::check(int vec_to_be_set)
{
    int x_to_go = 0;
    int y_to_go = 0;
    if(vec_to_be_set == 0)//向上走
    {
        x_to_go=image->x();
        y_to_go=image->y()-40;
    }
    else if(vec_to_be_set == 1)
    {
        x_to_go=image->x();
        y_to_go=image->y()+40;
    }
    else if(vec_to_be_set == 2)
    {
        x_to_go=image->x()-40;
        y_to_go=image->y();
    }
    else if(vec_to_be_set == 3)
    {
        x_to_go=image->x()+40;
        y_to_go=image->y();
    }
    QGraphicsItem* item = gameScene -> itemAt(x_to_go,y_to_go,QTransform());
    while(item->parentItem() != nullptr)
        item = item -> parentItem();
    auto transform = dynamic_cast<Transform *>(item);
    auto gameObject = transform->getParentGameObject();
    if(gameObject -> getComponent<Softwall>()!=nullptr || gameObject -> getComponent<Player>() != nullptr)
        return true;
    return false;
}
