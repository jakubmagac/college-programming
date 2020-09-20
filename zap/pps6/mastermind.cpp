#include "mastermind.h"
#include "lcd_wrapper.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include <assert.h>
#include "string.h"
#include <Arduino.h>

char* generate_code(bool repeat, int length)
{
    if(length < 1 || (repeat == false && length > 10)) return NULL;

    char *code = (char*) calloc(length, sizeof(int));
    int gen;

    for(int i=0;i<length;i++){
        gen = (rand() % 10) +48;
        if(repeat == false && i > 0)
            while(strchr(code, gen)) gen = (random(0,10) +48);
        code[i] = gen;
    }

    code[length] = '\0';
    return code;
}



void turn_off_leds()
{
  for(int i=6;i<14;i++){
     digitalWrite(i, LOW);
  }
}

void render_leds(const int peg_a, const int peg_b)
{
  int ledB[] = {6,8,10,12}; int ledR[] = {7,9,11,13};
  int s = 0;

  for(int i=0;i<peg_a;i++){
    digitalWrite(ledR[i],HIGH);
    s++;  
  }

  for(int i=0;i<peg_b;i++){
    digitalWrite(ledB[i+s],HIGH);  
  }
}

void welcome()
{
  lcd_print_at(0,0,"MasterMind");
  delay(4000);
  lcd_clear();
  lcd_print_at(0,0,"Guess my number");
  lcd_print_at(0,1,"Your guess: 0000");
}

void ending()
{
  for(int i=0;i<4;i++){
    turn_off_leds();
    delay(200);
    render_leds(4,0);
    delay(500);
    turn_off_leds();
    delay(200);
    render_leds(0,4);
    delay(500);
  }
  turn_off_leds();
}

void check_if_won(char* guess, char* secret, int chance_to_guess)
{
  char buff[13];
  int good, wrong;
  get_score(secret, guess, &good, &wrong);    

  if(strcmp(guess, secret) == 0){
    lcd_clear();
    sprintf(buff, "%d: %s %dA%dB", chance_to_guess, guess, good, wrong);
    lcd_print_at(0,0,buff);
    sprintf(buff, "Won with %d guess!", chance_to_guess);
    lcd_print_at(0,1,buff);
    ending();
  }else{
    lcd_clear();
    sprintf(buff, "%d: %s %dA%dB", chance_to_guess, guess, good, wrong);
    lcd_print_at(0,0,buff);
    sprintf(buff, "My code was %s", secret);
    lcd_print_at(0,1,buff);
    ending();
  }  
}

void debounce(int pin)
{
  while(digitalRead(pin));
  delay(300);  
}

void print_change(char *guess)
{
  char buffer[20];
  sprintf(buffer, "Your guess: %s", guess);
  lcd_print_at(0,1,buffer);
}

void get_new_try(int chance_to_guess, char* guess, int good, int wrong)
{
  char buff[13];
  lcd_clear();
  sprintf(buff, "%d: %s %dA%dB", chance_to_guess, guess, good, wrong);

  lcd_print_at(0,0,buff);
  lcd_print_at(0,1,"Your guess: 0000");
}

void get_score(const char* secret, const char* guess, int* peg_a, int* peg_b)
{
    *peg_a = 0; *peg_b = 0;
    char secret_copy[strlen(secret)+1];
    strcpy(secret_copy, secret);

    for(int i=0;i<strlen(guess);i++){
       if(secret_copy[i] == guess[i]) *peg_a+=1;
    }

    for(int i=0;i<strlen(guess);i++){
        for(int j=0;j<strlen(guess);j++){
            if(secret_copy[i] == guess[j] && i != j){
                *peg_b+=1;
                secret_copy[i] = '*';
            } 
        }  
    }   
}

void render_history(char* secret, char** history, const int entry_nr)
{
  int good = 0; int wrong =0;
  char buff[13];

  get_score(secret, history[entry_nr], &good, &wrong);    
      
  turn_off_leds();
  render_leds(good, wrong);

  sprintf(buff, "%d: %s %dA%dB", entry_nr+1, history[entry_nr], good, wrong);
  lcd_print_at(0,0,buff);
}


void play_game(char* secret)
{
  int peg_a = 0; int peg_b = 0;
  int list, chance_to_guess = 0;
  char guess[] = "0000";
  char **history = calloc(10,sizeof(char*));
  for(int i=0;i<10;i++){
    history[i] = calloc(5, sizeof(char));  
  }
  char buff[13];
  welcome();
  int history_step = 0;

  while(1){
    if(digitalRead(BTN_1_PIN)){
      list = 0;
      delay(200);
      while(digitalRead(BTN_1_PIN)){
        delay(200);
        if(digitalRead(BTN_2_PIN)){
          debounce(3);
          if(history_step > 0) history_step--;
          render_history(secret,history,history_step);
          list=1;
        }
        if(digitalRead(BTN_3_PIN)){
          debounce(4);
          if(history_step < 10 && history_step < chance_to_guess-1) history_step++;
          render_history(secret,history,history_step);
          list=1;
        }
      }

      if(list == 0){
        debounce(2);
        guess[0] += 1;  
        if(guess[0] > 57) guess[0] = 48;
        print_change(guess);
      }
    }
    
    if(digitalRead(BTN_2_PIN)){
      debounce(3);
      guess[1] += 1;  
      if(guess[1] > 57) guess[1] = 48;
      print_change(guess);
    }
    
    if(digitalRead(BTN_3_PIN)){
      debounce(4);
      guess[2] += 1;  
      if(guess[2] > 57) guess[2] = 48;
      print_change(guess);
    }
    
    if(digitalRead(BTN_4_PIN)){
      debounce(5);
      guess[3] += 1;  
      if(guess[3] > 57) guess[3] = 48;
      print_change(guess);
    }

    if(digitalRead(BTN_ENTER_PIN)){
      while(digitalRead(BTN_ENTER_PIN));
      delay(300);
      chance_to_guess++;

      if(chance_to_guess > 9 || strcmp(guess, secret) == 0) break;
      get_score(secret, guess, &peg_a, &peg_b); 

      for(int i=0;i<4;i++){
        history[chance_to_guess-1][i] = guess[i];
      }
      history[chance_to_guess-1][4] = '\0';
      
      lcd_clear();
      turn_off_leds();
      render_leds(peg_a, peg_b);
      
      sprintf(buff, "%d: %s %dA%dB", chance_to_guess, guess, peg_a, peg_b);
      lcd_print_at(0,1,buff);
      
      get_new_try(chance_to_guess, guess, peg_a, peg_b);
      guess[0]='0';guess[1]='0';guess[2]='0';guess[3]='0';
    } 
  }

  check_if_won(guess, secret, chance_to_guess);
  delay(5000);
}