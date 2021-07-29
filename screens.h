#include "keylog.h"
#include "main_screen.h"
#include "second_screen.h"

char wpm_str[10];

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_anim();
        oled_set_cursor(0, 0);
        sprintf(wpm_str, "WPM: %03d", get_current_wpm());
        oled_write(wpm_str, false);
    }
}
