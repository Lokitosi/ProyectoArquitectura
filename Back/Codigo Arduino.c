#include "Servo.h"   // librería para poder controlar el servo

enum SpaceState {
  Available, Reserved, Bussy
};

enum Pin {
  Infra1 = 2, // Infrarrojo Puesto 1
  Infra2 = A5, // Infrarojo Puesto 2
  Infra3 = A4, // Infrarrojo Puesto 3
  Led1R = 11, // Led Notificador Puesto 1 Red
  Led1G = 10, // Led Notificador Puesto 1 Green
  Led1B = 9, // Led Notificador Puesto 1 Blue
  Led2R = 8, // Led Notificador Puesto 2 Red
  Led2G = 7, // Led Notificador Puesto 2 Green
  Led2B = 6, // Led Notificador Puesto 2 Blue
  Led3R = 5, // Led Notificador Puesto 3 Red
  Led3G = 4, // Led Notificador Puesto 3 Green
  Led3B = 3, // Led Notificador Puesto 3 Blue
  Servo1 = 13, // Servo Entrada
  Servo2 = 12, // Servo Salida
  UltraSonidoTrigger1 = A3, // UltraSonido Entrada Trigger
  UltraSonidoEcho1 = A2, // UltraSonido Entrada Echo
  UltraSonidoTrigger2 = A1, // UltraSonido Salida Trigger
  UltraSonidoEcho2 = A0 // UltraSonido Salida Echo
};

struct SpaceRGB {
  Pin red, green, blue;
  String nombre;

  SpaceRGB(String nombre, Pin red, Pin green, Pin blue) : nombre(nombre), red(red), green(green), blue(blue) {};

  void begin() {
    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(blue, OUTPUT);

    Serial.print("Inicializado LED\t");
    Serial.println(nombre);
  }
};

struct Puesto {
  SpaceRGB led;
  Pin infrarrojo;
  bool isReserved;
  String nombre;

  Puesto(String nombre, Pin infrarrojo, SpaceRGB led) : nombre(nombre), infrarrojo(infrarrojo), led(led) {};

  void begin() {
    led.begin();
    pinMode(infrarrojo, INPUT);

    Serial.print("Inicializado Puesto\t");
    Serial.println(nombre);
  }
};

struct UltraSonido {
  Pin echo, trigger;
  String nombre;

  UltraSonido(String nombre, Pin echo, Pin trigger) : nombre(nombre), echo(echo), trigger(trigger) {};

  void begin() {
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT); 

    Serial.print("Inicializado UltraSonido\t");
    Serial.println(nombre);
  }
};

struct Puerta {
  Servo servo;
  Pin servoPin;
  UltraSonido ultraSonido;
  bool isOpen;
  String nombre;

  Puerta(String nombre, Pin servoPin, UltraSonido ultraSonido) : nombre(nombre), servoPin(servoPin), ultraSonido(ultraSonido) {};

  void begin() {
    ultraSonido.begin();
    servo.attach(servoPin);

    Serial.print("Inicializado Puerta\t");
    Serial.println(nombre);
  }
};

Puesto espacios[] = {
  Puesto("Infrarrojo_0", Infra1, SpaceRGB("Led_0", Led1R, Led1G, Led1B)),
  Puesto("Infrarrojo_1", Infra2, SpaceRGB("Led_1", Led2R, Led2G, Led2B)),
  Puesto("Infrarrojo_2", Infra3, SpaceRGB("Led_2", Led3R, Led3G, Led3B))
};

Puerta puertas[] = {
  Puerta("Servo_0", Servo1, UltraSonido("Ultrasonido_0", UltraSonidoEcho1, UltraSonidoTrigger1)),
  Puerta("servo_1", Servo2, UltraSonido("Ultrasonido_1", UltraSonidoEcho2, UltraSonidoTrigger2))
};

bool networkControl;

void setup() {
  // Velocidad Baud
  Serial.begin(9600);

  // Inicializar estructuras
  for(Puesto espacio : espacios) {
    espacio.begin();
  }

  for(Puerta puerta : puertas) {
    puerta.begin();
  }

  delay(5000);
}

void abrirPuerta(Puerta &puerta) {

  if(puerta.isOpen) {
    return;
  }

  puerta.isOpen = true;

  puerta.servo.attach(puerta.servoPin);
  
  for(int i = 90; i <= 180; ++i) {
    puerta.servo.write(i);
    delay(20);
  }

  puerta.servo.detach();
}

void cerrarPuerta(Puerta &puerta) {

  if(!puerta.isOpen) {
    return;
  }

  puerta.isOpen = false;

  puerta.servo.attach(puerta.servoPin);
  
    for(int i = 180; i >= 90; --i) {
      puerta.servo.write(i);
      delay(20);
  }

  puerta.servo.detach();
}


bool validarEspacio(Puesto &puesto) {
  int value = digitalRead(puesto.infrarrojo);
  return value == HIGH;
}

bool validarPuerta(UltraSonido &ultraSonido) {

  double duration, distance;
  
  digitalWrite(ultraSonido.trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(ultraSonido.trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultraSonido.trigger, LOW);
  
  duration = pulseIn(ultraSonido.echo, HIGH); // Lee el tiempo de respuesta del pin Echo
  distance = (duration / 2) * 0.0343; // Convierte el tiempo en distancia en centímetros

  return distance <= 5;
}

void asignarEstadoRGB(SpaceRGB puesto, SpaceState estado) {
  switch(estado) {
    case Available:
      analogWrite(puesto.red, 255);
      analogWrite(puesto.green, 0);
      analogWrite(puesto.blue, 255);
      break;
    case Reserved:
      analogWrite(puesto.red, 255);
      analogWrite(puesto.green, 255);
      analogWrite(puesto.blue, 0);
      break;
    case Bussy:
      analogWrite(puesto.red, 0);
      analogWrite(puesto.green, 255);
      analogWrite(puesto.blue, 255);
      break;
  }
}

void asignarEstadoPuerta(Puerta &puerta, bool shouldOpen) {
  if(shouldOpen) {
    abrirPuerta(puerta);
  } else {
    cerrarPuerta(puerta);
  }
}

void asignarEstadoPuerta(Puerta &puerta) {
  asignarEstadoPuerta(puerta, validarPuerta(puerta.ultraSonido));
}

void loop() {
  // Leer ESP32
  String operation = Serial.readString();

  String action = operation.substring(0, 1);
  String element = operation.substring(1, 2);
  String idElement = operation.substring(2, 3);

  // Validar Puertas
  for(Puerta &puerta : puertas) {
    if(operation.length() > 0 && element.indexOf("S") >= 0 && puerta.nombre.indexOf(idElement) >= 0) {
      bool state = action.indexOf("O") >= 0;
      asignarEstadoPuerta(puerta, state);
    } else {
      asignarEstadoPuerta(puerta);
    }
  }

  // Validar Espacios Parqueo
  for(Puesto &espacio : espacios) {

    if(operation.length() > 0 && espacio.nombre.indexOf(idElement) >= 0) {
      if(action.indexOf("R") >= 0) {
        espacio.isReserved = true;
      } else if(action.indexOf("F") >= 0) {
        espacio.isReserved = false;
      }
    }
    
    if(!validarEspacio(espacio)) {
      asignarEstadoRGB(espacio.led, Bussy); // Led Espacio Ocupado
    } else if(espacio.isReserved) {
      asignarEstadoRGB(espacio.led, Reserved); // Led Espacio Reservado
    } else {
      asignarEstadoRGB(espacio.led, Available); // Led Espacio Disponible
    }
  }
  
  delay(500);
}