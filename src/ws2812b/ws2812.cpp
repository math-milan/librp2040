#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "pico/stdlib.h"
#include "ws2812.h"
#include <bits/stdc++.h>


ws2812::ws2812(uint8_t pin, int number_of_leds){
    this->pin = pin;
    this->number_of_leds = number_of_leds;
    this->led = new uint32_t[number_of_leds];
    pio = pio0;
    uint offset = pio_add_program(pio, &ws2812_program);
    sm = pio_claim_unused_sm(pio, true);
    ws2812_program_init(pio, sm, offset, pin, freq, false);
}

void ws2812::put_pixel(uint32_t pixel_grb){
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

uint32_t ws2812::urgb_u32(uint8_t r, uint8_t g, uint8_t b){
    return ((uint32_t) (r) << 8) | ((uint32_t) (g) << 16) | (uint32_t)  (b);
}

uint32_t ws2812::convertHSV_urgb_u32(float H, float S,float V){
        if(H>360 || H<0 || S>1 || S<0 || V>1 || V<0){
        return 0;
    }
    float f = H / 60 - abs(H/60);
    float p = V * (1 - S);
    float q = V * (1 - S * f);
    float t = V * (1 - S * (1 - f));

    float r, g, b;
    // int r, g, b;
    if(H >= 0 && H < 60){
       r = V;
       g = t;
       b = p;
    }
    else if(H >= 60 && H < 120){
        r = q;
        g = V;
        b = p;
    }
    else if(H >= 120 && H < 180){
        r = p;
        g = V;
        b = t;
    }
    else if(H >= 180 && H < 240){
        r = p;
        g = q;
        b = V;
    }
    else if(H >= 240 && H < 300){
        r = t;
        g = p;
        b = V;
    }
    else{
        r = V;
        g = p;
        b = q;
    }
    return this->urgb_u32(r, g, b);
}

void ws2812::setRGB(uint8_t r, uint8_t g, uint8_t b, int number){
    if (this->number_of_leds < number){
        return;
    }
    led[number] = this->urgb_u32(r, g, b);
}


void ws2812::setHEX(uint32_t hex, int number){
    if (this->number_of_leds < number){
        return;
    }
    led[number] = hex;
}

void ws2812::setAllRGB(uint8_t r, uint8_t g, uint8_t b){
    for (int i = 0; i < this->number_of_leds; i++){
        led[i] = this->urgb_u32(r, g, b);
    }
}


void ws2812::setAllHEX(uint32_t hex){
    for (int i = 0; i < this->number_of_leds; i++){
        led[i] = hex;
    }
}


void ws2812::flip(){
    for (int i = 0; i < this->number_of_leds; i++)
    {
        for (int x = i; x < this->number_of_leds; x++)
        {
            put_pixel(led[x]);
        }
        
    }
}

void ws2812::setLEDs(uint16_t *data, int len){
    if (number_of_leds < len){
        return;
    }
    memcpy(led, data, len);
}