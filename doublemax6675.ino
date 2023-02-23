// this example is public domain. enjoy! https://learn.adafruit.com/thermocouple/

#include "max6675.h"

int thermoDO = 12;//mauve
int thermoCS = 10;//orange
int thermoCLK = 13;//vert
int thermoCS2 = 9;//jaune
bool unit_F = true;
float tempA;
float tempB;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
MAX6675 thermocouple2(thermoCLK, thermoCS2, thermoDO);
void setup() {
  Serial.begin(115200);
  //Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);
}

//Parsing Serial Commands
void handleSerialCommand(){   

    if (Serial.available()>0){
        String msg = Serial.readStringUntil('\n');

        if (msg.indexOf("CHAN;")== 0){  //Ignore this Setting
            Serial.print("#OK");
        }
        else if (msg.indexOf("UNITS;")== 0){

            if (msg.substring(6,7)=="F"){   //Change to Farenheit
                unit_F = true;
                Serial.println("#OK Farenheit");
            }
            else if (msg.substring(6,7)=="C"){  //Change to Celsius
                unit_F = false;
                Serial.println("#OK Celsius");
            }

        }
        else if (msg.indexOf("READ")==0){   //Send Temps
           Command_READ();

       }
   }

}
//Send Data
void Command_READ(){    
    if(unit_F){
      Serial.print("0.00,");
    Serial.print(thermocouple.readFahrenheit());
    Serial.print(",");
    Serial.print(thermocouple2.readFahrenheit());
    Serial.println(",0.00,0.00");
      }else
      {
        Serial.print("0.00,");
    Serial.print(thermocouple.readCelsius());
    Serial.print(",");
    Serial.print(thermocouple2.readCelsius());
    Serial.println(",0.00,0.00");
     }
    
    
}





void loop() {

    handleSerialCommand();
    
}
