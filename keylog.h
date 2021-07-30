char keylog_str[24];
const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if (keycode < 60) {
        name = code_to_name[keycode];
    } else {
        name = ' ';
    }
    switch (keycode) {
        case KC_BSPC:
            snprintf(keylog_str, sizeof(keylog_str), "<<<<<");
            break;
        case RAISE_UP:
            snprintf(keylog_str, sizeof(keylog_str), "^ RAI");
            break;
        case ALT_RIGHT:
            snprintf(keylog_str, sizeof(keylog_str), "> ALT");
            break;
        case SLS_SFT:
            snprintf(keylog_str, sizeof(keylog_str), "/ SFT");
            break;
        case ESC_ADJ:
            snprintf(keylog_str, sizeof(keylog_str), "E ADJ");
            break;
        case LSFT_CAPS:
        case KC_LSFT:
        case KC_RSFT:
            snprintf(keylog_str, sizeof(keylog_str), ">SFT<");
            break;
        case KC_RALT:
        case KC_LALT:
            snprintf(keylog_str, sizeof(keylog_str), ">ALT<");
            break;
        case KC_LGUI:
        case KC_RGUI:
            snprintf(keylog_str, sizeof(keylog_str), ">CMD<");
            break;
        case KC_LCTL:
        case KC_RCTL:
            snprintf(keylog_str, sizeof(keylog_str), ">CTL<");
            break;
        default:
            snprintf(keylog_str, sizeof(keylog_str), "> %c <", name);
            break;
    }
}