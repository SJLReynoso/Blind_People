#define trigPin 9
     #define echoPin 8
     
     int speakerPin = 7;
     int numTones = 10;
     int tones[ ] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440,466, 494};
                       // mid C C# D D# E F F# G G# A

     void setup()
        {   Serial.begin (9600);
            pinMode(trigPin, OUTPUT);
            pinMode(echoPin, INPUT);      
        }

     void loop()
        {   long duracion, distancia ;
            digitalWrite(trigPin, LOW);        // Nos aseguramos de que el trigger está desactivado
            delayMicroseconds(2);              // Para asegurarnos de que el trigger esta LOW
            digitalWrite(trigPin, HIGH);       // Activamos el pulso de salida
            delayMicroseconds(10);             // Esperamos 10µs. El pulso sigue active este tiempo
            digitalWrite(trigPin, LOW);        // Cortamos el pulso y a esperar el echo
            duracion = pulseIn(echoPin, HIGH) ;
            distancia = duracion / 2 / 29.1  ;
            Serial.println(String(distancia) + " cm.") ;
   
            if ( distancia >30){
                noTone(speakerPin);
            }
            
    
        if (distancia < 30 && distancia >10){
               tone(speakerPin, tones[350 - distancia]);
               delay(700);
            } 
            else {
              noTone(speakerPin);
              }  
            if ( distancia < 10){
                tone(speakerPin, tones[400]);
                     delay(500);
            }
            else{
              noTone(speakerPin);
            }        
        }

