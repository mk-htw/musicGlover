/*
  Battery Monitor

  This example creates a Bluetooth® Low Energy peripheral with the standard battery service and
  level characteristic. The A0 pin is used to calculate the battery level.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.

  You can use a generic Bluetooth® Low Energy central app, like LightBlue (iOS and Android) or
  nRF Connect (Android), to interact with the services and characteristics
  created in this sketch.

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>


#define KEYCODE_MEDIA_PLAY (0xB0 | 0xE400)
#define KEYCODE_MEDIA_PAUSE (0xB1 | 0xE400)
#define KEYCODE_MEDIA_RECORD (0xB2 | 0xE400)
#define KEYCODE_MEDIA_FAST_FORWARD (0xB3 | 0xE400)
#define KEYCODE_MEDIA_REWIND (0xB4 | 0xE400)
#define KEYCODE_MEDIA_NEXT_TRACK (0xB5 | 0xE400)
#define KEYCODE_MEDIA_PREV_TRACK (0xB6 | 0xE400)
#define KEYCODE_MEDIA_STOP (0xB7 | 0xE400)
#define KEYCODE_MEDIA_EJECT (0xB8 | 0xE400)
#define KEYCODE_MEDIA_RANDOM_PLAY (0xB9 | 0xE400)
#define KEYCODE_MEDIA_PLAY_PAUSE (0xCD | 0xE400)
#define KEYCODE_MEDIA_PLAY_SKIP (0xCE | 0xE400)
#define KEYCODE_MEDIA_MUTE (0xE2 | 0xE400)
#define KEYCODE_MEDIA_VOLUME_INC (0xE9 | 0xE400)
#define KEYCODE_MEDIA_VOLUME_DEC (0xEA | 0xE400)


#define KEYCODE_ANDROID_MEDIA_VOLUME_UP (24 | 0x18)
#define KEYCODE_ANDROID_MEDIA_PLAY_PAUSE (85 | 0x55)

// Bluetooth® Low Energy Battery Service
BLEService batteryService("180F");

// Bluetooth® Low Energy Battery Level Characteristic
BLEUnsignedCharCharacteristic batteryLevelChar("2A19",                // standard 16-bit characteristic UUID
                                               BLERead | BLENotify);  // remote clients will be able to get notifications if this characteristic changes


BLEService mediaKeyService("1849");                                       // Erstellt einen BLE-Service
BLEUnsignedCharCharacteristic mediaKeyChar("2BA4", BLERead | BLENotify);  // Erstellt eine BLE-Charakteristik

int oldBatteryLevel = 0;  // last battery level reading from analog input
long previousMillis = 0;  // last time the battery level was checked, in ms

void setup() {
  Serial.begin(9600);  // initialize serial communication
  while (!Serial)
    ;

  pinMode(LED_BUILTIN, OUTPUT);  // initialize the built-in LED pin to indicate when a central is connected

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }

  /* Set a local name for the Bluetooth® Low Energy device
     This name will appear in advertising packets
     and can be used by remote devices to identify this Bluetooth® Low Energy device
     The name can be changed but maybe be truncated based on space left in advertisement packet
  */
  BLE.setLocalName("musicGlover");
  BLE.setAdvertisedService(mediaKeyService);       // add the service UUID
  batteryService.addCharacteristic(mediaKeyChar);  // add the battery level characteristic
  BLE.addService(mediaKeyService);                 // Add the battery service
  mediaKeyChar.writeValue(oldBatteryLevel);        // set initial value for this characteristic

  /* Start advertising Bluetooth® Low Energy.  It will start continuously transmitting Bluetooth® Low Energy
     advertising packets and will be visible to remote Bluetooth® Low Energy central devices
     until it receives a new connection */

  // start advertising
  BLE.advertise();

  Serial.println("Bluetooth® device active, waiting for connections...");
}

void loop() {
  // wait for a Bluetooth® Low Energy central
  BLEDevice central = BLE.central();

  // if a central is connected to the peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's BT address:
    Serial.println(central.address());
    // turn on the LED to indicate the connection:
    digitalWrite(LED_BUILTIN, HIGH);

    // check the battery level every 200ms
    // while the central is connected:
    while (central.connected()) {
      long currentMillis = millis();
      // if 1s have passed, check the increase volume level:
      if (currentMillis - previousMillis >= 1000) {
        previousMillis = currentMillis;
        Serial.println("Send Media Keycode volume up");
        mediaKeyChar.writeValue(KEYCODE_ANDROID_MEDIA_PLAY_PAUSE);
        //updateBatteryLevel();
      }
    }
    // when the central disconnects, turn off the LED:
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}

void updateBatteryLevel() {
  /* Read the current voltage level on the A0 analog input pin.
     This is used here to simulate the charge level of a battery.
  */
  int battery = analogRead(A0);
  int batteryLevel = map(battery, 0, 1023, 0, 100);

  if (batteryLevel != oldBatteryLevel) {       // if the battery level has changed
    Serial.print("Battery Level % is now: ");  // print it
    Serial.println(batteryLevel);
    batteryLevelChar.writeValue(batteryLevel);  // and update the battery level characteristic
    oldBatteryLevel = batteryLevel;             // save the level for next comparison
  }
}
