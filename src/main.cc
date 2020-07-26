// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#if defined(ARDUINO)
// Import required libraries
#include <Arduino.h>
#include <WiFi.h>

#include "../include/credentials.h"

// must define char *ssid and char *pass)
#include "builder.h"         // NOLINT
#include "http_parser.h"     // NOLINT
#include "json_writer.h"     // NOLINT
#include "process_parser.h"  // NOLINT
#include "process_runner.h"  // NOLINT

// Create an instance of the server
WiFiServer server(80);

ProcessRunner* processRunner = NULL;

char readBuffer[1024];
char errBuffer[1024];
const char* kOverflow = "Read Buffer overflow";

void ok(WiFiClient client);
void showPage(WiFiClient client);

void setup() {
  // Start Serial
  Serial.begin(9600);

  // Connect to WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Indicate the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // check for new WiFi requests
  WiFiClient client = server.available();
  if (!client) {
    if (processRunner != NULL) {
      processRunner->Run();
    }
    return;
  }

  char* msg = NULL;

  auto stop = [&client, &msg]() -> void {
    if (strlen(msg) > 0) client.println(msg);
    client.stop();
  };

  while (!client.available()) {
    delay(10);
  }

  Serial.println(client.remoteIP(client.fd()));

  // read request
  auto bytesRead = client.readBytes(readBuffer, sizeof(readBuffer));
  if (bytesRead >= sizeof(readBuffer)) {
    strncpy(errBuffer, kOverflow, sizeof(errBuffer));
    msg = errBuffer;
    stop();
    return;
  }
  // null terminate
  readBuffer[bytesRead] = '\0';

  JsonWriter* writer = new JsonWriter(1024);

  // parse http
  HttpParser* request = BuildHttpParser(readBuffer, writer);
  if (request->ok() == false) {
    msg = request->ReadError(errBuffer, sizeof(errBuffer));
    stop();
    return;
  }

  ProcessParser* parser = BuildProcessParser(request->args().body(), writer);
  if (parser->ok() == false) {
    parser->ReadError(errBuffer, sizeof(errBuffer));
    stop();
    return;
  }

  delete processRunner;
  auto args = parser->args();
  processRunner = BuildProcessRunner(&args);
}
#else
int main() {}
#endif  // ARDUNIO
