# =============================================================================
# # ---------------------------------------------------------------------------
# # Creation Date: 01-sep-2021
# # Author: Bibekananda Nayak
# # Version: 1.0
# #
# # ---------------------------------------------------------------------------#
# =============================================================================
//Blynk Home Automation with Physical Button and ON OFF State Feedback


#define BLYNK_PRINT Serial            
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266mDNS.h>  // For OTA with ESP8266
#include <WiFiUdp.h>  // For OTA
#include <ArduinoOTA.h>  // For OTA
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

BlynkTimer timer;

void checkPhysicalButton();

int relay1State = LOW;
int pushButton1State = HIGH;

int relay2State = LOW;
int pushButton2State = HIGH;

int relay3State = LOW;
int pushButton3State = HIGH;

int relay4State = LOW;
int pushButton4State = HIGH;

#define AUTH "fEiDsasesr9kAQB7zzN1aTvqvng0fbrM"  // You should get Auth Token in the Blynk App.  
#define WIFI_SSID "JioFi_4391CE"                   //Enter Wifi Name
#define WIFI_PASS "sxdcsq137j"                   //Enter wifi Password

#define SERVER "blynk-cloud.com "             // Comment-out if use Blynk hosted cloud service
#define PORT 8442


const uint16_t kRecvPin = 0;

IRrecv irrecv(kRecvPin);

decode_results results;

#define IR_SEND_PIN  10
#define DEBUG_SW 1

#define REMOTE_LIGHT1_DATA 3772818013
#define REMOTE_LIGHT2_DATA 3772834333
#define REMOTE_LIGHT3_DATA 3772797613
#define REMOTE_LIGHT4_DATA 3772781293



#define RELAY_PIN_1      12   //D6
#define RELAY_PIN_2      16   //D0
#define RELAY_PIN_3       4   //D2
#define RELAY_PIN_4       5   //D1 

#define PUSH_BUTTON_1     2   //D4
#define PUSH_BUTTON_2    14   //D5
#define PUSH_BUTTON_3    13   //D7
#define PUSH_BUTTON_4     1   //TX

#define VPIN_BUTTON_1    V12 
#define VPIN_BUTTON_2    V13
#define VPIN_BUTTON_3    V14
#define VPIN_BUTTON_4    V15  

#define OTA_HOSTNAME "Home_Automation"


BLYNK_CONNECTED() {

  // Request the latest state from the server

//  Blynk.syncVirtual(VPIN_BUTTON_1);
//  Blynk.syncVirtual(VPIN_BUTTON_2);
//   Blynk.syncVirtual(VPIN_BUTTON_3);
//  Blynk.syncVirtual(VPIN_BUTTON_4);

  // Alternatively, you could override server state using:
  Blynk.virtualWrite(VPIN_BUTTON_1, relay1State);
  Blynk.virtualWrite(VPIN_BUTTON_2, relay2State);
  Blynk.virtualWrite(VPIN_BUTTON_3, relay3State);
  Blynk.virtualWrite(VPIN_BUTTON_4, relay4State);

}

// When App button is pushed - switch the state

BLYNK_WRITE(VPIN_BUTTON_1) {
  relay1State = param.asInt();
  digitalWrite(RELAY_PIN_1, relay1State);
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  relay2State = param.asInt();
  digitalWrite(RELAY_PIN_2, relay2State);
}
BLYNK_WRITE(VPIN_BUTTON_3) {
  relay3State = param.asInt();
  digitalWrite(RELAY_PIN_3, relay3State);
}
BLYNK_WRITE(VPIN_BUTTON_4) {
  relay4State = param.asInt();
  digitalWrite(RELAY_PIN_4, relay4State);
}

void checkPhysicalButton()
{
  if (digitalRead(PUSH_BUTTON_1) == LOW) {
    // pushButton1State is used to avoid sequential toggles
    if (pushButton1State != LOW) {

      // Toggle Relay state
      relay1State = !relay1State;
      digitalWrite(RELAY_PIN_1, relay1State);

      // Update Button Widget
      Blynk.virtualWrite(VPIN_BUTTON_1, relay1State);
    }
    pushButton1State = LOW;
  } else {
    pushButton1State = HIGH;
  }

  if (digitalRead(PUSH_BUTTON_2) == LOW) {
    // pushButton2State is used to avoid sequential toggles
    if (pushButton2State != LOW) {

      // Toggle Relay state
      relay2State = !relay2State;
      digitalWrite(RELAY_PIN_2, relay2State);

      // Update Button Widget
      Blynk.virtualWrite(VPIN_BUTTON_2, relay2State);
    }
    pushButton2State = LOW;
  } else {
    pushButton2State = HIGH;
  }

  if (digitalRead(PUSH_BUTTON_3) == LOW) {
    // pushButton3State is used to avoid sequential toggles
    if (pushButton3State != LOW) {

      // Toggle Relay state
      relay3State = !relay3State;
      digitalWrite(RELAY_PIN_3, relay3State);

      // Update Button Widget
      Blynk.virtualWrite(VPIN_BUTTON_3, relay3State);
    }
    pushButton3State = LOW;
  } else {
    pushButton3State = HIGH;
  }

  if (digitalRead(PUSH_BUTTON_4) == LOW) {
    // pushButton4State is used to avoid sequential toggles
    if (pushButton4State != LOW) {

      // Toggle Relay state
      relay4State = !relay4State;
      digitalWrite(RELAY_PIN_4, relay4State);

      // Update Button Widget
      Blynk.virtualWrite(VPIN_BUTTON_4, relay4State);
    }
    pushButton4State = LOW;
  } else {
    pushButton4State = HIGH;
  }
}
void irsense()
{
  if (irrecv.decode(&results)) {
    Serial.print("Result - "); Serial.println(results.value);
    if ( results.value == REMOTE_LIGHT1_DATA)
    {
      // Toggle Relay state
      relay1State = !relay1State;
      digitalWrite(RELAY_PIN_1, relay1State);
//      Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
//      serialPrintUint64(results.value);
//      Serial.println("");
      // Update Button Widget
      Blynk.virtualWrite(VPIN_BUTTON_1, relay1State);
      delay(100);
    }

    if ( results.value == REMOTE_LIGHT2_DATA)
    {
      // Toggle Relay state
      relay2State = !relay2State;
      digitalWrite(RELAY_PIN_2, relay2State);
      Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
      serialPrintUint64(results.value);
      Serial.println("");
      // Update Button Widget
      Blynk.virtualWrite(VPIN_BUTTON_2, relay2State);
      delay(100);
    }

    if ( results.value == REMOTE_LIGHT3_DATA)
    {
      // Toggle Relay state
      relay3State = !relay3State;
      digitalWrite(RELAY_PIN_3, relay3State);
      Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
      serialPrintUint64(results.value);
      Serial.println("");
      // Update Button Widget
      Blynk.virtualWrite(VPIN_BUTTON_3, relay3State);
      delay(100);
    }

    if ( results.value == REMOTE_LIGHT4_DATA)
    {
      // Toggle Relay state
      relay4State = !relay4State;
      digitalWrite(RELAY_PIN_4, relay4State);
      Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
      serialPrintUint64(results.value);
      Serial.println("");
      // Update Button Widget
      Blynk.virtualWrite(VPIN_BUTTON_4, relay4State);
      delay(100);
    }

    irrecv.resume();
  }
}
void setup()
{

  Serial.begin(115200);
  Blynk.begin(AUTH, WIFI_SSID, WIFI_PASS,"blynk-cloud.com", 8442);
  ArduinoOTA.setHostname(OTA_HOSTNAME);  // For OTA - Use your own device identifying name
  ArduinoOTA.begin();  // For OTA
  irrecv.enableIRIn();  // Start the receiver
  
  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(PUSH_BUTTON_1, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_1, relay1State);


  pinMode(RELAY_PIN_2, OUTPUT);
  pinMode(PUSH_BUTTON_2, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_2, relay2State);


  pinMode(RELAY_PIN_3, OUTPUT);
  pinMode(PUSH_BUTTON_3, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_3, relay3State);


  pinMode(RELAY_PIN_4, OUTPUT);
  pinMode(PUSH_BUTTON_4, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_4, relay4State);

  // Setup a function to be called every 100 ms
  timer.setInterval(500L, checkPhysicalButton);
}


void loop()
{
  Blynk.run();
  ArduinoOTA.handle();  // For OTA
  timer.run();
  irsense();
}
