/******************************************************************************

                            Home automation using Arduino 

*******************************************************************************/
int SoundSensor=12;                                 // LM393 Sound Sensor Digital Pin D0 connected to pin 2  
int LED=13;                                        // LED connected to pin 9  
boolean LEDStatus=false;  

int motor1pin1 = 10;                               // MOTOR INPUT 1
int motor1pin2 = 11;                              // MOTOR INPUT 2
int en=9;                                        //ENABLE INPUT

int echoPin=2;                                   // attach pin D2 Arduino to pin Echo of HC-SR04
int trigPin=3;                                  // attach pin D3 Arduino to pin Trig of HC-SR04                                      
long duration; 
int distance; 

void setup()  
{  
    pinMode(SoundSensor,INPUT);  
    pinMode(LED,OUTPUT);   
    Serial.begin(9600); 

    pinMode(motor1pin1, OUTPUT);
    pinMode(motor1pin2, OUTPUT);
    pinMode(A0,INPUT);
    pinMode(9,   OUTPUT); 

    pinMode(trigPin,OUTPUT); 
    pinMode(echoPin, INPUT);
}
 
void loop()   
{  
    // ultra sonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); 
 
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPin,LOW); 
 
    duration=pulseIn(echoPin, HIGH);
    distance=duration * 0.0344 / 2;
    delay(100);
    
    if(distance <50)
    {
        Serial.print(distance); 
        Serial.println(" ALERT");
        delay(100);
    }

    //sensor part
    int SensorData=digitalRead(SoundSensor); 
 
    //temperature part
    int a=analogRead(A0);
    float tc=((a/10)*4.88);
  
    if(SensorData==1)  
    {  
        if(LEDStatus==false)  
        {  
            LEDStatus=true;  
            digitalWrite(LED,HIGH); 
        }  
        else if(LEDStatus==true)  
        {  
            LEDStatus=false;  
            digitalWrite(LED,LOW); 
        }

        //temperature part
        if(LEDStatus==true)
        {
            if(tc<=29)
            {
                analogWrite(9, 30); //ENA   pin
                digitalWrite(motor1pin1,   HIGH);
                digitalWrite(motor1pin2, LOW);
                Serial.println("s1");
            }
            else if(tc>30 && tc<40)
            {
                analogWrite(9, 90); //ENA   pin
                digitalWrite(motor1pin1,   HIGH);
                digitalWrite(motor1pin2, LOW);
                Serial.println("s2");
            }
            else if(tc>40 && tc<50)
            {
                analogWrite(9, 125); //ENA   pin
                digitalWrite(motor1pin1,   HIGH);
                digitalWrite(motor1pin2, LOW);
                Serial.println("sp3");
            }
            else
            {
                analogWrite(9, 150); //ENA   pin
                digitalWrite(motor1pin1, HIGH);
                digitalWrite(motor1pin2, LOW);
                Serial.println("HIGH");
            }
        }

        if(LEDStatus==false)
        {
            analogWrite(9, 0); //ENA   pin
            digitalWrite(motor1pin1,   LOW);
            digitalWrite(motor1pin2, LOW);
        }
    }
 }