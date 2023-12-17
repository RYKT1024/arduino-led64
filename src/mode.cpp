#include <mode.h>
#include <Arduino.h>
#include <led.h>
#include <config.h>

Config *onboardConfig[5];
BreathConfig breathConfig;
BreathConfig breathConfig_1;
StaticConfig staticConfig;
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

    int colors[64][3] = {
        {255,0,0}, {255,0,0}, {255,0,0}, {255,0,0}, {255,0,0}, {255,0,0}, {255,0,0}, {255,0,0}, 
        {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255},
        {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255},
        {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255},
        {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255},
        {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255},
        {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {255,0,0},
        {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {255,0,0}, {255,0,0}
    };
    staticConfig.mode = "static";
    staticConfig.brightness = 0.2;
    for (int i=0; i<64; i++) {
        staticConfig.colors[i][0] = colors[i][0];
        staticConfig.colors[i][1] = colors[i][1];
        staticConfig.colors[i][2] = colors[i][2];
    }
    onboardConfig[2] = &staticConfig;

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
    else if(!strcmp(mode, "static")) {
        StaticConfig *configPtr = static_cast<StaticConfig *>(config);
        StaticConfig *staticConfig = new StaticConfig;
        *staticConfig = *configPtr;

        onboardConfig[onboard] = staticConfig;
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

Config **get_onboard() {
    return onboardConfig;
}

void loop_mode() {
    Config *config = onboardConfig[selected];
    const char *mode = config->get_mode();

    if(!strcmp(mode, "breath")) {
        BreathConfig *configPtr = static_cast<BreathConfig *>(config);
        led_static_switch(false);
        loop_led_breath(configPtr->color, configPtr->speed, configPtr->brightness);
        // configPtr->show_detail();
        // Serial.println(configPtr->get_json());
    }
    else if(!strcmp(mode, "gradient")) {
        GradientConfig *configPtr = static_cast<GradientConfig *>(config);
        led_static_switch(false);
        loop_led_gradient(configPtr->color_from, configPtr->color_to, configPtr->speed, configPtr->brightness);
        // configPtr->show_detail();
        // Serial.println(configPtr->get_json());
    }
    else if(!strcmp(mode, "static")) {
        StaticConfig *configPtr = static_cast<StaticConfig *>(config);
        loop_led_static(configPtr->colors, configPtr->brightness);
        led_static_switch(true);
        // configPtr->show_detail();
        // Serial.println(configPtr->get_json());
    }
}