#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <iostream>

class MapObject {
protected:
    int id;
    double x, y;
    static int nextId;

public:
    MapObject(double x, double y);
    virtual void print() const = 0;
    virtual ~MapObject() {}

    double getX() const { return x; }
    double getY() const { return y; }
    int getId() const { return id; }
    double distanceTo(const MapObject& other);

    static void resetNextId();
};

#endif 
