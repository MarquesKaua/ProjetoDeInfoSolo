#include <Adafruit_LiquidCrystal.h>


Adafruit_LiquidCrystal lcd(0);

#define sensorUmidade A0 // Sensor de umidade de solo do módulo
unsigned long tempoAnterior = 0; // Variável utilizada para guardar o tempo anterior
unsigned long intervalo = 1000; // Intervalo de tempo em MS para cada leituraa
int pinoTMP = A1; // sensor temperatura
int estado = LOW; // botao
int anterior = 0; // botao
float AnalogIn=0;  // Variável global de armazenamento do sinal do conversor A/D
float TensaoA0=0;  // Variável global de armazenamento da tensão do conversor A/D
float valPh=0; // PH
int valor_botao = 0;

void setup() {
  pinMode(2, INPUT); //botao
  pinMode(A2, INPUT); //potenciometro
  lcd.begin(16,2);
  Serial.begin(9600); // Inicialização da comunicação serial
}
void loop() {
  
  //ph
  AnalogIn = analogRead(A2);           // Armazena o valor obtido pelo conversor A/D na variável "AnalogIn"
  TensaoA0 = (AnalogIn * 5)/1024;      // Calcula a tensão condizente ao valor do conversor A/D e armazena na variável "TensaoA0"
  valPh = TensaoA0 * 2.8; 
 
  //umidade
  unsigned long tempoAtual = millis(); // Realizamos a leitura atual do tempo em que o nosso Arduino Nano está ligado
  if (tempoAtual-tempoAnterior > intervalo){ // Pequena lógica para realizar leituras temporizadas sem parar o microcontrolador
      tempoAnterior =tempoAtual; // Guardamos o tempo anterior como o ultimo intervalo de tempo lido
      int leitura = analogRead(sensorUmidade);
    
    //temperatura
    int valorSensor = analogRead(pinoTMP);
     float voltagem = (valorSensor * 5.0) / 1024;
  float milliVolt = voltagem * 1000;
  float tmpCel = (milliVolt - 500) / 10;
  
    //botao
     valor_botao = digitalRead(2);
    
     Serial.println(leitura);
    Serial.println(tmpCel);// Leitura dos dados analógicos vindos do sensor de umidade de solo
    
    
    //os IFS E ELSES servem para rodar o display lcd com o botao
    if(valor_botao == 1 && anterior == LOW){
  estado++;
  
     if(estado > 2){
     estado = 0;
     }
  }
    if (estado == 0 && leitura >= 700){ 
        lcd.setCursor(0, 0);
        lcd.print("Umidade alta: ");
        lcd.setCursor(0, 1);
        lcd.print("                "); 
        lcd.setCursor(0, 1);
        lcd.print(map(leitura, 0, 876, 0, 100)); //umidade alta
        lcd.print("%");
        delay(10);
        delay(50);
      }else{
        if ( estado == 0 && leitura >= 400 && leitura <= 699){
         lcd.setCursor(0, 0);
         lcd.print("Umidade media: ");
         lcd.setCursor(0, 1);
         lcd.print("                "); 
         lcd.setCursor(0, 1);
         lcd.print(map(leitura, 0, 876, 0, 100)); //umidade media
         lcd.print("%");
         delay(10);
         delay(50);
        }
        else{
          if (estado == 0 && leitura <= 399 && leitura>=0){
            lcd.setCursor(0, 0);
            lcd.print("Umidade baixa: ");
            lcd.setCursor(0, 1);
            lcd.print("                "); 
            lcd.setCursor(0, 1);       
            lcd.print(map(leitura, 0, 876, 0, 100)); //umidade baixa
            lcd.print("%");
            delay(10);
            delay(50);
          }
          else{
          if (estado == 1){
            lcd.setCursor(0, 0);
            lcd.print("Temperatura:");
            lcd.print(tmpCel); ;// valor temperatura
            lcd.setCursor(0, 1);        
            lcd.print("Celsius");
            delay(10);
            delay(50);
          }
            else{
          if (estado == 2){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("                    ");
            lcd.setCursor(0,0);                  // Posiciona o cursor do LCD
            lcd.print("PH:");  
            
            lcd.setCursor(0,1);                  // Posiciona o cursor do LCD
            lcd.print(valPh);  // Exibe o valor calculado pela variável "valPh"
            delay(10);
            delay(50);
          }
            anterior = valor_botao;
           delay(50);
        } 
      }
  }
 }
}
}
