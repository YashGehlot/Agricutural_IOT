// V1.1.0 - underDevel
// *Sensors get power only at the time of broadcast
// 2 onboard LED - Red --> MESH_STATUS LED
// Constantly ON --> When the node is not in the network
// Blink Repeteadly --> When less number of nodes are present
// Blue LED --> broadcast led
// Blink --> When message is broadcasted
// 
// V1.0.1 - no_timing easyMesh used --> Eliminate getNodeTime() and getChipId()
// node restart
// Sleep Mode - In future versions
// V1.0.2 - additional LED functions, restart bug
// V1.1.0 - double gas sensor in storage mode,
// dip switch - 1 - powerOn node
//              2 - mq2 & mq4
//              3 - moisture   
// Modes - MODE0 MODE1 - 01 - moisture,dht --> field mode
//                     - 10 - mq2,mq4,dht  --> storage mode
//                     - 11 - moisture,mq2,mq4,dht --> ultimate

#include <easyMesh.h>
#include <DHT_U.h>
#include <DHT.h>

#define   MESH_PREFIX     "FarmAssist"
#define   MESH_PASSWORD   "agriculturalIOT"
#define   MESH_PORT       0001

#define DHTTYPE DHT11   // DHT 11

/*
static const uint8_t D0   = 16;  MESH_STATUS_LED
static const uint8_t D1   = 5;   DHT_PIN
static const uint8_t D2   = 4;   POWER_MOISTURE
static const uint8_t D3   = 0;   MODE0
static const uint8_t D4   = 2;   BROADCAST_LED
static const uint8_t D5   = 14;  POWER_DHT
static const uint8_t D6   = 12;  POWER_MQ2
static const uint8_t D7   = 13;  MODE1
static const uint8_t D8   = 15;  POWER_MQ4
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;
*/

// PINS
const int DHT_PIN = 5;
const int POWER_DHT = 14;
const int POWER_MQ2 = 12;
const int POWER_MQ4 = 15;
const int POWER_MOISTURE = 4;
const int MESH_STATUS_LED = 16 ;
const int BROADCAST_LED= 2 ;
const int MODE0 = 0;
const int MODE1 = 13;

// timing variables
int i = 0;
int restart = 0;


// Mesh Constants
const int NUMBER_OF_NODES = 6;
const int BROADCAST_TIME = 10000; // 10 seconds
const int RESTART_TIME = 600000; // 600 seconds - 10 min
const int MESH_START_TIME = 10000; // 10 seconds

// Varius strings
String analog_sensor = "";

// Initialize easyMesh
easyMesh  mesh;
DHT dht(DHT_PIN, DHTTYPE);


void setup() {
  Serial.begin(9600);
  
  pinMode(POWER_DHT,OUTPUT); // power for sensors
  pinMode(POWER_MQ2,OUTPUT);
  pinMode(POWER_MQ4,OUTPUT);
  pinMode(POWER_MOISTURE,OUTPUT);

  pinMode(MODE0,INPUT); // mode select input
  pinMode(MODE1,INPUT);
  
  pinMode(MESH_STATUS_LED,OUTPUT);
  pinMode(BROADCAST_LED,OUTPUT);
  
  digitalWrite(BROADCAST_LED,HIGH);
  //mesh.setDebugMsgTypes( ERROR | MESH_STATUS_LED | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  //mesh.setDebugMsgTypes( ERROR | STARTUP | MESH_STATUS_LED );  // set before init() so that you can see startup messages
  Serial.println("Restart:Initializing hotspot");
  
  digitalWrite(MESH_STATUS_LED,LOW);
  digitalWrite(BROADCAST_LED,LOW);
  delay(1000);
  digitalWrite(MESH_STATUS_LED,HIGH);
  digitalWrite(BROADCAST_LED,HIGH);

  Serial.println("Saving Power - Turning on wifi in "+ (String)(MESH_START_TIME/1000) + "seconds");
  delay(MESH_START_TIME);
  
  mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT );
  mesh.setReceiveCallback( &receivedCallback );
  mesh.setNewConnectionCallback( &newConnectionCallback );
  Serial.println("Hotspot Created");

  //randomSeed( analogRead( A0 ) );  
}

void loop() {
  mesh.update();
  // MESH_STATUS_LED
  ledBlink(mesh.connectionCount(),50,500);
  i = i + ( 5*mesh.connectionCount() ) + 50 ; // to compensate for the delays used in ledBlink()
  restart = restart + ( 5*mesh.connectionCount() ) + 50 ;
  
  delay(10);
  i = i + 1;
  restart= restart + 1;
 
  Serial.println(mesh.connectionCount());
  // ******************************broadcasting Message******************************
  // ********************************************************************************
  if ( i > (BROADCAST_TIME-700 + random(0,200))/10 && ( digitalRead(MODE0) || digitalRead(MODE1) ) ){ // broadcast after BROADCAST_TIME + some random time
    String msg;
    
    // Node Mode Identifier and Analog Sensor Routine
    if( not digitalRead(MODE0) &&  digitalRead(MODE1) ) { // field mode
         msg = "IOT_Field**";
         analogRoutine(POWER_MOISTURE,"M",&msg);
         
      }
    if( digitalRead(MODE0) && not digitalRead(MODE1) ) { // storage mode
         msg = "IOT_Storage**"; 
         analogRoutine(POWER_MQ2,"S",&msg);
         delay(50);
         analogRoutine(POWER_MQ4,"**G",&msg);
      }
    if( digitalRead(MODE0) && digitalRead(MODE1) ) { // ultimate mode
         msg = "IOT_Ultimate**";
         analogRoutine(POWER_MOISTURE,"M",&msg);
         delay(50);
         analogRoutine(POWER_MQ2,"**S",&msg);
         delay(50);
         analogRoutine(POWER_MQ4,"**G",&msg);
      }    
    
    //********************************************************************************
    // DHT Sensor Routine
    digitalWrite(POWER_DHT,HIGH);
    delay(300);
    float h = dht.readHumidity();
    float t = dht.readTemperature(); // celcius
    if ( not isnan(h) ){ // Fail check - humidity
          msg += "**H"+(String)h;
      }
    else {
      msg += "**HNoInput";}
    if (  not isnan(t) ) { // Fail Check - temperature
          msg += "**T"+(String)t;
      }
    else {
      msg += "**TNoInput";}
    digitalWrite(POWER_DHT,LOW);
    //*********************************************************************************
    // Final message broadcast
    msg += "**C"+(String)mesh.getChipId()+"**N" + (String)mesh.connectionCount();
    Serial.println(msg);
    if( mesh.connectionCount() !=0 ){ 
      mesh.sendBroadcast(msg); 
      digitalWrite(BROADCAST_LED,LOW);
      delay(100);
      digitalWrite(BROADCAST_LED,HIGH);
      Serial.println("Broadcasted");
    }
    i = 0;
    }
  //***********************************************************************************
  // Restart Node
  if( restart > RESTART_TIME/10 ){
    ESP.restart();
    restart = 0;
  }
  //***********************************************************************************
}


void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("startHere: Received from %d msg=%s\n", from, msg.c_str());
}


void newConnectionCallback( bool adopt ) {
  Serial.printf("startHere: New Connection, adopt=%d\n", adopt);
}
void ledBlink (int reps, int onTime, int period){
    for (int j = 0; j<reps;j++){
      digitalWrite(MESH_STATUS_LED,LOW);
      delay(onTime);
      digitalWrite(MESH_STATUS_LED,HIGH);
      delay(onTime);
    }
    delay(period-onTime);
  } 
void analogRoutine ( int power , String prefix,String *msg){
     digitalWrite(power,HIGH);
     delay(300);
     (*msg) += prefix +(String)analogRead(A0);
     delay(200);
     digitalWrite(power,LOW);
  }
