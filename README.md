**_PURPOSE OF CODE_**
-> Use an ESP32 as a web client to interact with a RESTful API to implement GET and PUT requests using WiFi, HTTPClient, and ArduinoJson

**_EXPECTED BEHAVIOUR OF CODE_**

**-> Setup()**
Purpose: Initializes the ESP32, sets up WiFi, and configures the LED pin.

Steps:

Starts Serial communication (Serial.begin(115200)).

Connects to WiFi using credentials from env.h.

Waits until the WiFi connection is established.

Prints the ESP32’s local IP address.

Sets up LED_PIN as an output to control the LED.

**-> Loop()**
Purpose: Repeatedly fetches light status from the API and sends temperature data.

Steps:

Check WiFi Connection: Ensures the ESP32 is connected before making API requests.

GET Request (/api/light):

Requests the light state from the API.

Parses the JSON response to check if the light should be ON or OFF.

Updates the LED state based on the API response.

PUT Request (/api/temp):

Reads the temperature sensor value (or uses a placeholder value).

Sends the temperature as a JSON request to the API.

Prints the API response for debugging.



