#include <malloc.h>
#include <iostream>
#include <string>
using namespace std;

typedef double (*double_method_type)(void*);
typedef void (*void_method_type)(void*);

typedef union {
  void_method_type void_method;
  double_method_type double_method;
} VirtualTableEntry;

typedef VirtualTableEntry *VTableType;

#define PRINT_INDEX 0
#define DRAW_INDEX 1
#define AREA_INDEX 2

#define PI 3.14159

// Start of Class Shape

struct Shape {
  VTableType VPointer;
  double name;
};

void Shape_print(Shape *_this) {
  cout << _this->name << endl;
}

void Shape_draw(Shape *_this){
  cout << "^_^" << endl;
};

double Shape_area(Shape *_this) {
  return 0;
};

VirtualTableEntry Shape_VTable[] = {
  {.void_method = (void_method_type)Shape_print},
  {.void_method = (void_method_type)Shape_draw},
  {.double_method = (double_method_type)Shape_area}
};

Shape* Shape_Shape(Shape *_this, double newName) {
  _this->VPointer = Shape_VTable;
  _this->name = newName;

  return _this;
};

// End of Class Shape



// Start of Class Circle

struct Circle // extends Shape 
{
  VTableType Vpointer;
  double name;

  // new data members
  double radius;
};

double Circle_area(Circle *_this)
{
  return PI * _this->radius * _this->radius;
};

void Circle_print(Circle *_this) {
  cout << _this->name << "(" << _this->radius << ") : " << Circle_area(_this) << endl;
};

void Circle_draw(Circle *_this) {
  for (int y = (int)-_this->radius; y <= _this->radius; y++)
  {
    for (int x = (int)-_this->radius; x <= _this->radius; x++)
    {
      if (x * x + y * y <= _this->radius * _this->radius)
      {
        cout << "*";
      }
      else
      {
        cout << " ";
      }
    }
    cout << endl;
  }
};

VirtualTableEntry Circle_VTable[] = {
  {.void_method = (void_method_type)Circle_print},
  {.void_method = (void_method_type)Circle_draw},
  {.double_method = (double_method_type)Circle_area}
};

Circle* Circle_Circle(Circle *_this, double newName, double newRadius) {
  Shape_Shape((Shape*) _this, newName);
  _this->Vpointer = Circle_VTable;
  _this->radius = newRadius;
  return _this;
};

// End of Class Circle


// Start of Class Triangle

struct Triangle // extends Shape
{
  VTableType Vpointer;
  double name;

  // new data members
  double base;
  double height;
};

double Triangle_area(Triangle *_this)
{
  return (_this->base * _this->height) / 2;
};

void Triangle_print(Triangle *_this)
{
  cout << _this->name << "(" << _this->base << "," << _this->height << ") : " << Triangle_area(_this) << endl;
};

void Triangle_draw(Triangle *_this)
{
  for (int i = 0; i < _this->height; i++)
  {
    for (int j = 0; j < _this->base; j++)
    {
      if (j >= _this->height - i - 1 && j <= _this->height + i - 1)
      {
        cout << "*";
      }
      else
      {
        cout << " ";
      }
    }
    cout << endl;
  }
};

VirtualTableEntry Triangle_VTable[] = {
    {.void_method = (void_method_type)Triangle_print},
    {.void_method = (void_method_type)Triangle_draw},
    {.double_method = (double_method_type)Triangle_area}};

Triangle *Triangle_Triangle(Triangle *_this, double newName, double newBase, double newHeight)
{
  Shape_Shape((Shape *)_this, newName);
  _this->Vpointer = Triangle_VTable;
  _this->base = newBase;
  _this->height = newHeight;
  return _this;
};

// End of Class Triangle

// Start of Class Square

struct Square // extends Shape
{
  VTableType Vpointer;
  double name;

  // new data members
  int length;
};

double Square_area(Square *_this)
{
  return _this->length * _this->length;
};

void Square_print(Square *_this)
{
  cout << _this->name << "(" << _this->length << ") : " << Square_area(_this) << endl;
};

void Square_draw(Square *_this)
{
  for (int i = 0; i < _this->length; i++)
  {
    for (int j = 0; j < _this->length; j++)
    {
      cout << "*";
    }
    cout << endl;
  }
};

VirtualTableEntry Square_VTable[] = {
  {.void_method = (void_method_type)Square_print},
  {.void_method = (void_method_type)Square_draw},
  {.double_method = (double_method_type)Square_area}
};

Square *Square_Square(Square *_this, double newName, int newLength)
{
  Shape_Shape((Shape *)_this, newName);
  _this->Vpointer = Square_VTable;
  _this->length = newLength;
  return _this;
};

// End of Class Square

// Start of Class Rectangle

struct Rectangle {
  VTableType Vpointer;
  double name;
  int length;

  // new data members
  int width;
};

double Rectangle_area(Rectangle *_this)
{
  return _this->length * _this->width;
};

void Rectangle_print(Rectangle *_this)
{
  cout << _this->name << "(" << _this->length << "," << _this->width << ") : " << Rectangle_area(_this) << endl;
};

void Rectangle_draw(Rectangle *_this)
{
  for (int i = 0; i < _this->width; i++)
  {
    for (int j = 0; j < _this->length; j++)
    {
      cout << "*";
    }
    cout << endl;
  }
};

VirtualTableEntry Rectangle_VTable[] = {
    {.void_method = (void_method_type)Rectangle_print},
    {.void_method = (void_method_type)Rectangle_draw},
    {.double_method = (double_method_type)Rectangle_area}};

Rectangle *Rectangle_Rectangle(Rectangle *_this, double newName, int newLength)
{
  Square_Square((Square*) _this, newName, newLength);
  _this->Vpointer = Rectangle_VTable;
  _this->width = newLength;
  return _this;
};

// Picture Functions

void drawAll(Shape** shapeArray, int elems) {
  // Drawing all Shapes in a Picture
  for (int i = 0; i < elems; i++)
  {
    shapeArray[i]->VPointer[DRAW_INDEX].void_method(shapeArray[i]);
  }
}

void printAll(Shape** shapeArray, int elems)
{
  // Printing all Shapes in Picture
  for (int i = 0; i < elems; i++)
  {
    shapeArray[i]->VPointer[PRINT_INDEX].void_method(shapeArray[i]);
  }
}

double totalArea(Shape** shapeArray, int elems)
{
  double total = 0;
  for (int i = 0; i < elems; i++)
  {
    total += shapeArray[i]->VPointer[AREA_INDEX].double_method(shapeArray[i]);
  }
  return total;
}

// Main function

int main()
{
  // "Picture Implementation"
  Shape *s[] = {
    Shape_Shape((Shape *) malloc(sizeof(Shape)), 0),
    (Shape *) Circle_Circle((Circle*) malloc(sizeof(Circle)), 1, 5)
  };

  drawAll(s, 2);
  printAll(s, 2);
  cout << totalArea(s, 2);

  // Drawing all Shapes in a Picture
  // for (int i = 0; i < sizeof(s) / sizeof(*s); i++)
  // {
  //   s[i]->VPointer[DRAW_INDEX].void_method(s[i]);
  // };

  return 0;
}