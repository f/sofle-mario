void main_encoder(bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case _RAISE:
            if (clockwise) {
                tap_code16(KC_MREDO);
            } else {
                tap_code16(KC_MUNDO);
            }
            break;
        default:
            if (clockwise) {
                tap_code(KC_BRMU);
            } else {
                tap_code(KC_BRMD);
            }
    }
}

void second_encoder(bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case _LOWER:
            if (clockwise) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_MPRV);
            }
            break;
        default:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        main_encoder(clockwise);
    } else if (index == 1) {
        second_encoder(clockwise);
    }
    return true;
}