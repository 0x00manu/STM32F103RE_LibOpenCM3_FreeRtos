#ifndef LED_HPP
#define LED_HPP
    class Led
    {
    private:
        int pin;
    public:
        Led(int Pin);
        ~Led();
        void on(void);
    };
    
    Led::Led(int Pin)
    {
        pin = Pin;
    }
    
    Led::~Led()
    {
    }
    
#endif