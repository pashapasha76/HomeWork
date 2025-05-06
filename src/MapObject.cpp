#include "MapObject.h"

int MapObject::nextId = 0;

MapObject::MapObject(double x, double y)
    : id(nextId++), x(x), y(y) {}

void MapObject::resetNextId() {
    nextId = 0;
}

double MapObject::distanceTo(const MapObject& other){
    return std::sqrt((x - other.getX()) * (x - other.getX()) + (y - other.getY()) * (y - other.getY()));
}