// Author: John-William Lebel, 2021-04-10, creation

// simple utility class that helps to compute voltage divider circuits

#ifndef VOLTAGE_DIVIDER_H
    #define VOLTAGE_DIVIDER_H

    class VoltageDivider
    {
        public:
            static inline constexpr float getVoltageFactor(float r1, float r2);
            static inline constexpr float getInverseVoltageFactor(float r1, float r2);
            
        private:

    };

#endif