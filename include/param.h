#ifndef PARAM_H
#define PARAM_H
#include <Arduino.h>
    #define TEST_TIMER false
    #if TEST_TIMER
        #define ALARM_DURATION_4HRinSeconds 60
        #define ALARM_DURATION_8HRinSeconds 90
        #define ALARM_DURATION_12HRinSeconds 120
        #define FILTER_GOOD_HOURS 60
        #define FILTER_AVG_HOURS 120
        #define FILTER_BAD_HOURS 180
    #else
        #define ALARM_DURATION_4HRinSeconds 14400
        #define ALARM_DURATION_8HRinSeconds 28800
        #define ALARM_DURATION_12HRinSeconds 43200
        #define FILTER_GOOD_HOURS 750
        #define FILTER_AVG_HOURS 1400
        #define FILTER_BAD_HOURS 1500
    #endif

    #define FIRING_TIME_uS_HIGH 2000
    #define FIRING_TIME_uS_MID 3300
    #define FIRING_TIME_uS_LOW 4200
    
    #define EEPROM_ADDRESS_HOURS0 0//0,1,2
    #define EEPROM_ADDRESS_HOURS1 3//3,4,5
    #define EEPROM_ADDRESS_MINUTES0 6//6,7,8
    #define EEPROM_ADDRESS_MINUTES1 9//9,10,11
    #define RECV_PIN PD7
    #define slaveSelectPin (int)10 // Example SS pin
    
    //  ir remote sends 4-byte-code
    #define IRcode_4Byte_ONOFF 0xB946FF00UL
    #define IRcode_4Byte_FANMINUS 0xBB44FF00UL
    #define IRcode_4Byte_TIMER 0xBF40FF00ul
    #define IRcode_4Byte_FANPLUS 0xBC43FF00UL
    #define IRcode_4Byte_AUTO 0xE916FF00UL
    #define IRcode_4Byte_IONIZER 0xEA15FF00UL
    #define IRcode_4Byte_CHILD 0xE619FF00UL
    #define IRcode_4Byte_SLEEP 0xF20DFF00UL

    /// @brief 4-byte-ir-receiver code mapped to 1-byte
    typedef enum{
        SpiByteForRemoteCode_INVALID='\0',
        SpiByteForRemoteCode_ONOFF='A',
        SpiByteForRemoteCode_FANMINUS='B',
        SpiByteForRemoteCode_TIMER='C',
        SpiByteForRemoteCode_FANPLUS='D',
        SpiByteForRemoteCode_IONIZER='E',
        SpiByteForRemoteCode_AUTO='F',
        SpiByteForRemoteCode_CHILDLOCK='G',
        SpiByteForRemoteCode_SLEEP='H',
    }SpiByteForRemoteCode_t;

    #define RX_PIN PA10//1
    #define TX_PIN PA15//2
    #define VBAT 1      //3
    //====== port C =====//
    #ifdef __STM32F103xE_H
        #define segA PC0    //4
        #define segB PC1    //5
        #define segC PC2    //6
        #define segD PC3    //7
        #define segE PC4    //8
        #define segF PC5    //9
        #define segG PC6    //10
        #define segH PC7    //11
    #else
        #define segA PC13    //4
        #define segB PC13    //5
        #define segC PC13    //6
        #define segD PC13    //7
        #define segE PC13    //8
        #define segF PC13    //9
        #define segG PC13    //10
        #define segH PC13    //11
    #endif
    //PC8 FREE
    //PC9 FREE
    //PC10 FREE
    //PC11 FREE    
    #define Auto_led PC12//12
    #define MOSI PC13    //13
    #define MISO PC14    //14
    #define SCK PC15     //15
    /// @brief Slave Select pin
    #define SS PC10//FREE
    //====== port A =====//
    #define FAN_PLUS PA0    //16
    #define FAN_MINUS PA1    //17
    #define TIMER PA2    //18
    #define FILTER PA3    //19
    #define ChildLock PA4    //20 SPI1_NSS
    #define OnOff PA5    //21
    #define Sensor_ADC_TX PA6    //22
    #define AutoMode PA7    //23
    #define FAN_PWM PA8    //24
    #define Inizier PA9    //25
    //#define PA10
    #define INT1 PA11   //ZERO DETECT
    #define SleepMode PA12    //27
    #define P_DATA PA13    //28
    #define P_CLK PA14    //29
    //#define PA15
    //====================//
    // PA5, PA6, PA7 (SPI1), PB3, PB4, PB5 (SPI2), and PB15 (SPI3)
    //====== port B =====//
    #define CS3 PB0    //30
    #define CS2 PB1    //31
    #define CS1 PB2    //32
    //#define x PB3
    //#define x PB4
    #define Inizier_Led PB5    //33
    #define RED_HEALTH PB6    //34
    #define GREEN_HEALTH PB7    //35
    #define BUZZER PB8    //36
    #define SENSOR_DO_RX PB9    //37
    #define SCL PB10    //38
    #define SDA PB11    //39
    #define CHILDLOCK_LED PB12    //40
    #define FILTER_R PB13    //41
    #define FILTER_G PB14    //42
    #define FILTER_B PB15    //43
    #define FILTER_HOURS_GUD 0 //0~750
    #define FILTER_HOURS_AVG 750 //751~1500
    #define FILTER_HOURS_BAD 1500   //>1500
    //====================//
    #define HEALTH_LED_GREEN_PM25 120
    #define BUZZER_ON_TIME_MS 50
    #define DISPLAY_BUSY_TIME_MAX 3000//MS
    #define TOUCHPAD_BUSY_TIME_MAX 3000//MS
    #define TOUCHPAD_BUSY_TIME_SECONDS 3
    typedef void (*PatternFunction)();
#endif