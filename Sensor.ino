#define PIN_TRIG           6  //Cambiar según sea mas comodo
#define PIN_ECO            5  //Cambiar según sea mas comodo
#define CANTIDAD_LECTURAS 20

long duracion;  // Variables

int suma = 0;
float distancia;
float distaciaMinima = 80.0;  //Distacia minima en cm para accionar led

long lectura(){
  
  long distancia;
  /* Hacer el disparo */
  digitalWrite(PIN_TRIG, LOW);  
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);  // Flanco ascendente
  delayMicroseconds(10);        // Duracion del pulso
  digitalWrite(PIN_TRIG, LOW);  // Flanco descendente

  /* Recepcion del eco de respuesta */
  duracion = pulseIn(PIN_ECO, HIGH);

  /* Calculo de la distancia efectiva */
  distancia = (duracion/2) / 29;
  return distancia;
}
  
void setup() {
  // Inicializacion de la comunicacion serial
  Serial.begin (9600);  
  // Inicializacion de pines digitales
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECO, INPUT);
  pinMode(2, OUTPUT);

}

void loop() {
  
  suma = 0;
  for (byte i=0; i<CANTIDAD_LECTURAS; i++) {
      suma += lectura();
  }
  distancia = suma/CANTIDAD_LECTURAS;

  if (distancia <= distaciaMinima){
      digitalWrite(2, HIGH);
  }
  else
      digitalWrite(2, LOW);
}

