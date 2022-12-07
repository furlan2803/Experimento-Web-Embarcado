#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <LiquidCrystal_I2C.h>

// Definindo os pinos utilizados para ligar o display LCD
#define I2C_SDA 47
#define I2C_SCL 48

LiquidCrystal_I2C lcd(0x27, 16, 2);
 
const char* ssid = "Inteli-COLLEGE";
const char* password =  "QazWsx@123";

AsyncWebServer server(8080);

void tocar_buzzer() {

  tone(38,494,100);
  tone(38,988,100);
  tone(38,740,100);
  tone(38,622,100);
  tone(38,740,100);
  tone(38,622,100);
  tone(38,523,100);
  tone(38,1047,100);
  tone(38,784,100); 
  tone(38,659,100);
  tone(38,1047,100);
  tone(38,784,100); 
  noTone(38);

}

void print_lcd(String texto) {

  Serial.println(texto);
  lcd.print(texto);

}
 
void setup(){
  
  Serial.begin(115200); 
  Wire.begin(I2C_SDA, I2C_SCL);
  lcd.init();
  lcd.backlight();


  pinMode(38, OUTPUT);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println(WiFi.localIP());
 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Sistema Web Embarcado</title></head><body style='overflow: hidden; margin: 0; padding: 0; box-sizing: border-box;'><section class='principal' style='background-color: coral; height: 30vh;'><!-- background coral--></section><section class='text-home' style='width: 70%; margin: 0 auto; margin-top: -5%; z-index: 1; background-color: white; padding: 2%;'><div><form action='/enviar'><h3 for='MSG' style='text-align: center; font-size: 40px;'>Exercício Semana 9</h3><p> Criar um servidor Web Embarcado, um Endpoint do tipo 'GET' que receba um parametro enviado por um form HTML e quando receber o valor digitado deve mostrar no Display LCD E tocar um Buzzer.</p><p style='text-align: left; font-size: 20px;'>Digite uma palavra : </p><input type='text' name='MSG' id='MSG' style='font-size: 20px; width: 400px; color: black;'><button type='submit' style='background-color: coral; border: none; color: white; border-radius: 15px; padding: 15px'>Enviar</button></form></div></section></body></html>");
  });

  server.on("/enviar", HTTP_GET, [](AsyncWebServerRequest *request){
    
    AsyncWebParameter* p = request->getParam(0);

    request->send(200, "text/html", "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Sistema Web Embarcado</title></head><body style='overflow: hidden; margin: 0; padding: 0; box-sizing: border-box;'><section class='principal' style='background-color: coral; height: 30vh;'><!-- background coral--></section><section class='text-home' style='width: 70%; margin: 0 auto; margin-top: -5%; z-index: 1; background-color: white; padding: 2%;'><div><form action='/enviar'><h3 for='MSG' style='text-align: center; font-size: 40px;'>Exercício Semana 9</h3><p> Criar um servidor Web Embarcado, um Endpoint do tipo 'GET' que receba um parametro enviado por um form HTML e quando receber o valor digitado deve mostrar no Display LCD E tocar um Buzzer.</p><h2>Mensagem Enviada com Sucesso!</h2><button type='button' style='background-color: coral; border: none; color: white; border-radius: 15px; padding: 15px'><a style='border: none; color: white; border-radius: 15px; padding: 15px; text-decoration: none' href='http://10.128.66.23:8080'>Enviar nova mensagem</a></button></div></section></body></html>");

    


    print_lcd(p->value());
    tocar_buzzer();
    delay(2000);
    lcd.clear();

  });

  server.begin();
}
 
void loop(){}