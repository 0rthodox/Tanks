#include "windows.h"

int scale = 60;

int rate = 30;

texture_keeper T(3);

font F;

int main() {

    init_window iw;
    main_window mw;
    if(iw.work())
        mw.work();

    return 0;

}
