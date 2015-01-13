
#ifndef LINK3D_H
#define	LINK3D_H

enum ObjectType{WALL,BOMB,KEY,DOOR,EMPTY};

template <class Type>
struct Link3D
{
    Link3D<Type>(const Type& initData);
    Link3D<Type>(Link3D<Type>*);
    Link3D<Type>();
    Link3D<Type> *right;
    Link3D<Type> *left;
    Link3D<Type> *above;
    Link3D<Type> *below;
    Link3D<Type> *infront;
    Link3D<Type> *behind;
    Type data;
    Type explodeCondition;
    ObjectType type;
    bool isSolid;
    void startCountDown(const Type&,int);
    bool countDown();
    void lock();
    void unlock();
private:
    void recExplode(int Magnitude);
    void explode();
    int magnitude;
    bool isLocked;
};

template <class Type>
Link3D<Type>::Link3D(const Type& initData)
{
    right = NULL;
    left = NULL;
    above = NULL;
    below = NULL;
    infront = NULL;
    behind = NULL;
    type = EMPTY;
    data = initData;
    explodeCondition = NULL;
    magnitude = NULL;
}

template <class Type>
Link3D<Type>::Link3D(Link3D<Type>* otherLink)
{
    right = otherLink->right;
    left = otherLink->left;
    above = otherLink->above;
    below = otherLink->below;
    infront = otherLink->infront;
    behind = otherLink->behind;
    type = otherLink->type;
    data = otherLink->data;
}

template <class Type>
Link3D<Type>::Link3D()
{
    right = NULL;
    left = NULL;
    above = NULL;
    below = NULL;
    infront = NULL;
    behind = NULL;
    type = EMPTY;
    data = NULL;
    explodeCondition = NULL;
    magnitude = NULL;
}

template <class Type>
void Link3D<Type>::startCountDown(const Type& condition,int explodeMag)
{
    explodeCondition = condition;
    magnitude = explodeMag;
}

template <class Type>
bool Link3D<Type>::countDown()
{
    data--;
    if(data == explodeCondition)
    {
        recExplode(magnitude);
        return false;
    }
    else
        return true;
}

template <class Type>
void Link3D<Type>::recExplode(int i)
{
    //base case
    if(i == 0)
        explode();
    else
    {
        if(right != NULL)
        right->recExplode(i-1);
        if(left != NULL)
        left->recExplode(i-1);
        if(above != NULL)
        above->recExplode(i-1);
        if(below != NULL)
        below->recExplode(i-1);
        if(infront != NULL)
        infront->recExplode(i-1);
        if(behind != NULL)
        behind->recExplode(i-1);
        explode();
    }

}

template <class Type>
void Link3D<Type>::explode()
{
    isSolid = false;
    type = EMPTY;
    data = explodeCondition;
}

template <class Type>
void Link3D<Type>::lock()
{
    isLocked = true;
}

template <class Type>
void Link3D<Type>::unlock()
{
    isLocked = false;
}



#endif	/* LINK3D_H */

