/* 
* ░█▀▄░█▀▄░▀█▀░█░░░█░░░▀█▀░█▀█░█▀█░▀█▀░░░█▀▄░█▀▀░█▀▀░█░░░█▀█░█░█
* ░█▀▄░█▀▄░░█░░█░░░█░░░░█░░█▀█░█░█░░█░░░░█▀▄░█▀▀░█▀▀░█░░░█░█░█▄█
* ░▀▀░░▀░▀░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░▀░▀░░▀░░░░▀░▀░▀▀▀░▀░░░▀▀▀░▀▀▀░▀░▀
* Project:    Brilliant Reflow
* Code by:    Anuradha Gunawardhana
* version:    v1.0.0
* Date:       2022.01.30
* 
* Hardware:   Display - ST7735(128x160)TFT
*             Thermocouple Interface - MAX6675
*             Microcontroller - STM32F103C8T6
*             ST-LINK - CubeProgrammer - https://www.st.com/en/development-tools/stm32cubeprog.html
* 
* Libraries:  PID(v1.2.0) by Brett Beauregard : https://github.com/br3ttb/Arduino-PID-Library
*             Ucglib(v1.5.2) by Oliver: https://github.com/olikraus/ucglib
*             MAX6675(v1.1.0) by Adafruit: https://github.com/adafruit/MAX6675-library
* 
* Arduino STM32 Boards:(v2.0.0) https://github.com/stm32duino/Arduino_Core_STM32
* 
* Note: If Ucglib did not compile with the STM32(arm architecture) add the following lines just 
*       after "Ucglib.h" line at the begining of the 'Ucglib.cpp'. 
*       
*                 #if defined(__NOP)
*                 #undef __NOP
*                 #endif
*                 #define __NOP __asm volatile ("nop")
*                 #endif
*       
*       You can find the Ucglib.cpp' on; Windows: Documents/Arduino/libraries/Ucglib/src/Ucglib.cpp
*                                        Linux: /home/USERNAME/Arduino/libraries/Ucglib/src/Ucglib.cpp
* 
* License: MIT License
* 
* Copyright (c) 2021 Anuradha Gunawardhana
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include <SPI.h>
#include <PID_v1.h>
#include <EEPROM.h>
#include "Ucglib.h"
#include "max6675.h"

// Unique identifiers for colors
#define black   100
#define yellow  101
#define red     102
#define green   103
#define blackOnYellow 201
#define yellowOnBlack 202

#define SSR_out PB8

#define btnDebounceDelay  300
#define btnHoldDelay     1000
#define btnHoldUpdateRate  50
#define tempSampleRate    200

Ucglib_ST7735_18x128x160_HWSPI ucg(PA2, PA4, PA3);
MAX6675 thermocouple(PA9, PA8, PA10);

bool debug = false;        // Show PID output info on the disply when heating

bool blinkState = false;

bool editSettings = false;
bool resetRequest = false;
bool saveRequest = false;
bool save_pressed = false;
bool reset_pressed = false;

double default_K_pid[3] = {4, 0.01, 5};
double K_pid[3]={0,0,0};
String pid[3] = {"Kp:","Ki:","Kd:"};
String pid_[3] = {"P","I","D"};
bool pidInit = false;
double Setpoint, Input, Output;
PID myPID(&Input, &Output, &Setpoint, K_pid[0], K_pid[1], K_pid[2], DIRECT);

byte p4LastSelect_v = 1;
byte p4LastSelect_h = 1;

bool backRequest = false;
bool startStopRequest = false;
bool settingsPageRequest = false;
byte request_draw_profile_page = 0;

unsigned long lstTempRead = 0;
unsigned long lstBlink = 0;
float temp = 0;
byte tempPos[2] = {94, 52};

bool heating = false;
unsigned long lstPlotDraw = 0;
float plotTime = 0;
float plotDrawRate = 500;  // in milliseconds

int default_profiles[3][6][2] =  {{{25, 0}, {150, 100}, {180, 160}, {240, 200}, {240, 210}, {100, 300}},   // Profile 1
                                  {{25, 0}, {130, 80}, {150, 240}, {230, 300}, {230, 310}, {100, 400}},    // Profile 2
                                  {{25, 0}, {130, 60}, {150, 230}, {240, 290}, {240, 310}, {100, 380}}};   // Profile 3
int profiles[3][6][2];

int maxTemp = 0;
int minTemp = 0;
int maxTime = 0;

const byte main_btn_pos[3][2] = {{70, 20}, {40, 20}, {10, 20}};
const byte main_btn_text_pos[3][2] = {{77, 51}, {47, 51}, {17, 51}};
const String main_btn_labels[3] = {"PROFILE 1", "PROFILE 2", "PROFILE 3"};
const byte main_btn_height = 25;
const byte main_btn_width = 120;

byte h_btn_pos[3][2] = {{83, 5}, {83, 56}, {83, 107}};
byte h_btn_text_pos[3][2] = {{87, 17}, {87, 66}, {87, 120}};
String h_btn_labels[3] = {"BACK", "START", "EDIT"};
byte h_btn_height = 18;
byte h_btn_width = 47;

volatile byte vertical_pos = 1;
volatile byte horizontal_pos = 1;

byte page = 0;
byte previosPage = 0;

volatile unsigned long lstBtnBounce = 0;
volatile unsigned long hold_start = 0;
unsigned long last_val_change = 0;

void setup(void) {
  pinMode(PB3, INPUT_PULLUP);
  pinMode(PB4, INPUT_PULLUP);
  pinMode(PB5, INPUT_PULLUP);
  pinMode(PB6, INPUT_PULLUP);
  pinMode(PB7, INPUT_PULLUP);
  pinMode(PB8, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(PB3), up, FALLING);
  attachInterrupt(digitalPinToInterrupt(PB4), center, RISING);
  attachInterrupt(digitalPinToInterrupt(PB5), right, FALLING);
  attachInterrupt(digitalPinToInterrupt(PB6), down, FALLING);
  attachInterrupt(digitalPinToInterrupt(PB7), left, FALLING);

  ucg.begin(UCG_FONT_MODE_SOLID);
  ucg.setFontPosBaseline();
  ucg.setPrintDir(1);
  draw_main_page();

  // initiate the emulated EEPROM
  if (!EEPROM_check()) EEPROM_set_default();
  EEPROM_get();

  // PID Controller
  Setpoint = 50;
  temp = thermocouple.readCelsius();
  Input = temp;
  myPID.SetOutputLimits(0, 255);
  myPID.SetTunings(K_pid[0], K_pid[1], K_pid[2]);
}

void loop(void) {
  if (backRequest) {
    backRequest = false;
    goBack();
  }
  if (startStopRequest) {
    startStopRequest = false;
    startStop();
  }
  if (request_draw_profile_page != 0) {
    request_draw_profile_page = 0;
    horizontal_pos = 1; // select the "BACK"
    draw_profile_page(vertical_pos);
  }
  if (settingsPageRequest){
    settingsPageRequest = false;
    draw_settings_page(1);
  }
  if (resetRequest){
    resetRequest = false;
    EEPROM_set_default();
    EEPROM_get();         // get the new save values from the EEPROM
    default_h_btn_para();
    page = previosPage;   // setting the correct page
    draw_settings_page(3);
  }
  if (saveRequest){
    saveRequest = false;
    EEPROM_save();
    EEPROM_get();
    default_h_btn_para();
    page = previosPage;   // setting the correct page
    draw_settings_page(2);
  }
  if (heating) { // Plot the temperature on the graph
    if (!pidInit) {
      pidInit = true;
      myPID.SetMode(AUTOMATIC);
    }
    // Show the real time value of the Temperature
    setColor(yellowOnBlack);
    ucg.setFont(ucg_font_6x12_mr);  // use 'mr' font to completely fill the background

    if ((millis() - lstTempRead) > tempSampleRate) { // Read the thermocouple in the set interval
      temp = thermocouple.readCelsius();
      lstTempRead = millis();
    }
    ucg.setPrintPos(tempPos[0], tempPos[1]);
    ucg.print(String(temp));
    if (temp < 100.0){
      setColor(black);
      ucg.drawBox(tempPos[0]+1,tempPos[1]+30,7,5); // to clear the last decimal when going from 100.00 to 99.75 
    }

    if ((millis() - lstPlotDraw) > plotDrawRate) {  // draw the plot in a set interval
      plotTime = plotTime + plotDrawRate / 1000;
      setColor(yellowOnBlack);
      ucg.setPrintPos(tempPos[0]-10, tempPos[1]);
      ucg.print(String(plotTime));
      float currentTemp = thermocouple.readCelsius();

      float T = ((60 * (currentTemp - minTemp)) / (maxTemp - minTemp)) + 10;  // height of plot is 60
      float t = ((120 * plotTime) / maxTime) + 20;                // width of plot is 120

      if (T > 70) T = 70;     // use constrain(x, a, b)
      if (T < 11) T = 11;
      if (t < 21) t = 21;
      setColor(red);
      ucg.drawPixel(T, t);     // Plot the temperature on the graph

      if(debug){
        ucg.setPrintPos(73,35);           
        ucg.print("out:"+String(Output));
        ucg.setPrintPos(63,35);           
        ucg.print("set:"+String(Setpoint));
        for (byte i=0; i<=2; i++){
          ucg.setFont(ucg_font_6x12_tr);
          ucg.setPrintPos(72 - i*10, 127);
          ucg.print(pid_[i]);
          ucg.setFont(ucg_font_6x12_mr);
          ucg.setPrintPos(72 - i*10, 134);
          ucg.print(K_pid[i]);
        }
      }

      if (plotTime > maxTime) {
        startStopRequest = true;
      }
      lstPlotDraw = millis();
    }
    blinking_dot(red);
    // PID Controller
    calculateSetPoint();  // calculate the setpoint based on the plot
    Input = temp;         // if the temperature function directly provided, the displaying of the temp will stop 
    myPID.Compute();
    analogWrite(SSR_out, Output);
  }
  if(!digitalRead(PB3) && (millis()-hold_start)>=btnHoldDelay) holding_up();
  if(!digitalRead(PB6) && (millis()-hold_start)>=btnHoldDelay) holding_down();
}

void up() {
  if ((millis() - lstBtnBounce) > btnDebounceDelay) {
    hold_start = millis();
    if (!editSettings){
      vertical_pos -= 1;
      if (page == 0 && vertical_pos == 0) vertical_pos = 3;
      else if (page == 4 && horizontal_pos == 1 && vertical_pos == 0) vertical_pos = 7;
      else if (page == 4 && horizontal_pos == 2 && vertical_pos == 0) vertical_pos = 7;
      else if (page == 4 && horizontal_pos == 3 && vertical_pos == 0) vertical_pos = 4;
    }
    else{
      if (horizontal_pos == 1 && profiles[previosPage-1][vertical_pos-2][1] < 500) profiles[previosPage-1][vertical_pos-2][1] += 1; // Max Time limit
      else if (horizontal_pos == 2 && profiles[previosPage-1][vertical_pos-2][0] < 250) profiles[previosPage-1][vertical_pos-2][0] += 1; // Max Temp limit
      else if (horizontal_pos == 3 && K_pid[vertical_pos-2] < 9.99) K_pid[vertical_pos-2] += 0.01;
    }
    drawSelector();
    lstBtnBounce = millis();
  }
}

void down() {
  if ((millis() - lstBtnBounce) > btnDebounceDelay) {
    hold_start = millis();
    if (!editSettings){
      vertical_pos += 1;
      if (page == 0 && vertical_pos == 4) vertical_pos = 1;
      else if (page == 4 && horizontal_pos == 1 && vertical_pos == 8) vertical_pos = 1;
      else if (page == 4 && horizontal_pos == 2 && vertical_pos == 8) vertical_pos = 1;
      else if (page == 4 && horizontal_pos == 3 && vertical_pos == 5) vertical_pos = 1;
    }
    else{
      if (horizontal_pos == 1 && profiles[previosPage-1][vertical_pos-2][1] > 0) profiles[previosPage-1][vertical_pos-2][1] -= 1;  // Min Time limit
      else if (horizontal_pos == 2 && profiles[previosPage-1][vertical_pos-2][0] > 25) profiles[previosPage-1][vertical_pos-2][0] -= 1; // Min Temp limit
      else if (horizontal_pos == 3 && K_pid[vertical_pos-2] > 0) K_pid[vertical_pos-2] -= 0.01;
    }
    drawSelector();
    lstBtnBounce = millis();
  }
}

void left() {
  if ((millis() - lstBtnBounce) > btnDebounceDelay) {
    if (!heating && !editSettings){
      horizontal_pos -= 1;
      if (!save_pressed && !reset_pressed && horizontal_pos == 0) horizontal_pos = 3;
      if (page == 4){
        if ((save_pressed || reset_pressed) && (horizontal_pos == 1)) horizontal_pos = 3;
        else if (horizontal_pos == 3 && vertical_pos > 4) vertical_pos = 4; // jump to the shorter PID list
      }
      drawSelector();
      lstBtnBounce = millis();
    }
  }
}

void right() {
  if ((millis() - lstBtnBounce) > btnDebounceDelay) {
    if (!heating && !editSettings){
      horizontal_pos += 1;
      if (!save_pressed && !reset_pressed && horizontal_pos == 4) horizontal_pos = 1;
      if (page == 4){
        if ((save_pressed || reset_pressed) && (horizontal_pos == 4)) horizontal_pos = 2;
        else if (horizontal_pos == 3 && vertical_pos > 4) vertical_pos = 4; // jump to the shorter PID list
      } 
      drawSelector();
      lstBtnBounce = millis();
    }
  }
}

void holding_up(){
  if (editSettings && (millis() - last_val_change) > btnHoldUpdateRate){
    if (horizontal_pos == 1 && profiles[previosPage-1][vertical_pos-2][1] < 500) profiles[previosPage-1][vertical_pos-2][1] += 1; // Max Time limit
    else if (horizontal_pos == 2 && profiles[previosPage-1][vertical_pos-2][0] < 250) profiles[previosPage-1][vertical_pos-2][0] += 1; // Max Temp limit
    else if (horizontal_pos == 3 && K_pid[vertical_pos-2] < 9.99) K_pid[vertical_pos-2] += 0.01;
    drawSelector();
    last_val_change = millis();
  }
}

void holding_down(){
  if (editSettings && (millis() - last_val_change) > btnHoldUpdateRate){
    if (horizontal_pos == 1 && profiles[previosPage-1][vertical_pos-2][1] > 0) profiles[previosPage-1][vertical_pos-2][1] -= 1;  // Min Time limit
    else if (horizontal_pos == 2 && profiles[previosPage-1][vertical_pos-2][0] > 25) profiles[previosPage-1][vertical_pos-2][0] -= 1; // Min Temp limit
    else if (horizontal_pos == 3 && K_pid[vertical_pos-2] > 0) K_pid[vertical_pos-2] -= 0.01;
    drawSelector();
    last_val_change = millis();
  }
}

void center() {
  if ((millis() - lstBtnBounce) > btnDebounceDelay) {
    if (page == 0) {
      request_draw_profile_page = vertical_pos;
    }
    else if (page == 1 || page == 2 || page == 3) {
      if (horizontal_pos == 1) backRequest = true;
      else if (horizontal_pos == 2) startStopRequest = true;
      else if (heating == false && horizontal_pos == 3) settingsPageRequest = true;
      else if (heating == true && horizontal_pos == 3) startStopRequest = true;
    }
    else if (page == 4) {
      if (vertical_pos == 1 && horizontal_pos == 1) backRequest = true;
      else if (vertical_pos == 1 && horizontal_pos == 2){
        if (!save_pressed && !reset_pressed){
          save_pressed = true;
          draw_yes_no_buttons("save");
        }
        else if (save_pressed){
          saveRequest = true;
          save_pressed = false;
          reset_pressed = false;
        }
        else if (reset_pressed){
          resetRequest = true;
          save_pressed = false;
          reset_pressed = false;
        }
      }
      else if (vertical_pos == 1 && horizontal_pos == 3){
        if (!reset_pressed && !save_pressed){
          reset_pressed = true; 
          draw_yes_no_buttons("reset");
        }
        else if (save_pressed || reset_pressed){
          default_h_btn_para();
          page = previosPage;   // setting the correct page
          if (save_pressed) draw_settings_page(2);
          else if (reset_pressed) draw_settings_page(3);
          save_pressed = false;
          reset_pressed = false;
        }
      }
      else {
        editSettings = !editSettings;
        drawSelector();
      }
    }
    lstBtnBounce = millis();
  }
}

void drawBorder() {
  // Frame
  ucg.drawVLine(0, 0, 144);
  ucg.drawLine(0, 144, 15, 159);
  ucg.drawHLine(15, 159, 113);
  ucg.drawVLine(127, 132, 27);
  ucg.drawLine(127, 132, 105, 110);
  ucg.drawVLine(105, 0, 110);
  ucg.drawHLine(0, 0, 105);
  // Title
  ucg.drawBox(108, 0, 127, 109);
  ucg.drawTriangle(108, 109, 128, 109, 127, 129);
}

void drawBtn(byte x, byte y, byte h, byte w, byte font_x, byte font_y, String label) { // x,y - (bottom left), h - height
  ucg.setColor(0, 250, 245, 0);   // Bright Yellow
  ucg.drawBox(x, y, h, w);
  ucg.setColor(0, 0, 0, 0);
  ucg.drawTriangle(x + (h / 2) + 1, y, x + h, y, x + h, y + (h / 2));   // top left triangle
  ucg.drawTriangle(x, (y + w) - (h / 2), x, y + w, x + (h / 2), y + w); // bottom right triangle
  ucg.setColor(1, 250, 245, 0); // background Yellow
  ucg.setPrintPos(font_x, font_y);
  ucg.print(label);
}

void title(String label) {
  ucg.setFont(ucg_font_7x14_tr);  // Final
  ucg.setPrintPos(112, 2);
  ucg.print(label);
}

void draw_main_buttons() {
  ucg.setFont(ucg_font_7x14_tr);
  for (byte i = 0; i <= 2; i++) {
    drawBtn(main_btn_pos[i][0], main_btn_pos[i][1], main_btn_height, main_btn_width, main_btn_text_pos[i][0], main_btn_text_pos[i][1], main_btn_labels[i]);
  }
}

void draw_horizontal_buttons() {
  setColor(black);
  ucg.drawBox(81,2,23,100); // clear the temp and time info after heating
  ucg.setFont(ucg_font_6x13_tr);
  for (byte i = 0; i < 3; i++) {
    drawBtn(h_btn_pos[i][0], h_btn_pos[i][1], h_btn_height, h_btn_width, h_btn_text_pos[i][0], h_btn_text_pos[i][1], h_btn_labels[i]);
  }
}

void drawSelector() {
  if (page == 0) selector_main_buttons(vertical_pos);
  else if (page == 1 || page == 2 || page == 3) selector_horizontal_buttons(horizontal_pos);
  else if (page == 4){
    if (save_pressed || reset_pressed) selector_horizontal_buttons(horizontal_pos);
    else selector_settings_page(vertical_pos,horizontal_pos);
  }
}

void selector_main_buttons(byte v) {
  for (byte u = 1; u <= 3; u++) {
    if (v != u) {
      ucg.setColor(0, 0, 0, 0);
      ucg.drawLine((main_btn_pos[u - 1][0] + main_btn_height / 2) + 3, main_btn_pos[u - 1][1], main_btn_pos[u - 1][0] +  main_btn_height, (main_btn_pos[u - 1][1] +  main_btn_height / 2) - 2);
      ucg.drawLine((main_btn_pos[u - 1][0] + main_btn_height / 2) + 4, main_btn_pos[u - 1][1], main_btn_pos[u - 1][0] +  main_btn_height, (main_btn_pos[u - 1][1] +  main_btn_height / 2) - 3);
      ucg.drawLine(main_btn_pos[u - 1][0], (main_btn_pos[u - 1][1] + main_btn_width - main_btn_height / 2) + 3, (main_btn_pos[u - 1][0] + main_btn_height / 2) - 3, main_btn_pos[u - 1][1] + main_btn_width);
      ucg.drawLine(main_btn_pos[u - 1][0], (main_btn_pos[u - 1][1] + main_btn_width - main_btn_height / 2) + 4, (main_btn_pos[u - 1][0] + main_btn_height / 2) - 4, main_btn_pos[u - 1][1] + main_btn_width);
    }
  }
  ucg.setColor(0, 250, 245, 0); // Bright Yellow
  ucg.drawLine((main_btn_pos[v - 1][0] + main_btn_height / 2) + 3, main_btn_pos[v - 1][1], main_btn_pos[v - 1][0] +  main_btn_height, (main_btn_pos[v - 1][1] +  main_btn_height / 2) - 2);
  ucg.drawLine((main_btn_pos[v - 1][0] + main_btn_height / 2) + 4, main_btn_pos[v - 1][1], main_btn_pos[v - 1][0] +  main_btn_height, (main_btn_pos[v - 1][1] +  main_btn_height / 2) - 3);

  ucg.drawLine(main_btn_pos[v - 1][0], (main_btn_pos[v - 1][1] + main_btn_width - main_btn_height / 2) + 3, (main_btn_pos[v - 1][0] + main_btn_height / 2) - 3, main_btn_pos[v - 1][1] + main_btn_width);
  ucg.drawLine(main_btn_pos[v - 1][0], (main_btn_pos[v - 1][1] + main_btn_width - main_btn_height / 2) + 4, (main_btn_pos[v - 1][0] + main_btn_height / 2) - 4, main_btn_pos[v - 1][1] + main_btn_width);
}

void selector_horizontal_buttons(byte h) {
  byte u;
  if (save_pressed || reset_pressed) u = 1;
  else u = 0;
  for (u; u < 3; u++) {
    if (h != u+1) {
      ucg.setColor(0, 0, 0, 0);
      ucg.drawLine((h_btn_pos[u][0] + h_btn_height / 2) + 3, h_btn_pos[u][1], h_btn_pos[u][0] +  h_btn_height, (h_btn_pos[u][1] +  h_btn_height / 2) - 3);
      ucg.drawLine((h_btn_pos[u][0] + h_btn_height / 2) + 4, h_btn_pos[u][1], h_btn_pos[u][0] +  h_btn_height, (h_btn_pos[u][1] +  h_btn_height / 2) - 4);
      ucg.drawLine(h_btn_pos[u][0], (h_btn_pos[u][1] + h_btn_width - h_btn_height / 2) + 3, (h_btn_pos[u][0] + h_btn_height / 2) - 3, h_btn_pos[u][1] + h_btn_width);
      ucg.drawLine(h_btn_pos[u][0], (h_btn_pos[u][1] + h_btn_width - h_btn_height / 2) + 4, (h_btn_pos[u][0] + h_btn_height / 2) - 4, h_btn_pos[u][1] + h_btn_width);
    }
  }
  ucg.setColor(0, 250, 245, 0); // Bright Yellow
  ucg.drawLine((h_btn_pos[h - 1][0] + h_btn_height / 2) + 3, h_btn_pos[h - 1][1], h_btn_pos[h - 1][0] +  h_btn_height, (h_btn_pos[h - 1][1] +  h_btn_height / 2) - 3);
  ucg.drawLine((h_btn_pos[h - 1][0] + h_btn_height / 2) + 4, h_btn_pos[h - 1][1], h_btn_pos[h - 1][0] +  h_btn_height, (h_btn_pos[h - 1][1] +  h_btn_height / 2) - 4);

  ucg.drawLine(h_btn_pos[h - 1][0], (h_btn_pos[h - 1][1] + h_btn_width - h_btn_height / 2) + 3, (h_btn_pos[h - 1][0] + h_btn_height / 2) - 3, h_btn_pos[h - 1][1] + h_btn_width);
  ucg.drawLine(h_btn_pos[h - 1][0], (h_btn_pos[h - 1][1] + h_btn_width - h_btn_height / 2) + 4, (h_btn_pos[h - 1][0] + h_btn_height / 2) - 4, h_btn_pos[h - 1][1] + h_btn_width);
}

void selector_settings_page(byte v, byte h){
  if(editSettings == true){   // when editing - highlight the selected value
    setColor(black);          // Remove the rectangle around selected values
    if (h == 1) ucg.drawFrame(55 - (p4LastSelect_v-2)*10, 18, 11, 22);
    else if (h == 2) ucg.drawFrame(55 - (p4LastSelect_v-2)*10, 53, 11,  22);
    else if (h == 3 && p4LastSelect_v <= 4) ucg.drawFrame(55 - (p4LastSelect_v-2)*10, 118, 11, 27);

    ucg.setFont(ucg_font_6x12_mr);
    int val;
    if (h == 1){
      setColor(blackOnYellow);
      ucg.setPrintPos(56 - (v-2)*10, 20);
      val = profiles[previosPage-1][vertical_pos-2][1];
      ucg.print(String(val));
      setColor(black);
      if (val >= 10 && val < 100) ucg.drawBox(55 - (v-2)*10, 32,12,7); // manually remove last digit
      else if (val < 10) ucg.drawBox(55 - (v-2)*10, 26,12,7);
    }
    else if (h == 2){
      setColor(blackOnYellow);
      ucg.setPrintPos(56 - (v-2)*10, 55);
      val = profiles[previosPage-1][vertical_pos-2][0];
      ucg.print(String(val));
      setColor(black);
      if (val >= 10 && val < 100) ucg.drawBox(55 - (v-2)*10, 67,12,7);  // manually remove last digit
      else if (val < 10) ucg.drawBox(55 - (v-2)*10, 61,12,7);
    }
    else if (h == 3 && v != 5){
      setColor(blackOnYellow);
      ucg.setPrintPos(56 - (v-2)*10, 120);
      ucg.print(String(K_pid[v-2]));
    }
  }
  else{  // Rectangle around the value
    if (vertical_pos != 1){
      setColor(yellowOnBlack);
      ucg.setFont(ucg_font_6x12_mr);
      if (h == 1){
        ucg.setPrintPos(56 - (v-2)*10, 20);
        ucg.print(String(profiles[previosPage-1][vertical_pos-2][1]));
      }
      else if (h == 2){
        ucg.setPrintPos(56 - (v-2)*10, 55);
        ucg.print(String(profiles[previosPage-1][vertical_pos-2][0]));
      }
      else if (h == 3 && v != 5){
        ucg.setPrintPos(56 - (v-2)*10, 120);
        ucg.print(String(K_pid[v-2]));
      }
    }
    
    // Remove rectangle around the last selection
    if(p4LastSelect_v != 1){
      setColor(black);
      if (h == 1) ucg.drawFrame(55 - (p4LastSelect_v-2)*10, 18, 11, 22);
      else if (h == 2) ucg.drawFrame(55 - (p4LastSelect_v-2)*10, 53, 11,  22);
      else if (h == 3 && p4LastSelect_v <= 4) ucg.drawFrame(55 - (p4LastSelect_v-2)*10, 118, 11, 27);

      if (p4LastSelect_h != h && p4LastSelect_h == 1) ucg.drawFrame(55 - (p4LastSelect_v-2)*10, 18, 11, 22);
      else if (p4LastSelect_h != h && p4LastSelect_h == 2) ucg.drawFrame(55 - (p4LastSelect_v-2)*10, 53, 11,  22);
      else if (p4LastSelect_h != h && p4LastSelect_h == 3 && p4LastSelect_v != 5) ucg.drawFrame(55 - (p4LastSelect_v-2)*10, 118, 11, 27);
    }
    // Draw horizontal button selectors
    if (v == 1){
      for (byte u = 0; u < 3; u++) {
        if (h != u+1) {
          setColor(black);
          ucg.drawLine((h_btn_pos[u][0] + h_btn_height / 2) + 3, h_btn_pos[u][1], h_btn_pos[u][0] +  h_btn_height, (h_btn_pos[u][1] +  h_btn_height / 2) - 3);
          ucg.drawLine((h_btn_pos[u][0] + h_btn_height / 2) + 4, h_btn_pos[u][1], h_btn_pos[u][0] +  h_btn_height, (h_btn_pos[u][1] +  h_btn_height / 2) - 4);
          ucg.drawLine(h_btn_pos[u][0], (h_btn_pos[u][1] + h_btn_width - h_btn_height / 2) + 3, (h_btn_pos[u][0] + h_btn_height / 2) - 3, h_btn_pos[u][1] + h_btn_width);
          ucg.drawLine(h_btn_pos[u][0], (h_btn_pos[u][1] + h_btn_width - h_btn_height / 2) + 4, (h_btn_pos[u][0] + h_btn_height / 2) - 4, h_btn_pos[u][1] + h_btn_width);
        }
      }
      setColor(yellow);
      ucg.drawLine((h_btn_pos[h - 1][0] + h_btn_height / 2) + 3, h_btn_pos[h - 1][1], h_btn_pos[h - 1][0] +  h_btn_height, (h_btn_pos[h - 1][1] +  h_btn_height / 2) - 3);
      ucg.drawLine((h_btn_pos[h - 1][0] + h_btn_height / 2) + 4, h_btn_pos[h - 1][1], h_btn_pos[h - 1][0] +  h_btn_height, (h_btn_pos[h - 1][1] +  h_btn_height / 2) - 4);
      ucg.drawLine(h_btn_pos[h - 1][0], (h_btn_pos[h - 1][1] + h_btn_width - h_btn_height / 2) + 3, (h_btn_pos[h - 1][0] + h_btn_height / 2) - 3, h_btn_pos[h - 1][1] + h_btn_width);
      ucg.drawLine(h_btn_pos[h - 1][0], (h_btn_pos[h - 1][1] + h_btn_width - h_btn_height / 2) + 4, (h_btn_pos[h - 1][0] + h_btn_height / 2) - 4, h_btn_pos[h - 1][1] + h_btn_width);
    }
    else {
      // Clear the button slectors
      setColor(black);
      for (byte u = 0; u < 3; u++) {
        ucg.drawLine((h_btn_pos[u][0] + h_btn_height / 2) + 3, h_btn_pos[u][1], h_btn_pos[u][0] +  h_btn_height, (h_btn_pos[u][1] +  h_btn_height / 2) - 3);
        ucg.drawLine((h_btn_pos[u][0] + h_btn_height / 2) + 4, h_btn_pos[u][1], h_btn_pos[u][0] +  h_btn_height, (h_btn_pos[u][1] +  h_btn_height / 2) - 4);
        ucg.drawLine(h_btn_pos[u][0], (h_btn_pos[u][1] + h_btn_width - h_btn_height / 2) + 3, (h_btn_pos[u][0] + h_btn_height / 2) - 3, h_btn_pos[u][1] + h_btn_width);
        ucg.drawLine(h_btn_pos[u][0], (h_btn_pos[u][1] + h_btn_width - h_btn_height / 2) + 4, (h_btn_pos[u][0] + h_btn_height / 2) - 4, h_btn_pos[u][1] + h_btn_width);
      }
      setColor(yellow);
      if (h == 1) ucg.drawFrame(55 - (v-2)*10, 18, 11, 22);
      else if (h == 2)ucg.drawFrame(55 - (v-2)*10, 53, 11,  22);
      else if (h == 3 && v != 5) ucg.drawFrame(55 - (v-2)*10, 118, 11, 27);
    
      p4LastSelect_h = h;
      p4LastSelect_v = v;
    }
  }
}

void draw_main_page() {
  ucg.clearScreen();
  setColor(yellow);
  drawBorder();
  setColor(blackOnYellow);
  title("BRILLIANT REFLOW");
  draw_main_buttons();
  previosPage = page;
  page = 0;
  drawSelector();
}

void draw_profile_page(byte i) {
  ucg.clearScreen();
  setColor(yellow);
  drawBorder();
  setColor(blackOnYellow);
  title(main_btn_labels[i - 1]);
  draw_horizontal_buttons();
  previosPage = page;
  page = i;
  drawSelector();
  drawPlot(i);
}

void goBack() {
  if (page != 4) {
    vertical_pos = page;        // draw the selector on the last selected page
    draw_main_page();
  }
  else{
    horizontal_pos = 3;
    draw_profile_page(previosPage);
  }
}

void drawPlot(byte i) {
  i = i - 1;
  ucg.setColor(0, 0, 0, 0);     // Font Yellow
  ucg.drawBox(11,21,70,120);
  
  ucg.setColor(0, 250, 245, 0); // Font Yellow
  ucg.setColor(1, 0, 0, 0);     // background Black
  ucg.drawHLine(10, 20, 61);    // Time limits - 20, 80, 140
  ucg.drawVLine(10, 20, 120);   // Temp limits - 10, 40, 70

  ucg.drawHLine(10, 140, 3);
  ucg.drawHLine(10, 80, 3);
  ucg.drawVLine(10, 18, 2);
  ucg.drawVLine(70, 18, 2);
  ucg.drawVLine(40, 18, 2);

  ucg.setFont(ucg_font_6x10_tr); // texts
  ucg.setPrintPos(72, 8);
  ucg.print("T(C)");
  ucg.setPrintPos(13, 136);
  ucg.print("t(s)");

  // map the values
  maxTemp = profiles[i][0][0];
  minTemp = profiles[i][0][0];
  maxTime = profiles[i][5][1];

  for (byte u = 0; u < 5; u++) { // finding the max and min Temperatures from the preset points
    if ( maxTemp < profiles[i][u][0]) maxTemp = profiles[i][u][0];
    if ( minTemp > profiles[i][u][0]) minTemp = profiles[i][u][0];
  }

  ucg.setFont(ucg_font_5x7_tr);  // numbers
  ucg.setPrintPos(62, 4);
  ucg.print(String(maxTemp));
  ucg.setPrintPos(32, 4);
  ucg.print(String((maxTemp + minTemp) / 2));
  ucg.setPrintPos(7, 6);
  ucg.print(String(minTemp));

  ucg.setPrintPos(2, 18);
  ucg.print("0");
  ucg.setPrintPos(2, 73);
  ucg.print(String(maxTime / 2));
  ucg.setPrintPos(2, 130);
  ucg.print(String(maxTime));

  for (byte k = 0; k < 5; k++) {
    float tem_1 = ((60 * (profiles[i][k][0] - minTemp)) / (maxTemp - minTemp)) + 10;   // height of plot is 60
    float t_1 = ((120 * profiles[i][k][1]) / maxTime) + 20;                            // width of plot is 120

    float tem_2 = ((60 * (profiles[i][k + 1][0] - minTemp)) / (maxTemp - minTemp)) + 10;
    float t_2 = ((120 * profiles[i][k + 1][1]) / maxTime) + 20;
    ucg.drawLine(tem_1, t_1, tem_2, t_2);
  }
}

void startStop() {
  ucg.setFont(ucg_font_6x13_tr);
  if (heating == false) {
    drawStopBtn();
    drawPlot(page);
    setColor (black);
    heating = true;
  }
  else {
    heating = false;
    myPID.SetMode(MANUAL);      // turn off the PID
    Output = 0;
    digitalWrite(SSR_out, LOW); // turn off the heater
    pidInit = false;
    draw_horizontal_buttons();
    horizontal_pos = 2;
    drawSelector();
    plotTime=0;
  }
}

void blinking_dot(int c){
  if ((millis() - lstBlink) > 500){
    blinkState = !blinkState;
    if (blinkState) setColor(c);
    else setColor(black);
    ucg.drawDisc(120, 152, 3, UCG_DRAW_ALL);
    lstBlink = millis();
  } 
}

void setColor(int i){
  switch (i) {
    case black:
      ucg.setColor(0, 0, 0, 0);
      break;
    case red:
      ucg.setColor(0, 250, 0, 0);
      break;
    case yellow:
      ucg.setColor(0, 250, 245, 0);
      break;
    case green:
      ucg.setColor(0, 0, 250, 0);
      break;
    case blackOnYellow:
      ucg.setColor(0, 0, 0, 0);
      ucg.setColor(1, 250, 245, 0);
      break; 
    case yellowOnBlack:
      ucg.setColor(0, 250, 245, 0);
      ucg.setColor(1, 0, 0, 0);
      break;   
  }
}

void drawStopBtn(){
    setColor(black);
    ucg.drawBox(h_btn_pos[0][0],h_btn_pos[0][1],h_btn_height, h_btn_pos[2][1]-1);
    h_btn_labels [2] = "STOP";
    setColor(yellow);
    drawBtn(h_btn_pos[2][0], h_btn_pos[2][1], h_btn_height, h_btn_width, h_btn_text_pos[2][0], h_btn_text_pos[2][1], h_btn_labels[2]);
    horizontal_pos = 3;
    drawSelector();
    h_btn_labels [2] = "EDIT";

    // Time and Temperature
    setColor(yellowOnBlack);
    ucg.setFont(ucg_font_6x12_tr);
    ucg.setPrintPos(95, 4);
    ucg.print("Temp(C):");
    ucg.setPrintPos(85, 4);
    ucg.print("Time(s):");
}

void draw_settings_page(byte h){
  previosPage = page; 
  page = 4;
  ucg.clearScreen();
  setColor(yellow);
  drawBorder();
  setColor(blackOnYellow);
  title("Settings Prof_" + String(previosPage)); // previous page number is the profile number

  h_btn_labels [1] = "SAVE";
  h_btn_labels [2] = "RESET";
  h_btn_text_pos[1][1] = 68;
  h_btn_text_pos[2][1] = 117;
  setColor(yellow);
  draw_horizontal_buttons();
  default_h_btn_para();
  
  setColor(yellowOnBlack);
  ucg.setFont(ucg_font_6x12_mr);
  ucg.setPrintPos(68, 17);
  ucg.print("t(s)");
  ucg.setPrintPos(68, 45);
  ucg.print("Temp(C)");
  ucg.setPrintPos(68, 94);
  ucg.print("Global PID");
  for (byte i = 0; i<=5; i++){    // plot coordinates
    ucg.setPrintPos(56 - i*10, 6);
    ucg.print(String(i+1)+":");
    int p = profiles[previosPage-1][i][1];
    ucg.setPrintPos(56 - i*10, 20);
    ucg.print(String(p));

    int k = profiles[previosPage-1][i][0];
    ucg.setPrintPos(56 - i*10, 55);
    ucg.print(String(k));
  }
  for (byte i=0; i<=2; i++){      // PID values
    ucg.setFont(ucg_font_6x12_tr);
    ucg.setPrintPos(56 - i*10, 100);
    ucg.print(pid[i]);
    ucg.setFont(ucg_font_6x12_mr);
    ucg.setPrintPos(56 - i*10, 120);
    ucg.print(K_pid[i]);
  } 
  setColor(yellow);
  ucg.drawHLine(6,88,70);
  horizontal_pos = h;             // starting selector positions
  vertical_pos = 1;
  drawSelector();
}

void calculateSetPoint(){ // calculate the temperature values for every time steps
  byte k = page - 1;
  for (byte i = 0; i<=5; i++){
    if (profiles[k][i][1] < plotTime && plotTime < profiles[k][i+1][1]) Setpoint = ((profiles[k][i+1][0] - profiles[k][i][0])*(plotTime - profiles[k][i][1])/(profiles[k][i+1][1] - profiles[k][i][1])) + profiles[k][i][0];
  }
}

void EEPROM_get(){
  int addr = 0;
  addr += sizeof(int);  // skip the first value
  for (byte u = 0; u < 3; u++){
    for (byte i = 0; i < 6; i++){
      for (byte k = 0; k < 2; k++){
        EEPROM.get(addr, profiles[u][i][k]);
        addr += sizeof(int);  // move the address a size of `int`
      }
    } 
  }
  for (byte m = 0; m < 3; m++){
    EEPROM.get(addr, K_pid[m]);
    addr += sizeof(double);
  }
}

void EEPROM_set_default(){
  int addr = 0;
  addr += sizeof(int); // placeholder for for the initial value
  for (byte u = 0; u < 3; u++){
    for (byte i = 0; i < 6; i++){
      for (byte k = 0; k < 2; k++){
        EEPROM.put(addr, default_profiles[u][i][k]);
        addr += sizeof(int);  // move the address a size of `int`
      }
    }   
  }
  for (byte m = 0; m < 3; m++){
    EEPROM.put(addr, default_K_pid[m]);
    addr += sizeof(double);
  }
  EEPROM.put(addr, 101);
  EEPROM.put(0, addr);
}

void EEPROM_save(){
  int addr = 0;
  addr += sizeof(int); // placeholder for for the initial value
  for (byte u = 0; u < 3; u++){
    for (byte i = 0; i < 6; i++){
      for (byte k = 0; k < 2; k++){
        EEPROM.put(addr, profiles[u][i][k]);
        addr += sizeof(int);  // move the address a size of `int`
      }
    }   
  }
  for (byte m = 0; m < 3; m++){
    EEPROM.put(addr, K_pid[m]);
    addr += sizeof(double);
  }
  EEPROM.put(addr, 101);
  EEPROM.put(0, addr);
}

bool EEPROM_check(){
  byte addr, ck;
  EEPROM.get(0,addr); // read the address 0 to get the address of the last value
  EEPROM.get(addr,ck);
  if (ck == 101) return true;
  else return false;
}

void draw_yes_no_buttons(String s) {
  h_btn_labels [1] = "YES";
  h_btn_labels [2] = "NO";
  h_btn_pos[1][1] = 80;
  h_btn_pos[2][1] = 120;
  h_btn_text_pos[1][1] = 89;
  h_btn_text_pos[2][1] = 133;
  h_btn_width = 35;

  setColor(black);
  ucg.drawBox(81,2,23,157); // clear the buttons
  
  setColor(blackOnYellow);
  ucg.setFont(ucg_font_6x13_tr);
  for (byte i = 1; i < 3; i++) {
    drawBtn(h_btn_pos[i][0], h_btn_pos[i][1], h_btn_height, h_btn_width, h_btn_text_pos[i][0], h_btn_text_pos[i][1], h_btn_labels[i]);
  }
  setColor(yellowOnBlack);
  if (s == "save"){
    ucg.setFont(ucg_font_6x12_tr);
    ucg.setPrintPos(95, 4);
    ucg.print("Save values");
    ucg.setPrintPos(85, 4);
    ucg.print("to memory?");
  }
  if (s == "reset"){
    ucg.setFont(ucg_font_6x12_tr);
    ucg.setPrintPos(95, 4);
    ucg.print("Reset values");
    ucg.setPrintPos(85, 4);
    ucg.print("to default?");
  }
  horizontal_pos = 2; // initially select YES 
  drawSelector();
}

void default_h_btn_para(){
  byte p[3][2] = {{83, 5}, {83, 56}, {83, 107}};
  byte q[3][2] = {{87, 17}, {87, 66}, {87, 120}};
  for (byte i=0; i<3; i++){
    for (byte u=0; u<2; u++){
      h_btn_pos[i][u] = p[i][u];
    }
  }
  for (byte i=0; i<3; i++){
    for (byte u=0; u<2; u++){
      h_btn_text_pos[i][u] = q[i][u];
    }
  }
  h_btn_labels[0] = "BACK";
  h_btn_labels[1] = "START";
  h_btn_labels[2] = "EDIT";
  h_btn_height = 18;
  h_btn_width = 47;
}
