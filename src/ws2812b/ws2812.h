#include "ws2812.pio.h"
// All my drivers will be in c going forward this will be converted to c


#ifndef ws2812b_H
#define ws2812b_H

class ws2812{
    public:
        /// @brief Initilize the PIO State maschine and allocate memory for the led buffer
        /// @param pin Set the ws2812 data PIN
        /// @param number_of_leds Sets the number of LED's that are conectet
        ws2812(
            uint8_t pin,
            int number_of_leds
        );
    private:
        /// @brief Data Pin off the LED's
        uint8_t pin;
        /// @brief Number off the LED's
        int number_of_leds;
        /// @brief Array storage off the LED's color
        uint32_t* led;

        /// @brief Frequency off the Com 
        float freq = 800000;
        /// @brief Number off the PIO instance
        PIO pio;
        /// @brief Number off the State Maschin
        uint sm;
        /// @brief Pusches 4 Bytes off Data to the LED Data Pin
        /// @param pixel_grb B Bytes off data to send
        void put_pixel(uint32_t pixel_grb);// Give 24 Bits to the SM to put on the Output
        /// @brief Combines 3 Bytes of Data into one 32 Bits Value
        /// @param r Red Color field
        /// @param g Green Color field
        /// @param b Blue Color field
        /// @return Returns the combined 4 Byte Value off the LED's
        uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b); // Convert 3 8 Bit numbers to one 24 Bit number that can be sent to to Pixel

        uint32_t convertHSV_urgb_u32(float H, float S,float V);
    public:
        /// @brief Pushes all the Data to the LED's
        void flip(); // Update all Pixel Colors from the Array Storage
        /// @brief Set one off the LED's with rgb values
        /// @param r Red
        /// @param g Green
        /// @param b Blou
        /// @param number Number of the LED;
        void setRGB(uint8_t r, uint8_t g, uint8_t b, int number); 
        /// @brief Set one off the LED's with a RGB Hex value
        /// @param hex RGB Hex code
        /// @param number Number of the LED
        void setHEX(uint32_t hex, int number);

        void setAllRGB(uint8_t r, uint8_t g, uint8_t b);

        void setAllHEX(uint32_t hex);

        void setLEDs(uint16_t *data, int len);
};

#endif