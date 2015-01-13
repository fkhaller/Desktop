#ifndef MATRIX3D_H
#define	MATRIX3D_H

#include <cstddef>
#include "Link3D.h"
#include "MatrixIterator.h"

using namespace std;

template <class Type>
class Matrix3D
{
public:
    Matrix3D();
    ~Matrix3D();
    bool isEmpty() const;
    void initCube(const Type& initVal,const int size);
    void initCuboid(const Type& initVal,const int height,const int length,const int width);
    void initRectangle(const Type& initVal,const int ht,const int wd);
    void insertRectangle(const Type& initVal,const int ht,const int wd);
    MatrixIterator<Type>* getIterator();
    int getHeight();
    int getLength();
    int getWidth();
protected:
    void insertLeft(const Type& newElem);
    void insertRight(const Type& newElem);
    void insertAbove(const Type& newElem);
    void insertBelow(const Type& newElem);
    void insertInfront(const Type& newElem);
    void insertBehind(const Type& newElem);
    MatrixIterator<Type> *itt;
    Link3D<Type> *source;
    Link3D<Type> *topLeftFirst;
    Link3D<Type> *topLeftLast;
    Link3D<Type> *topRightFirst;
    Link3D<Type> *topRightLast;
    Link3D<Type> *botLeftFirst;
    Link3D<Type> *botLeftLast;
    Link3D<Type> *botRightFirst;
    Link3D<Type> *botRightLast;
private:
    void init(const Type& newSource);
    int height;
    int length;
    int width;
};



template <class Type>
Matrix3D<Type>::Matrix3D()
{
    source = new Link3D<Type>();
    topLeftFirst = NULL;
    topLeftLast = NULL;
    topRightFirst = NULL;
    topRightLast = NULL;
    botLeftFirst = NULL;
    botLeftLast = NULL;
    botRightFirst = NULL;
    botRightLast = NULL;
    itt = NULL;
}

template <class Type>
Matrix3D<Type>::~Matrix3D()
{

}

template <class Type>
bool Matrix3D<Type>::isEmpty() const
{
    return (source.right == NULL);
}


template <class Type>
void Matrix3D<Type>::initCube(const Type& initVal,const int size)
{
    height = size;
    width = size;
    length = size;
    if(source->right == NULL)
        init(initVal);
    for(int i = 0;i<size;i++)
    {
        initRectangle(initVal,size,size);
        if(i < size - 1)
        {
        insertInfront(initVal);
        itt->moveForward();
        }
    }
    itt->allBack();

}

template <class Type>
void Matrix3D<Type>::initCuboid(const Type& initVal,const int height, const int length, const int width)
{

}

template <class Type>
void Matrix3D<Type>::initRectangle(const Type& initVal,const int ht,const int wd)
{
    height = ht;
    width = wd;
    if(source->right == NULL)
        init(initVal);
    else
    {
        itt->allUp();
        itt->allLeft();
    }
    for(int i = 0;i<width;i++)
    {
        for(int j = 0;j<height-1;j++)
            insertBelow(initVal);
        if(i != width-1)
        {
        insertRight(initVal);
        itt->moveRight();
        }
    }
    itt->allUp();
    itt->allLeft();
}


template <class Type>
MatrixIterator<Type>* Matrix3D<Type>::getIterator()
{
    return new MatrixIterator<Type>(topLeftFirst);
}

template <class Type>
int Matrix3D<Type>::getHeight()
{
    return height;
};

template <class Type>
int Matrix3D<Type>::getWidth()
{
    return width;
};

template <class Type>
int Matrix3D<Type>::getLength()
{
    return length;
};

template <class Type>
void Matrix3D<Type>::insertAbove(const Type& newElem)
{
    int count = 0;
    if(source->right == NULL)
        init(newElem);
    else
    {
        //go to the end
        while(itt->hasAbove())
        {
            itt->moveUp();
            count++;
        }
        //add new element
        Link3D<Type> *newLink;
        newLink = new Link3D<Type>(newElem);
        Link3D<Type> *current = itt->getCurrent();
        newLink->below = current;
        current->above = newLink;
        //make sure concavity is checked for
        if(current->left != NULL)
        {
            if(current->left->above != NULL)
            {
                newLink->left = current->left->above;
                current->left->above->right = newLink;
            }
        }
        if(current->right != NULL)
        {
            if(current->right->above != NULL)
            {
                newLink->right = current->right->above;
                current->right->above->left = newLink;
            }
        }
        if(current->infront != NULL)
        {
            if(current->infront->above != NULL)
            {
                newLink->infront = current->infront->above;
                current->infront->above->behind = newLink;
            }
        }
        if(current->behind != NULL)
        {
            if(current->behind->above != NULL)
            {
                newLink->behind = current->behind->above;
                current->behind->above->infront = newLink;
            }
        }
        //resets the iterator
        for(int i = 0;i<count;i++)
            itt.moveDown();
    }
}

template <class Type>
void Matrix3D<Type>::insertBelow(const Type& newElem)
{
    int count = 0;
    if(source->right == NULL)
        init(newElem);
    else
    {
        while(itt->hasBelow())
        {
            itt->moveDown();
            count++;
        }

        Link3D<Type> *newLink;
        newLink = new Link3D<Type>(newElem);
        Link3D<Type> *curr = itt->getCurrent();
        newLink->above = curr;
        curr->below = newLink;

        if(curr->left != NULL){
            if(curr->left->below != NULL)
            {
                newLink->left = curr->left->below;
                curr->left->below->right = newLink;
            }
        }
        if(curr->right != NULL){
            if(curr->right->below != NULL)
            {
                newLink->right = curr->right->below;
                curr->right->below->left = newLink;
            }
        }
        if(curr->infront != NULL){
            if(curr->infront->below != NULL)
            {
                newLink->infront = curr->infront->below;
                curr->infront->below->behind = newLink;
            }
        }
        if(curr->behind != NULL){
            if(curr->behind->below != NULL)
            {
                newLink->behind = curr->behind->below;
                curr->behind->below->infront = newLink;
            }
        }
        for(int i = 0;i<count;i++)
            itt->moveUp();

    }
}

template <class Type>
void Matrix3D<Type>::insertLeft(const Type& newElem)
{
    int count = 0;
    if(source->right == NULL)
        init(newElem);
    else{
        while(itt->hasLeft())
        {
            itt->moveLeft();
            count++;
        }

        Link3D<Type> *newLink;
        newLink = new Link3D<Type>(newElem);
        Link3D<Type> *current = itt->getCurrent();
        newLink->right = current;
        current->left = newLink;

        if(current->above != NULL)
        {
            if(current->above->left != NULL)
            {
                newLink->above = current->above->left;
                current->above->left->below = newLink;
            }
        }
        if(current->below != NULL)
        {
            if(current->below->left != NULL)
            {
                newLink->below = current->below->left;
                current->below->left->above = newLink;
            }
        }
        if(current->infront != NULL)
        {
            if(current->infront->left != NULL)
            {
                newLink->infront = current->infront->left;
                current->infront->left->behind = newLink;
            }
        }
        if(current->behind != NULL)
        {
            if(current->behind->left != NULL)
            {
                newLink->behind = current->behind->left;
                current->behind->left->infront = newLink;
            }
        }
        for(int i = 0;i<count;i++)
            itt->moveRight();
    }
}

template <class Type>
void Matrix3D<Type>::insertRight(const Type& newElem)
{
    int count = 0;
    if(source->right == NULL)
        init(newElem);
    else{
        while(itt->hasRight())
        {
            itt->moveRight();
            count++;
        }

        Link3D<Type> *newLink;
        newLink = new Link3D<Type>(newElem);
        Link3D<Type> *current = itt->getCurrent();
        newLink->left = current;
        current->right = newLink;

        if(current->above != NULL)
        {
            if(current->above->right != NULL)
            {
                newLink->above = current->above->right;
                current->above->right->below = newLink;
            }
        }
        if(current->below != NULL)
        {
            if(current->below->right != NULL)
            {
                newLink->below = current->below->right;
                current->below->right->above = newLink;
            }
        }
        if(current->infront != NULL)
        {
            if(current->infront->right != NULL)
            {
                newLink->infront = current->infront->right;
                current->infront->right->behind = newLink;
            }
        }
        if(current->behind != NULL)
        {
            if(current->behind->right != NULL)
            {
                newLink->behind = current->behind->right;
                current->behind->right->infront = newLink;
            }
        }
        for(int i = 0;i<count;i++)
            itt->moveLeft();
    }
}

template <class Type>
void Matrix3D<Type>::insertInfront(const Type& newElem)
{
    int count = 0;
    if(source->right == NULL)
        init(newElem);
    else{
        while(itt->hasInfront())
        {
            itt->moveForward();
            count++;
        }

        Link3D<Type> *newLink;
        newLink = new Link3D<Type>(newElem);
        Link3D<Type> *current = itt->getCurrent();
        newLink->behind = current;
        current->infront = newLink;

        if(current->left != NULL)
        {
            if(current->left->infront != NULL)
        {
                newLink->left = current->left->infront;
                current->left->infront->right = newLink;
            }
        }
        if(current->right != NULL)
        {
            if(current->right->infront != NULL)
            {
                newLink->right = current->right->infront;
                current->right->infront->left = newLink;
            }
        }
        if(current->above != NULL)
        {
            if(current->above->infront != NULL)
            {
                newLink->above = current->above->infront;
                current->above->infront->below = newLink;
            }
        }
        if(current->below != NULL)
        {
            if(current->below->infront != NULL)
            {
                newLink->below = current->below->infront;
                current->below->infront->above = newLink;
            }
        }
        for(int i = 0;i<count;i++)
            itt->moveBack();
    }
}

template <class Type>
void Matrix3D<Type>::insertBehind(const Type& newElem)
{
    int count = 0;
    if(source.right == NULL)
        init(newElem);
    else{
        while(itt->hasBehind())
        {
            itt->moveBack();
            count++;
        }

        Link3D<Type> *newLink;
        newLink = new Link3D<Type>(newElem);
        Link3D<Type> *current = itt->getCurrent();
        newLink->infront = current;
        current->behind = newLink;

        if(current->left != NULL)
        {
            if(current->left->behind != NULL)
            {
                newLink->left = current->left->behind;
                current->left->above->right = newLink;
            }
        }
        if(current->right != NULL)
        {
            if(current->right->behind != NULL)
            {
                newLink->right = current->right->behind;
                current->right->above->left = newLink;
            }
        }
        if(current->above != NULL)
        {
            if(current->above->behind != NULL)
            {
                newLink->above = current->above->behind;
                current->above->behind->below = newLink;
            }
        }
        if(current->below != NULL)
        {
            if(current->below->behind != NULL)
            {
                newLink->below = current->below->behind;
                current->below->behind->above = newLink;
            }
        }
        for(int i = 0;i<count;i++)
            itt.moveForward();
    }
}

template <class Type>
void Matrix3D<Type>::init(const Type& firstData)
{
    source->right = new Link3D<Type>(firstData);
    itt = new MatrixIterator<Type>(source->right);
    topLeftFirst = source->right;
}

#endif	/* MATRIX3D_H */
