#include "lcd_wrapper.h"
#include "mastermind.h"

void setup(){
    Serial.begin(9600);
    pinMode(BTN_1_PIN,INPUT);       
    pinMode(BTN_2_PIN,INPUT);       
    pinMode(BTN_3_PIN,INPUT);       
    pinMode(BTN_4_PIN,INPUT);       
    pinMode(BTN_ENTER_PIN,INPUT);   
    pinMode(LED_BLUE_1, OUTPUT);     
    pinMode(LED_RED_1, OUTPUT);      
    pinMode(LED_BLUE_2, OUTPUT);     
    pinMode(LED_RED_2, OUTPUT);      
    pinMode(LED_BLUE_3, OUTPUT);     
    pinMode(LED_RED_3, OUTPUT);      
    pinMode(LED_BLUE_4, OUTPUT);     
    pinMode(LED_RED_4, OUTPUT);
    pinMode(A1, INPUT);
    lcd_init();
}

void loop(){
    randomSeed(analogRead(A1));
    char* secret = generate_code(false,4);
    Serial.println(secret);
    play_game(secret);
    delay(4000);
    lcd_clear();
    free(secret);
}