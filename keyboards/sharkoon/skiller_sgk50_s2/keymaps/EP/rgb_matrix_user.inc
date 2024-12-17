RGB_MATRIX_EFFECT(DEFAULT)
RGB_MATRIX_EFFECT(test_effect_1)


#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS




static bool DEFAULT(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i,
            abs(((  (g_rgb_timer / 10)  +  (-g_led_config.point[i].x*2)  +  ((g_led_config.point[i].y/2)*3)  ) % 510) - 255),
            0,
            abs(((  (g_rgb_timer / 10)  +  (-g_led_config.point[i].x*2)  +  ((g_led_config.point[i].y/2)*3)  +  255  ) % 510) - 255)
            );
    }

    return rgb_matrix_check_finished_leds(led_max);
}



static bool test_effect_1(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, 220, 0, 255);
    }

    return rgb_matrix_check_finished_leds(led_max);
}




#endif//RGB_MATRIX_CUSTOM_EFFECT_IMPLS