#include <mode.h>
#include <Arduino.h>
#include <led.h>
#include <config.h>

Config *onboardConfig[5];
BreathConfig breathConfig;
BreathConfig breathConfig_1;
BreathConfig breathConfig_2;
GradientConfig gradientConfig;
GradientConfig gradientConfig_1;

int selected = 0;

void setup_mode() {
    setup_led();

    breathConfig.mode = "breath";
    breathConfig.brightness = 0.1;
    breathConfig.speed = 1.5;
    breathConfig.color[0] = 120;
    breathConfig.color[1] = 240;
    breathConfig.color[2] = 0;
    onboardConfig[0] = &breathConfig;

    breathConfig_1.mode = "breath";
    breathConfig_1.brightness = 0.4;
    breathConfig_1.speed = 0.8;
    breathConfig_1.color[0] = 255;
    breathConfig_1.color[1] = 0;
    breathConfig_1.color[2] = 120;
    onboardConfig[1] = &breathConfig_1;

    breathConfig_2.mode = "breath";
    breathConfig_2.brightness = 0.2;
    breathConfig_2.speed = 0.2;
    breathConfig_2.color[0] = 0;
    breathConfig_2.color[1] = 240;
    breathConfig_2.color[2] = 120;
    onboardConfig[2] = &breathConfig_2;

    gradientConfig.mode = "gradient";
    gradientConfig.brightness = 0.6;
    gradientConfig.speed = 0.5;
    gradientConfig.color_from[0] = 100;
    gradientConfig.color_from[1] = 50;
    gradientConfig.color_from[2] = 0;
    gradientConfig.color_to[0] = 200;
    gradientConfig.color_to[1] = 0;
    gradientConfig.color_to[2] = 50;
    onboardConfig[3] = &gradientConfig;

    gradientConfig_1.mode = "gradient";
    gradientConfig_1.brightness = 0.1;
    gradientConfig_1.speed = 1;
    gradientConfig_1.color_from[0] = 0;
    gradientConfig_1.color_from[1] = 250;
    gradientConfig_1.color_from[2] = 140;
    gradientConfig_1.color_to[0] = 40;
    gradientConfig_1.color_to[1] = 100;
    gradientConfig_1.color_to[2] = 50;
    onboardConfig[4] = &gradientConfig_1;

}

void set_mode(int onboard, Config *config) {
    const char *mode = config->get_mode();

    if(!strcmp(mode, "breath")) {
        BreathConfig *configPtr = static_cast<BreathConfig *>(config);
        BreathConfig *breathConfig = new BreathConfig();
        *breathConfig = *configPtr;

        onboardConfig[onboard] = breathConfig;
    }
    else if(!strcmp(mode, "gradient")) {
        GradientConfig *configPtr = static_cast<GradientConfig *>(config);
        GradientConfig *gradientConfig = new GradientConfig;
        *gradientConfig = *configPtr;

        onboardConfig[onboard] = gradientConfig;
    }

    selected = onboard;
}

int mode_switch(int select) {
    if(select == -1) 
        selected = (selected + 1) % 5;
    else
        selected = select;
    return selected;
}

void loop_mode() {
    Config *config = onboardConfig[selected];
    const char *mode = config->get_mode();

    if(!strcmp(mode, "breath")) {
        BreathConfig *configPtr = static_cast<BreathConfig *>(config);
        loop_led_breath(configPtr->color, configPtr->speed, configPtr->brightness);
        // configPtr->show_detail();
    }
    else if(!strcmp(mode, "gradient")) {
        GradientConfig *configPtr = static_cast<GradientConfig *>(config);
        loop_led_gradient(configPtr->color_from, configPtr->color_to, configPtr->speed, configPtr->brightness);
        // configPtr->show_detail();
    }
}