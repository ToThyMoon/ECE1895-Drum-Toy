#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

void setup() 
{

lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
lcd.backlight();//To Power ON the back light
//lcd.backlight();// To Power OFF the back light

}

void loop() 
{
//Write your code
lcd.setCursor(0,0); //Defining positon to write from first row,first column .
lcd.print(" First Line ");
delay(1000);
lcd.setCursor(0,1);  //Defining positon to write from second row,first column .
lcd.print("Second Line");
delay(8000); 

lcd.clear();//Clean the screen
}
