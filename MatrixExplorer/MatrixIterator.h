
#ifndef MATRIXITERATOR_H
#define	MATRIXITERATOR_H


template <class Type>
class MatrixIterator
{
    public:
        MatrixIterator(Link3D<Type> *ptr);
        MatrixIterator();
        const MatrixIterator<Type>& operator=(const MatrixIterator<Type>&);
        Type operator*();
        void setData(const Type&,bool isSolid = false,ObjectType comp = EMPTY);
        void setCurrent(Link3D<Type> *ptr);
        Link3D<Type>* getCurrent();
        void setLocation(int x = 0,int y = 0,int z = 0);
        bool isSolid();

        //Does it got one?
        bool hasLeft();
        bool hasSolidLeft();
        bool hasBombLeft();
        bool hasRight();
        bool hasSolidRight();
        bool hasBombRight();
        bool hasAbove();
        bool hasSolidAbove();
        bool hasBombAbove();
        bool hasBelow();
        bool hasSolidBelow();
        bool hasBombBelow();
        bool hasInfront();
        bool hasSolidInfront();
        bool hasBombInfront();
        bool hasBehind();
        bool hasSolidBehind();
        bool hasBombBehind();

        //gotta get around
        bool moveLeft();
        void allLeft();
        bool moveRight();
        void allRight();
        bool moveUp();
        void allUp();
        bool moveDown();
        void allDown();
        bool moveForward();
        void allForward();
        bool moveBack();
        void allBack();
    private:
        Link3D<Type> *current;
};

template <class Type>
MatrixIterator<Type>::MatrixIterator(Link3D<Type> *ptr)
{
    current = ptr;
}

template <class Type>
MatrixIterator<Type>::MatrixIterator()
{
    current = NULL;
}

template <class Type>
void MatrixIterator<Type>::setData(const Type& newData,bool isSld,ObjectType comp)
{
    current->data = newData;
    current->isSolid = isSld;
    current->type = comp;
}

template <class Type>
Type MatrixIterator<Type>::operator*()
{
    return current->data;
}

template <class Type>
void MatrixIterator<Type>::setCurrent(Link3D<Type> *ptr)
{
    current = ptr;
}

template <class Type>
Link3D<Type>* MatrixIterator<Type>::getCurrent()
{
    return current;
}

template <class Type>
void MatrixIterator<Type>::setLocation(int x, int y,int z)
{
    allDown();
    allBack();
    allLeft();
    for(int i = 0;i<x;i++)
        moveRight();
    for(int j = 0;j<y;j++)
        moveForward();
    for(int k = 0;k<z;k++)
        moveUp();
}

template <class Type>
bool MatrixIterator<Type>::isSolid()
{
    return (current->isSolid);
}

template <class Type>
bool MatrixIterator<Type>::hasLeft()
{
    return (current->left != NULL);
}

template <class Type>
bool MatrixIterator<Type>::hasSolidLeft()
{
    if(hasLeft())
        return (current->left->isSolid);
    else
        return true;
}

template <class Type>
bool MatrixIterator<Type>::hasBombLeft()
{
    if(hasLeft())
        return (current->left->type == BOMB);
    else
        return false;
}

template <class Type>
bool MatrixIterator<Type>::hasRight()
{
    return (current->right != NULL);
}

template <class Type>
bool MatrixIterator<Type>::hasSolidRight()
{
    if(hasRight())
        return (current->right->isSolid);
    else
        return true;
}

template <class Type>
bool MatrixIterator<Type>::hasBombRight()
{
    if(hasRight())
        return (current->right->type == BOMB);
    else
        return false;
}

template <class Type>
bool MatrixIterator<Type>::hasAbove()
{
    return (current->above != NULL);
}

template <class Type>
bool MatrixIterator<Type>::hasSolidAbove()
{
    if(hasAbove())
        return (current->above->isSolid);
    else
        return true;
}

template <class Type>
bool MatrixIterator<Type>::hasBombAbove()
{
    if(hasAbove())
        return (current->above->type == BOMB);
    else
        return false;
}

template <class Type>
bool MatrixIterator<Type>::hasBelow()
{
    return (current->below != NULL);
}

template <class Type>
bool MatrixIterator<Type>::hasSolidBelow()
{
    if(hasBelow())
        return (current->below->isSolid);
    else
        return true;
}

template <class Type>
bool MatrixIterator<Type>::hasBombBelow()
{
    if(hasBelow())
        return (current->below->type == BOMB);
    else
        return false;
}

template <class Type>
bool MatrixIterator<Type>::hasInfront()
{
    return (current->infront != NULL);
}

template <class Type>
bool MatrixIterator<Type>::hasSolidInfront()
{
    if(hasInfront())
        return (current->infront->isSolid);
    else
        return true;
}

template <class Type>
bool MatrixIterator<Type>::hasBombInfront()
{
    if(hasInfront())
        return (current->infront->type == BOMB);
    else
        return false;
}

template <class Type>
bool MatrixIterator<Type>::hasBehind()
{
    return (current->behind != NULL);
}

template <class Type>
bool MatrixIterator<Type>::hasSolidBehind()
{
    if(hasBehind())
        return (current->behind->isSolid);
    else
        return true;
}

template <class Type>
bool MatrixIterator<Type>::hasBombBehind()
{
    if(hasBehind())
        return (current->behind->type == BOMB);
    else
        return false;
}



/////************/////////////////////////////////////////////////////////////////

template <class Type>
bool MatrixIterator<Type>::moveLeft()
{
    if(hasLeft())
    {
        current = current->left;
        return true;
    }
    else
        return false;
}

template <class Type>
void MatrixIterator<Type>::allLeft()
{
    while(hasLeft())
        current = current->left;
}

template <class Type>
bool MatrixIterator<Type>::moveRight()
{
    if(hasRight())
    {
        current = current->right;
        return true;
    }
        return false;
}

template <class Type>
void MatrixIterator<Type>::allRight()
{
    while(hasRight())
        current = current->right;
}

template <class Type>
bool MatrixIterator<Type>::moveUp()
{
    if(hasAbove())
    {
        current = current->above;
        return true;
    }
        return false;
}

template <class Type>
void MatrixIterator<Type>::allUp()
{
    while(hasAbove())
        current = current->above;
}

template <class Type>
bool MatrixIterator<Type>::moveDown()
{
    if(hasBelow())
    {
        current = current->below;
        return true;
    }
        return false;
}

template <class Type>
void MatrixIterator<Type>::allDown()
{
    while(hasBelow())
        current = current->below;
}

template <class Type>
bool MatrixIterator<Type>::moveForward()
{
    if(hasInfront())
    {
        current = current->infront;
        return true;
    }
        return false;
}

template <class Type>
void MatrixIterator<Type>::allForward()
{
    while(hasInfront())
        current = current->infront;
}

template <class Type>
bool MatrixIterator<Type>::moveBack()
{
    if(hasBehind())
    {
        current = current->behind;
        return true;
    }
        return false;
}

template <class Type>
void MatrixIterator<Type>::allBack()
{
    while(hasBehind())
        current = current->behind;
}

#endif	/* MATRIXITERATOR_H */

