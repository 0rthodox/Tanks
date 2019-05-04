#include "windows.h"

int scale = 40;

int main() {

    init_window w1;
    if(w1.work()) {
        main_window mw;
        mw.work();
    }

    return 0;

}
