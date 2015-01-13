

#ifndef OBJECTVIEWER_H
#define	OBJECTVIEWER_H

#include "MatrixIterator.h"
#include "Link3D.h"


template <class Type>
class ObjectViewer
{
public:
    ObjectViewer(Matrix3D<Type>*,const Type&,const Type&,bool*,int x = 0,int y = 0,int z = 2);
    ObjectViewer();
    void inspect(Link3D<Type>*,string,int);
    void inspectForward();
    void inspectBack();
    void inspectRight();
    void inspectLeft();
    void inspectDown();
    void inspectUp();
    void stepForward();
    void stepBack();
    void stepLeft();
    void stepRight();
    void printRectForward();
    void printRectBack();
    void printRectLeft();
    void printRectRight();
    void printRectAbove();
    void printRectBelow();
private:
    MatrixIterator<Type> *itt;
    MatrixIterator<Type> *location;
    int height;
    int width;
    int length;
    int *i;
    Type explodeCondition;
    Type player;
    Type emptySpace;
    string viewType(Link3D<Type>*);
    bool fall();
    bool isCounting;
    Link3D<Type> *bombs[10];
    int bombCount;
    int bombLife;
    int bombDec;
    bool tick();
    void initBomb();
    void startBomb();
    void die(string);
    bool *restart;
};

template <class Type>
ObjectViewer<Type>::ObjectViewer(Matrix3D<Type>* mat,const Type& playerType,const Type& emptySpaceType,bool *reset,int x,int y,int z)
{
    itt = mat->getIterator();
    itt->setLocation(x,y,z);
    location = new MatrixIterator<Type>(itt->getCurrent());
    location->setData(playerType);
    player = playerType;
    emptySpace = emptySpaceType;
    explodeCondition = emptySpaceType;
    height = mat -> getHeight();
    width = mat -> getWidth();
    length = mat -> getLength();
    isCounting = false;
    restart = reset;
    bombCount = 0;
    bombLife = 5;
    bombDec = 0;
    for(int i = 0;i<10;i++)
    {
        bombs[i] = NULL;
    }
}

template <class Type>
ObjectViewer<Type>::ObjectViewer()
{
    itt = NULL;
    location = NULL;
    height = 0;
    width = 0;
    length = 0;
}

template <class Type>
string ObjectViewer<Type>::viewType(Link3D<Type>* unknown)
{
    switch (unknown->type)
    {
            case WALL:
                return "wall";
            case BOMB:
                return "bomb";
            case KEY:
                return "key";
            default:
                return "empty";
    }
}

template <class Type>
void ObjectViewer<Type>::inspect(Link3D<Type>* unknown,string direction,int count)
{
    if(unknown->type != EMPTY)
        cout << "There is a " << viewType(unknown) << " "
             << count << " spaces " << direction << " of you!" << endl;
    else
        cout << "There is nothing there!" << endl;
}

template <class Type>
void ObjectViewer<Type>::inspectForward()
{
    int count = 1;
    Link3D<Type> *unknown = location->getCurrent()->infront;
    if(unknown != NULL)
    {
        while(unknown->type == EMPTY)
        {
            if(unknown->infront != NULL)
                unknown = unknown->infront;
            else
                break;
            count++;
        }
        inspect(unknown,"infront",count);
    }
    else
        cout << "End of the matrix."<< endl;
}

template <class Type>
void ObjectViewer<Type>::inspectBack()
{
    int count = 1;
    Link3D<Type> *unknown = location->getCurrent()->behind;
    if(unknown != NULL)
    {
        while(unknown->type == EMPTY)
        {
            if(unknown->behind != NULL)
                unknown = unknown->behind;
            else
                break;
            count++;
        }
        inspect(unknown,"behind",count);
    }
    else
        cout << "End of the matrix."<< endl;
}

template <class Type>
void ObjectViewer<Type>::inspectLeft()
{
    int count = 1;
    Link3D<Type> *unknown = location->getCurrent()->left;
    if(unknown != NULL)
    {
        while(unknown->type == EMPTY)
        {
            if(unknown->left != NULL)
                unknown = unknown->left;
            else
                break;
            count++;
        }
        inspect(unknown,"to the left",count);
    }
    else
        cout << "End of the matrix."<< endl;
}

template <class Type>
void ObjectViewer<Type>::inspectRight()
{
    int count = 1;
    Link3D<Type> *unknown = location->getCurrent()->right;
    if(unknown != NULL)
    {
        while(unknown->type == EMPTY)
        {
            if(unknown->right != NULL)
                unknown = unknown->right;
            else
                break;
            count++;
        }
        inspect(unknown,"to the right",count);
    }
    else
        cout << "End of the matrix."<< endl;
}

template <class Type>
void ObjectViewer<Type>::inspectUp()
{
    int count = 1;
    Link3D<Type> *unknown = location->getCurrent()->above;
    if(unknown != NULL)
    {
        while(unknown->type == EMPTY)
        {
            if(unknown->above != NULL)
                unknown = unknown->above;
            else
                break;
            count++;
        }
        inspect(unknown,"above",count);
    }
    else
        cout << "End of the matrix."<< endl;
}

template <class Type>
void ObjectViewer<Type>::inspectDown()
{
    int count = 1;
    Link3D<Type> *unknown = location->getCurrent()->below;
    if(unknown != NULL)
    {
        while(unknown->type == EMPTY)
        {
            if(unknown->below != NULL)
                unknown = unknown->below;
            else
                break;
            count++;
        }
        inspect(unknown,"below",count);
    }
    else
        cout << "End of the matrix."<< endl;
}

template <class Type>
void ObjectViewer<Type>::die(string message)
{
    char answer;
    cout << message << endl
         << "Do you want to play again?" << endl;
    while(answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N')
    {
        cin >> answer;
        if(answer == 'y' || answer == 'Y')
            *restart = true;
        else if(answer == 'n' || answer == 'N')
            exit(EXIT_SUCCESS);
    }

}

template <class Type>
bool ObjectViewer<Type>::fall()
{
    int count = 0;
    char answer;
    while(!location->hasSolidBelow())
    {
        location->setData(emptySpace);
        location->moveDown();
        count++;
    }
    if(count > 7)
        die("You fell to your death.");
    if(count > 0)
        return true;
    return false;
}

template <class Type>
bool ObjectViewer<Type>::tick(){
    if(bombCount != bombDec)
        bombLife--;
    for(int i = bombCount;i > bombDec;i--)
        if(bombs[i-1]->data != bombs[i-1]->explodeCondition)
            bombs[i-1]->countDown();
    if(bombLife == 0)
        {
            bombDec++;
            bombLife = 5;
        }

    if(location->getCurrent()->data == explodeCondition)
    {
        die("You got blown up!");
        return true;
    }
    return false;

}

template <class Type>
void ObjectViewer<Type>::initBomb()
{
    bool isCopy = true;
    if(location->hasBombInfront())
    {
        if(bombCount == bombDec)
            {
                bombs[bombCount++] = location->getCurrent()->infront;
                startBomb();
            }
        else
            for(int i = bombCount;i > bombDec;i--)
                if(bombs[i-1] != location->getCurrent()->infront)
                    isCopy = false;
                else
                {
                    isCopy = true;
                    break;
                }
        if(!isCopy)
        {
            bombs[bombCount++] = location->getCurrent()->infront;
            startBomb();
        }
    }
    if(location->hasBombBehind())
    {
        if(bombCount == bombDec)
            {
                bombs[bombCount++] = location->getCurrent()->behind;
                startBomb();
            }
        else
            for(int i = bombCount;i > bombDec;i--)
                if(bombs[i-1] != location->getCurrent()->behind)
                    isCopy = false;
                else
                {
                    isCopy = true;
                    break;
                }
        if(!isCopy)
        {
            bombs[bombCount++] = location->getCurrent()->behind;
            startBomb();
        }
    }
    if(location->hasBombLeft())
    {
        if(bombCount == bombDec)
            {
                bombs[bombCount++] = location->getCurrent()->left;
                startBomb();
            }
        else
            for(int i = bombCount;i > bombDec;i--)
                if(bombs[i-1] != location->getCurrent()->left)
                    isCopy = false;
                else
                {
                    isCopy = true;
                    break;
                }
        if(!isCopy)
        {
            bombs[bombCount++] = location->getCurrent()->left;
            startBomb();
        }
    }
    if(location->hasBombRight())
    {
        if(bombCount == bombDec)
            {
                bombs[bombCount++] = location->getCurrent()->right;
                startBomb();
            }
        else
            for(int i = bombCount;i > bombDec;i--)
                if(bombs[i-1] != location->getCurrent()->right)
                    isCopy = false;
                else
                {
                    isCopy = true;
                    break;
                }
        if(!isCopy)
        {
            bombs[bombCount++] = location->getCurrent()->right;
            startBomb();
        }
    }
    if(location->hasBombAbove())
    {
        if(bombCount == bombDec)
            {
                bombs[bombCount++] = location->getCurrent()->above;
                startBomb();
            }
        else
            for(int i = bombCount;i > bombDec;i--)
                if(bombs[i-1] != location->getCurrent()->above)
                    isCopy = false;
                else
                {
                    isCopy = true;
                    break;
                }
        if(!isCopy)
        {
            bombs[bombCount++] = location->getCurrent()->above;
            startBomb();
        }
    }
    if(location->hasBombBelow())
    {
        if(bombCount == bombDec)
        {
            bombs[bombCount++] = location->getCurrent()->below;
            startBomb();
        }
        else
            for(int i = bombCount;i > bombDec;i--)
                if(bombs[i-1] != location->getCurrent()->below)
                    isCopy = false;
                else
                {
                    isCopy = true;
                    break;
                }
        if(!isCopy)
        {
            bombs[bombCount++] = location->getCurrent()->below;
            startBomb();
        }
    }
}

template <class Type>
void ObjectViewer<Type>::startBomb()
{
    bombs[bombCount-1]->startCountDown(explodeCondition,2);
}

template <class Type>
void ObjectViewer<Type>::stepForward()
{
    if(!location->hasSolidInfront())
        {
            location->setData(emptySpace);
            location->moveForward();
            location->setData(player);
            if(fall())
                location->setData(player);
        }
    else if(!location->hasSolidAbove())
    {
        location->setData(emptySpace);
        location->moveUp();
        if(!location->hasSolidInfront())
        {
            location->moveForward();
            location->setData(player);
        }
        else
        {
            location->moveDown();
            location->setData(player);
        }
    }
    tick();
    initBomb();
}

template <class Type>
void ObjectViewer<Type>::stepBack()
{
    if(location->hasSolidBehind() == false)
    {
        location->setData(emptySpace);
        location->moveBack();
        location->setData(player);
        if(fall())
            location->setData(player);
    }
    else if(location->hasSolidAbove() == false)
    {
        location->setData(emptySpace);
        location->moveUp();
        if(location->hasSolidBehind() == false)
        {
            location->moveBack();
            location->setData(player);
        }
        else
        {
            location->moveDown();
            location->setData(player);
        }
    }
    bool tock = tick();

    initBomb();
}

template <class Type>
void ObjectViewer<Type>::stepLeft()
{
    if(location->hasSolidLeft() == false)
    {
        location->setData(emptySpace);
        location->moveLeft();
        location->setData(player);
        if(fall())
            location->setData(player);
    }
    else if(location->hasSolidAbove() == false)
    {
        location->setData(emptySpace);
        location->moveUp();
        if(location->hasSolidLeft() == false)
        {
            location->moveLeft();
            location->setData(player);
        }
        else
        {
            location->moveDown();
            location->setData(player);
        }
    }
    tick();
    initBomb();
}

template <class Type>
void ObjectViewer<Type>::stepRight()
{
    if(location->hasSolidRight() == false)
    {
        location->setData(emptySpace);
        location->moveRight();
        location->setData(player);
        if(fall())
            location->setData(player);
    }
    else if(location->hasSolidAbove() == false)
    {
        location->setData(emptySpace);
        location->moveUp();
        if(location->hasSolidRight() == false)
        {
            location->moveRight();
            location->setData(player);
        }
        else
        {
            location->moveDown();
            location->setData(player);
        }
    }
    tick();
    initBomb();
}

template <class Type>
void ObjectViewer<Type>::printRectForward()
{
    itt->setCurrent(location->getCurrent());
    itt->allUp();
    itt->allLeft();
    for(int i = 0;i<height;i++)
    {
        for(int i = 0;i<width;i++)
        {
            cout << itt->getCurrent()->data;
            cout << itt->getCurrent()->data;
            itt->moveRight();
        }
        itt->allLeft();
        itt->moveDown();
        cout << endl;
    }
}

template <class Type>
void ObjectViewer<Type>::printRectBack()
{
    itt->setCurrent(location->getCurrent());
    itt->allUp();
    itt->allRight();
    for(int i = 0;i<height;i++)
    {
        for(int i = 0;i<width;i++)
        {
            cout << itt->getCurrent()->data;
            cout << itt->getCurrent()->data;
            itt->moveLeft();
        }
        itt->allRight();
        itt->moveDown();
        cout << endl;
    }
}

template <class Type>
void ObjectViewer<Type>::printRectLeft()
{
    itt->setCurrent(location->getCurrent());
    itt->allUp();
    itt->allBack();
    for(int i = 0;i<height;i++)
    {
        for(int i = 0;i<length;i++)
        {
            cout << itt->getCurrent()->data;
            cout << itt->getCurrent()->data;
            itt->moveForward();
        }
        itt->allBack();
        itt->moveDown();
        cout << endl;
    }
}

template <class Type>
void ObjectViewer<Type>::printRectRight()
{
    itt->setCurrent(location->getCurrent());
    itt->allUp();
    itt->allForward();
    for(int i = 0;i<height;i++)
    {
        for(int i = 0;i<length;i++)
        {
            cout << itt->getCurrent()->data;
            cout << itt->getCurrent()->data;
            itt->moveBack();
        }
        itt->allForward();
        itt->moveDown();
        cout << endl;
    }
}

template <class Type>
void ObjectViewer<Type>::printRectAbove()
{
    itt->setCurrent(location->getCurrent());
    itt->allLeft();
    itt->allBack();
    for(int i = 0;i<width;i++)
    {
        for(int i = 0;i<length;i++)
        {
            cout << itt->getCurrent()->data;
            cout << itt->getCurrent()->data;
            itt->moveRight();
        }
        itt->allLeft();
        itt->moveForward();
        cout << endl;
    }
}

template <class Type>
void ObjectViewer<Type>::printRectBelow()
{
    itt->setCurrent(location->getCurrent());
    itt->allLeft();
    itt->allForward();
    for(int i = 0;i<width;i++)
    {
        for(int i = 0;i<length;i++)
        {
            cout << itt->getCurrent()->data;
            cout << itt->getCurrent()->data;
            itt->moveRight();
        }
        itt->allLeft();
        itt->moveBack();
        cout << endl;
    }
}


#endif

