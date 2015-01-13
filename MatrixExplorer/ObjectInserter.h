
#ifndef OBJECTINSERTER_H
#define	OBJECTINSERTER_H

#include "MatrixIterator.h"


template <class Type>
class ObjectInserter
{
public:
    ObjectInserter(Matrix3D<Type>*,const Type&,const Type&);
    ObjectInserter();
    void insertWallLR(int height,int length,int x,int y,int z = 2);
    void insertWallFB(int height,int length,int x,int y,int z = 2);
    void insertTower(int height,int radius, int x, int y, int z = 2);
    void insertCircle(int radius,int,int,int);
    void insertFloor(int width,int length,int x,int y,int z);
    void insertFloor(int,int);
    void insertPyramid(int height,int x,int y,int z = 2);
    void insertGround(int depth,int width,int length);
    void insertStairsLR(int height,int x,int y,int z = 2);
    void insertDoor(int x,int y,int z = 2);
    void insertLockedDoor(int x,int y,int z = 2);
    void insertRoom(int width,int height,int length,int x,int y,int z = 2);
    void insertBomb(int x,int y, int z = 2,int timer = 5);
    void insertKey(const Type& comp,int x,int y,int z = 2);
private:
    MatrixIterator<Type> *itt;
    Type composition;
    Type space;
};

template <class Type>
ObjectInserter<Type>::ObjectInserter(Matrix3D<Type>* mat,const Type& comp,const Type& emptySpace)
{
    itt = mat->getIterator();
    composition = comp;
    space = emptySpace;
}

template <class Type>
ObjectInserter<Type>::ObjectInserter()
{
    itt = NULL;
}

template <class Type>
void ObjectInserter<Type>::insertWallLR(int height,int length,int x,int y,int z)
{
    itt->setLocation(x,y,z);
    for(int i = 0;i<length;i++)
    {
        itt->setData(composition,true,WALL);
        for(int j = 0;j<height-1;j++)
        {
            itt->moveUp();
            itt->setData(composition,true,WALL);
        }
        for(int k = 0;k<height-1;k++)
            itt->moveDown();
        itt->moveRight();
    }
}

template <class Type>
void ObjectInserter<Type>::insertWallFB(int height,int length,int x,int y,int z)
{
    itt->setLocation(x,y,z);
    for(int i = 0;i<length;i++)
    {
        itt->setData(composition,true,WALL);
        for(int j = 0;j<height-1;j++)
        {
            itt->moveUp();
            itt->setData(composition,true,WALL);
        }
        for(int k = 0;k<height-1;k++)
            itt->moveDown();
        itt->moveBack();
    }
}

template <class Type>
void ObjectInserter<Type>::insertTower(int height, int radius, int x, int y, int z)
{
    itt->setLocation(x,y,z);
    for(int i = 0;i<height;i++)
        insertCircle(radius,x,y,z+i);
}

template <class Type>
void ObjectInserter<Type>::insertCircle(int radius,int x,int y,int z)
{
    int length = 2*radius-1;
    itt->setLocation(x,y,z);
    insertFloor(length,length);
    itt->setLocation(x,y,z);
    if(radius == 2 || radius == 3)
    {
        itt->setData(space,false,EMPTY);
        for(int j = 0;j<length-1;j++)
            itt->moveRight();
        itt->setData(space,false,EMPTY);
        for(int j = 0;j<length-1;j++)
            itt->moveForward();
        itt->setData(space,false,EMPTY);
        for(int j = 0;j<length-1;j++)
            itt->moveLeft();
        itt->setData(space,false,EMPTY);
    }
    else if(radius == 4 || radius == 5)
    {
        itt->setData(space,false,EMPTY);
        itt->moveForward();
        itt->setData(space,false,EMPTY);
        itt->moveBack();
        itt->moveRight();
        itt->setData(space,false,EMPTY);
        for(int j = 0;j<length-3;j++)
            itt->moveRight();
        itt->setData(space,false,EMPTY);
        itt->moveRight();
        itt->setData(space,false,EMPTY);
        itt->moveForward();
        itt->setData(space,false,EMPTY);
        for(int j = 0;j<length-3;j++)
            itt->moveForward();
        itt->setData(space,false,EMPTY);
        itt->moveForward();
        itt->setData(space,false,EMPTY);
        itt->moveLeft();
        itt->setData(space,false,EMPTY);
        for(int j = 0;j<length-3;j++)
            itt->moveLeft();
        itt->setData(space,false,EMPTY);
        itt->moveLeft();
        itt->setData(space,false,EMPTY);
        itt->moveBack();
        itt->setData(space,false,EMPTY);
    }
}

template <class Type>
void ObjectInserter<Type>::insertFloor(int width, int length, int x, int y, int z)
{
    itt->setLocation(x,y,z);
    for(int i = 0;i<length;i++)
    {
        itt->setData(composition,true,WALL);
        for(int j = 0;j<width-1;j++)
        {
            itt->moveForward();
            itt->setData(composition,true,WALL);
        }
        for(int k = 0;k<width-1;k++)
            itt->moveBack();
        if(i != length - 1)
            itt->moveRight();
    }
}

template <class Type>
void ObjectInserter<Type>::insertFloor(int width, int length)
{
    for(int i = 0;i<length;i++)
    {
        itt->setData(composition,true,WALL);
        for(int j = 0;j<width-1;j++)
        {
            itt->moveForward();
            itt->setData(composition,true,WALL);
        }
        for(int k = 0;k<width-1;k++)
            itt->moveBack();
        itt->moveRight();
    }
}

template <class Type>
void ObjectInserter<Type>::insertPyramid(int height,int x,int y,int z)
{
    itt->setLocation(x,y,z);
    for(int i = height;i>0;i--)
    {
        insertFloor(2*i-1,2*i-1);
        itt->setLocation(++x,++y,++z);
    }
}

template <class Type>
void ObjectInserter<Type>::insertGround(int depth,int width,int length)
{
    for(int i = 0;i<depth;i++)
        insertFloor(width,length,0,0,i);
}

template <class Type>
void ObjectInserter<Type>::insertStairsLR(int height,int x,int y,int z)
{
    bool go = true;
    itt->setLocation(x,y,z);
    for(int i = 0;i<height;i++)
    {
        if(i == 0)
            itt->setData(composition,true,WALL);
        else
        {
            go = itt->moveUp();
            go = itt->moveRight();
            if(go == true)
                itt->setData(composition,true,WALL);
            else
                break;
        }
    }
}

template <class Type>
void ObjectInserter<Type>::insertDoor(int x,int y,int z)
{
    itt->setLocation(x,y,z);
    itt->setData(space,false,EMPTY);
    itt->moveUp();
    itt->setData(space,false,EMPTY);
}

template <class Type>
void ObjectInserter<Type>::insertRoom(int width,int height,int length,int x,int y,int z)
{
    insertFloor(width,length,x,y,z-1);
    insertWallLR(height,length,x,y,z);
    insertWallLR(height,length,x,y+width-1,z);
    insertWallFB(height,width-2,x,y+width-2,z);
    insertWallFB(height,width-2,x+length-1,y+width-2,z);
    insertFloor(width-2,length-2,x+1,y+1,z+height-1);
}

template <class Type>
void ObjectInserter<Type>::insertBomb(int x, int y, int z,int timer)
{
    itt->setLocation(x,y,z);
    itt->setData(timer, true, BOMB);
}

template <class Type>
void ObjectInserter<Type>::insertKey(const Type& comp,int x,int y,int z)
{
    itt->setLocation(x,y,z);
    itt->setData(comp, true, KEY);
}



#endif

