#include <malloc.h>
#include <iostream>
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
  string name;  
};

void Shape_print(Shape *_this) {
  cout << _this->name;
}

void Shape_draw(Shape *_this){
  cout << "^_^";
};

double Shape_area(Shape *_this) {
 return 0;
};

VirtualTableEntry Shape_VTable[] = {
    // .void_method = (void_method_type) Shape_print
    {.void_method = (void_method_type)Shape_print},
    {.void_method = (void_method_type)Shape_draw},
    {.double_method = (double_method_type)Shape_area}};

Shape *Shape_Shape(Shape *_this, string newName) {
  _this->VPointer = Shape_VTable;
  _this->name = std::string();
  _this->name = newName;

  return _this;
}

// End of Class Shape


int main() {
  string testString = "test";
  Shape *s[] = {
    Shape_Shape((Shape *)malloc(sizeof(Shape)), testString)
  };

  for (int i = 0; i < sizeof(s)/sizeof(*s); i++) {
    // s[i]->VPointer[PRINT_INDEX].void_method(s[i]);
    s[i]->VPointer[PRINT_INDEX].void_method(s[i]);
  }

  return 0;
}