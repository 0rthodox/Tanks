#include "windows.h"

int scale = 60;

texture_keeper T(2);

int main() {

    init_window iw;
    iw.work();

    main_window mw;
    mw.work();

    return 0;

}
