#include <iostream>
#include "bitmap.h"

int main(int argc, char * argv[])
{
    Bitmap test(5, 5, 16);
    test.write("./test.bmp");
}


