#include "windows.h"

int scale = 60;

texture_keeper T(3);

int main() {

    init_window iw;
    main_window mw;
    if(iw.work())
        mw.work();

    return 0;

}
