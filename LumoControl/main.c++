#include <WiFi.h>

const char *ssid = "SSID";
const char *password = "PASSWORD";

WiFiServer server(80); // Start a web server on port 80

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    // Connect to Wi-Fi
    Serial.print("Connecting to Wi-Fi");
    WiFi.begin(ssid, password);

    unsigned long startAttemptTime = millis();

    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 20000)
    { // 20-second timeout
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\nConnected to Wi-Fi!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        server.begin();
    }
    else
    {
        Serial.println("\nFailed to connect to Wi-Fi.");
    }
}

void loop()
{
    WiFiClient client = server.available(); // Listen for incoming clients

    if (client)
    {
        Serial.println("New client connected!");
        String request = "";
        while (client.available())
        {
            char c = client.read();
            request += c;
            if (c == '\n')
                break; // Stop reading after the first line
        }

        Serial.println("Request: " + request);

        // Control LED based on request
        if (request.indexOf("/LED=ON") != -1)
        {
            digitalWrite(LED_BUILTIN, HIGH); // Turn on the LED
        }
        else if (request.indexOf("/LED=OFF") != -1)
        {
            digitalWrite(LED_BUILTIN, LOW); // Turn off the LED
        }

        client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
        client.print("<!DOCTYPE HTML>");
        client.print("<html>");
        client.print("<head>");
        client.print("<style>");
        client.print("body { background-color: #000; color: #FFF; font-family: Arial, sans-serif; text-align: center; padding: 20px; }");
        client.print("h1 { font-size: 80px; }");
        client.print(".button { background-color: #007BFF; color: white; border: none; padding: 20px 30px; font-size: 60px; cursor: pointer; border-radius: 15px; margin: 5px; }");
        client.print(".button:hover { background-color: #0056b3; }");
        client.print(".status { font-size: 35px; margin-top: 20px; }");
        client.print("</style>");
        client.print("</head>");
        client.print("<body>");
        client.print("<h1>LED Control</h1>");
        client.print("<p><button class=\"button\" onclick=\"window.location.href='/LED=ON'\">Turn On</button></p>");
        client.print("<p><button class=\"button\" onclick=\"window.location.href='/LED=OFF'\">Turn Off</button></p>");

        if (digitalRead(LED_BUILTIN) == HIGH)
        {
            client.print("<p class=\"status\">LED: On</p>");
        }
        else
        {
            client.print("<p class=\"status\">LED: Off</p>");
        }

        client.print("</body>");
        client.print("</html>");

        client.stop();
        Serial.println("Client disconnected.");
    }
}
