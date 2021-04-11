#include <iostream>
using namespace std;

struct ShapeVtable;

struct Shape
{
    ShapeVtable* table;
};

struct ShapeVtable
{
    float(*GetArea)(Shape*);
    void (*Destroy)(Shape*);

};

float GetArea(Shape* shape)
{
    return shape->table->GetArea(shape);
}

void DestroyShape(Shape* shape)
{
    shape->table->Destroy(shape);
}

struct Circle
{
    Shape parent;
    float radius;
};

float getCircleArea(Circle* circle)
{
    float r = circle->radius;
    float area = (22.0/7.0) * (r*r);
    return area;
}

void circleDestroy(Circle* circle){
}

ShapeVtable circleVTable =
{
    (float(*)(Shape*)) getCircleArea,
    (void(*)(Shape*)) circleDestroy
};

void CircleInitialize(Circle* circle, float radiuss)
{
    circle->parent.table = &circleVTable;
    circle->radius = radiuss;
}

struct Rectangle
{
    Shape parent;
    float length;
    float width;
};

float getRectangleArea(Rectangle* Rec)
{
    float l = Rec->length;
    float w = Rec->width;
    float area = l*w;
    return area;
}

void destroyRectangle(){
}

ShapeVtable rectangleVTable =
{
    (float(*)(Shape*)) getRectangleArea,
    (void(*)(Shape*)) destroyRectangle
};

void RectangleInitialize(Rectangle* Rec, float length, float width = 0)
{
    Rec->parent.table = &rectangleVTable;
    Rec->length = length;
    Rec->width = width;
}

struct Square
{
    Shape parent;
    float length;
    float area;
};

float getSquareArea(Square* S)
{
    float l = S->length;
    float area = l*l;
    return area;
}

void destroySquare(Square* S){
}

ShapeVtable squareVTable =
{
    (float(*)(Shape*)) getSquareArea,
    (void(*)(Shape*)) destroySquare
};

void SquareInitialize(Square* S, float length)
{
    S->parent.table = &squareVTable;
    S->length = length;
}

int main()
{
    Circle circle;
    CircleInitialize(&circle, 10); // circle with radius 10

    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3, 5); // rectangle with width 3 and height 5

    Square square;
    SquareInitialize(&square, 7); // square with side length 7

    Shape* shapes[3];
    shapes[0]=(Shape*)&circle;
    shapes[1]=(Shape*)&rectangle;
    shapes[2]=(Shape*)&square;

    double total_area=0;

    int i;
    for(i=0;i<3;i++)
    {
        double d=GetArea(shapes[i]);
        total_area+=d;
    }

    cout<<total_area<<endl; // check if the value is correct

    return 0;
}
