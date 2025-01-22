#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <ESP32Servo.h>

Servo servo1; // Horizontal 
Servo servo2; // Vertical

int posC4 = 150;
int posD4 = 132;
int posE4 = 115;
int posF4 = 96;
int posG4 = 80;
int posA4 = 60;
int posB4 = 45;
int posC5 = 30;


int upperPosition = 125;
int lowerPosition = 140;

String currentPos;


#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b" 
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8" 

BLECharacteristic *pCharacteristic;

class BLEServerCB : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer, esp_ble_gatts_cb_param_t *param) override {
    Serial.println("Client connected.");
  }

  void onDisconnect(BLEServer *pServer) override {
    Serial.println("Client disconnected. Restarting advertising...");
    BLEDevice::startAdvertising();
  }
} bleServerCB;

void setup() {
  Serial.begin(115200);

  servo1.attach(26); 
  servo2.attach(25); 
  servo2.write(upperPosition);
  servo1.write(posF4);

  BLEDevice::init("ESP32_Servo");

  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(&bleServerCB);


  BLEService *pService = pServer->createService(SERVICE_UUID);

  
  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_WRITE_NR
  );

  pCharacteristic->addDescriptor(new BLE2902());

  pService->start();

  BLEDevice::setMTU(512);
  esp_ble_conn_update_params_t conn_params = {
    .min_int = 0x06, 
    .max_int = 0x06, 
    .latency = 0,    
    .timeout = 400  
  };

  esp_ble_gap_update_conn_params(&conn_params);

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06); 
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  Serial.println("Waiting for a client to connect...");
}

 int valuesRecieved=0 ;
void loop() {
 std::string value = pCharacteristic->getValue();
if (!value.empty()) {
  int number = atoi(value.c_str());
  if (number >= 1 && number <= 100) {
    Serial.println(number); 
    pCharacteristic->setValue(""); 
    valuesRecieved++;
  }
  if (number == 99){
    Serial.println("total package recieved: ");
    Serial.print(valuesRecieved);
    valuesRecieved=0;
  }
}
   if (pCharacteristic->getValue() == "C4") {
            pCharacteristic->setValue(""); 
            Serial.println("Note C4 played");
            Serial.println(currentPos);
            servo1.attach(26);
            delay(2);
            servo1.write(155);
            delay(200); 
            servo1.detach();

            
            currentPos="C4";
            //valuesRecieved++; --test--
            //Serial.println("package recieved: ");
           // Serial.print(valuesRecieved);
           
           
            servo2.attach(25);
            delay(2);
            servo2.write(lowerPosition);
            delay(100); 
            servo2.write(upperPosition);
            delay(100);
            servo2.detach();
   }
    
    if (pCharacteristic->getValue() == "D") {
            pCharacteristic->setValue("");
            Serial.println("Note D4 played");
            delay(2);
            servo1.attach(26);
            servo1.write(posD4);
            delay(200);
            servo1.detach();
              
            
            currentPos="D4";

            
            servo2.attach(25);
            delay(2);
            servo2.write(lowerPosition);
            delay(100);
            servo2.write(upperPosition);
            delay(100);
            servo2.detach();
            
    }
    if (pCharacteristic->getValue() == "E") {
            pCharacteristic->setValue(""); 
            Serial.println("Note E4 played");
            servo1.attach(26);
            delay(2);
            servo1.write(posE4);
            delay(200); 
            servo1.detach();
              
            
            currentPos="E4";
            
            servo2.attach(25);
            delay(2);
            servo2.write(lowerPosition);
            delay(100);
            servo2.write(upperPosition);
            delay(100);
            servo2.detach();
            
    }
    if (pCharacteristic->getValue() == "F") {
            pCharacteristic->setValue(""); 
            Serial.println("Note F4 played");
            servo1.attach(26);
            delay(2);
            servo1.write(posF4);
            delay(200);
            servo1.detach();
              
            
            currentPos="F4";


            servo2.attach(25);
            delay(2);
            servo2.write(lowerPosition);
            delay(100); 
            servo2.write(upperPosition);
            delay(100);
            servo2.detach();
            
    }

    if (pCharacteristic->getValue() == "G") {
            pCharacteristic->setValue("");
            Serial.println("Note G4 played");
            servo1.attach(26);
            delay(2);
            servo1.write(posG4);
            delay(200); 
            servo1.detach();
              
            currentPos="G4";

            
            servo2.attach(25);
            delay(2);
            servo2.write(lowerPosition);
            delay(100); 
            servo2.write(upperPosition);
            delay(100);
            servo2.detach();
            
    }

    if (pCharacteristic->getValue() == "A") {
            pCharacteristic->setValue(""); 
            Serial.println("Note A4 played");
            servo1.attach(26);
            delay(2);
            servo1.write(posA4);
            delay(200); 
            servo1.detach();
              
            currentPos="A4";
            
           
            servo2.attach(25);
            delay(2);
            servo2.write(lowerPosition);
            delay(100);
            servo2.write(upperPosition);
            delay(100);
            servo2.detach();
            
    }

    if (pCharacteristic->getValue() == "B") {
            pCharacteristic->setValue(""); 
            Serial.println("Note B4 played");
            servo1.attach(26);
            delay(2);
            servo1.write(posB4);
            delay(200);
            servo1.detach();
              
            currentPos="B4";
            
            
            servo2.attach(25);
            delay(2);
            servo2.write(lowerPosition);
            delay(100);
            servo2.write(upperPosition);
            delay(100);
            servo2.detach();
            
    }

    if (pCharacteristic->getValue() == "C5") {
            pCharacteristic->setValue("");
            Serial.println("Note C5 played");
            servo1.attach(26);
            delay(2);
            servo1.write(posC5);
            delay(300); 
            servo1.detach();
              
            currentPos="C5";
            
           
            servo2.attach(25);
            delay(2);
            servo2.write(lowerPosition);
            delay(100); 
            servo2.write(upperPosition);
            delay(100);
            servo2.detach();
         
    }
    
}
  

