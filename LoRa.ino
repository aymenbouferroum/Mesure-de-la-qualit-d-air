// First install "The Things Network library" via the Library Manager
// Then import the package
#include <TheThingsNetwork.h>


// Set your AppEUI and AppKey corresponding to your Application
const char *appEui = "0000000000000000";
const char *appKey = "D1A03A431CD058800784D4A99BD96DEE";

// Type the following lines to create two serial port objects for Serial and Serial1.
#define loraSerial Serial1
#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
//Here we have replace with TTN_FP_EU868
#define freqPlan TTN_FP_EU868

//This will create a TheThingsNetwork object named ttn with loraSerial, debugSerial, and freqPlan as inputs.
TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

// Function that splits string data into substrings using the specified separator
String getValue(String data, char separator, int index){
    // Variable to count the number of substrings found
    int found = 0;
    // Variable to indicate the starting index 0 and the ending index -1 of a string
    int strIndex[] = { 0, -1 }; 
    // Get the length of the string data
    int maxIndex = data.length() - 1;
    
    // Loop until reaching the end of the string or finding a new substring
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        // Check if the character at index i is the specified separator or it's the end of the string
        if (data.charAt(i) == separator || i == maxIndex) {
            // Increment the variable found when finding a new substring
            found++;
            // Storing the starting index of the new found substring
            strIndex[0] = strIndex[1] + 1;
            // Storing the index of the separator , to indicate the ending index of the new found substring
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    // If you find a new substring return it, else return an empty string
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setup()
{
  //This will call the begin() function for each serial port object to set the baud rate for serial data transmission.
  loraSerial.begin(57600);
  debugSerial.begin(9600);

  // Wait a maximum of 10s don't jump to the next line until the Serial Monitor is ready
  while (!debugSerial && millis() < 10000);

  debugSerial.println("-- STATUS");
  // Retrieve some useful device-specific information from the Microchip LoRa module and prints them on the Serial Monitor.
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  //Sending join request to the server to get session Keys and establish communication
  ttn.join(appEui, appKey);

}

void loop()
{
  Serial.begin ( 9600 ) ;
  // Creates an empty string to store data received from Serial port
  String mesure;
  // Prepare an empty unsigned integer array of size 4 to store data measurements
  uint16_t tab[4];
  // Check if there is Bytes available for reading from the serial port
  while (Serial.available())
  {
    // reads characters from the serial buffer into a String
    mesure = Serial.readString();
    // Split string data into substrings with space as a separator using getValue Function defined above
    // Get Temperature value as a string
    String t = getValue(mesure, ' ', 0);
    // Get Humidity value as a string
    String h = getValue(mesure, ' ', 1);
    // Get CO2 value as a string
    String c = getValue(mesure, ' ', 2);
    // Get TVOC value as a string
    String tvoc = getValue(mesure, ' ', 3);
    // Convert Values from string data type to Float
    // Then multiply each value by 100 to get rid of the decimal point
    tab[0]=t.toFloat()*100;
    tab[1]=h.toFloat()*100;
    tab[2]=c.toFloat()*100;
    tab[3]=tvoc.toFloat()*100;
    
  }
 
  debugSerial.println("-- LOOP");
  // Prepare data for sending it to the TTN Server
  // Creates an empty bytes array of size 8 to store data after preparation
  byte payload[8];
  // Get the integer part of Temperature value and convert it to byte
  payload[0] = highByte(tab[0]);
  // Get the fractional part of Temperature value and convert it to byte
  payload[1] = lowByte(tab[0]);
  // Get the integer part of Humidity value and convert it to byte
  payload[2] = highByte(tab[1]);
  // Get the fractional part of Humidity value and convert it to byte
  payload[3] = lowByte(tab[1]);
  // Get the integer part of CO2 value and convert it to byte
  payload[4] = highByte(tab[2]);
  // Get the fractional part of CO2 value and convert it to byte
  payload[5] = lowByte(tab[2]);
  // Get the integer part of TVOC value and convert it to byte
  payload[6] = highByte(tab[3]);
  // Get the fractional part of TVOC value and convert it to byte
  payload[7] = lowByte(tab[3]);
  
  // Send data to the TTN Server, function accepts the data to be sent and the size of data.
  ttn.sendBytes(payload, sizeof(payload));
  
  // makes 1 second delay between each message, this should be the same as measurement interval
  delay(1000);
}
