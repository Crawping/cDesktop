#ifndef ICON_H
#define ICON_H

#include <string>
#include "Position.h"

class Icon
{
    public:
        int getIndex();
        std::string name; // filename
        std::string path; // path to the image of the icon
        Position position; // current position


        Icon(std::string name, std::string path, Position pos, int type); // creates new icon
        Icon(std::string name); // loads icon from desktop
        virtual ~Icon();

        //static const int width = 64, height = 64;
        static const int width = 80, height = 80;

        std::string getName() { return name; }
        void setName(std::string name);
        void setPos(Position pos);
        bool canPlace(Position pos);
        Position getPosition() { return position; }

        void init();

    protected:
        bool isOwnIcon; // Is this icon created by program, or existed before
};

#endif // ICON_H
