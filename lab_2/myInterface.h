#include "mySimpleComputer.h"
#include "myTerm.h"
#include <sys/ioctl.h>
#include <unistd.h>

#define UL_CORNER 'l' // левый верхний угол
#define UR_CORNER 'k' // правый верхний угол
#define DR_CORNER 'j' // правый нижний угол
#define DL_CORNER 'm' // левый нижний угол
#define H_LINE 'q'    // горизонтальная линия
#define V_LINE 'x'    // вертикальная линия
#define FILL 'a'      // штриховка

extern int instruction_counter;

int print_symbol (char symbol);
int print_box (int x, int y, int width, int height);
int drawing_boxes ();
int drawing_texts ();
int drawing_flags ();
int drawing_memory ();
int ui_initial ();
