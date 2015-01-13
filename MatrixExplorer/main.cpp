#include <iostream>
#include <string>
#include <stdlib.h>
#include "Matrix3D.h"
#include "ObjectInserter.h"
#include "ObjectViewer.h"

using namespace std;

int main() {

    bool *restart = new bool;
    *restart = true;
    Matrix3D<char> *mat = new Matrix3D<char>();
    mat->initCube(0,15);
    ObjectInserter<char> *creator = new ObjectInserter<char>(mat,219,0);
    ObjectViewer<char> *cam;
    while(*restart)
    {
    *restart = false;
    creator->insertGround(2,15,15);
    creator->insertRoom(5,5,5,0,0);
    creator->insertRoom(4,6,7,4,0);
    creator->insertStairsLR(5,0,5);
    creator->insertBomb(1,3);
    creator->insertBomb(6,1,8);
    creator->insertBomb(9,1);
    creator->insertKey(202,5,1);
    creator->insertPyramid(4,7,5);
    creator->insertTower(5,3,0,7);
    cam = new ObjectViewer<char>(mat,148,0,restart,1,1);
    cam->printRectBelow();

    string command;
    enum CameraPosition{ABOVE,RIGHT,BEHIND} camPos = ABOVE;

    while(command != "exit" && command != "Exit")
    {
        cin >> command;
        if(command == "step_forward" || command == "w" && camPos != BEHIND)
        {
            cam->stepForward();
            if(*restart)
                break;
            if(camPos == ABOVE)
                cam->printRectBelow();
            else if(camPos == RIGHT)
                cam->printRectLeft();
            else if(camPos == BEHIND)
                cam->printRectForward();
        }
        else if(command == "step_back" || command == "s" && camPos != BEHIND)
        {
            cam->stepBack();
            if(*restart)
                break;
            if(camPos == ABOVE)
                cam->printRectBelow();
            else if(camPos == RIGHT)
                cam->printRectLeft();
            else if(camPos == BEHIND)
                cam->printRectForward();
        }
        else if(command == "step_left" || command == "a" && camPos != RIGHT)
        {
            cam->stepLeft();
            if(*restart)
                break;
            if(camPos == ABOVE)
                cam->printRectBelow();
            else if(camPos == RIGHT)
                cam->printRectLeft();
            else if(camPos == BEHIND)
                cam->printRectForward();
        }
        else if(command == "step_right" || command == "d" && camPos != RIGHT)
        {
            cam->stepRight();
            if(*restart)
                break;
            if(camPos == ABOVE)
                cam->printRectBelow();
            else if(camPos == RIGHT)
                cam->printRectLeft();
            else if(camPos == BEHIND)
                cam->printRectForward();
        }

        else if(command == "look_FB"  || command == "q")
            cam->printRectLeft();
        else if(command == "look_LR" || command == "e")
            cam->printRectForward();

        else if(command == "setq")
            camPos = RIGHT;
        else if(command == "sete")
            camPos = BEHIND;
        else if(command == "setw")
            camPos = ABOVE;

        else if(command == "inspect_forward" || command == "iw")
            cam->inspectForward();
        else if(command == "inspect_left" || command == "ia")
            cam->inspectLeft();
        else if(command == "inspect_right" || command == "id")
            cam->inspectRight();
        else if(command == "inspect_behind" || command == "is")
            cam->inspectBack();
        else if(command == "inspect_above" || command == "iq")
            cam->inspectUp();
        else if(command == "inspect_below" || command == "ie")
            cam->inspectDown();

        else if(command == "restart")
        {
            *restart = true;
            break;
        }

        else if(command == "help")
        {
            cout << "w - move forward" << endl
                 << "s - move back" << endl
                 << "a - move left" << endl
                 << "d - move right" << endl
                 << "q - lets you see what's infront and behind you" << endl
                 << "e - lets you see what's to your left and right" << endl
                 << "i + a direction key(q for up and e for down) - inspects your "
                    "environment" << endl
                 << "set*(setq,setw,sete) - sets the camera angle. note:you can not "
                    "move a direction you can't see" << endl;
        }

    }
    delete cam;
    }
    return 0;
};



