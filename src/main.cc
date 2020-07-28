// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#if !defined(ARDUINO)
#include "native_main.h"  // NOLINT
#else
#include <Arduino.h>
#include <WiFi.h>

// must define char *ssid and char *pass)
#include "../include/credentials.h"
#include "builder.h"         // NOLINT
#include "http_parser.h"     // NOLINT
#include "json_writer.h"     // NOLINT
#include "process_parser.h"  // NOLINT
#include "process_runner.h"  // NOLINT

WiFiServer server(80);
void ok(WiFiClient client);
void showPage(WiFiClient client);

ProcessRunner* processRunner = NULL;

char readBuffer[1024];
char errBuffer[1024];
const char* kOverflow = "Read Buffer overflow";

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

  char* msg = "ok";

  auto stop = [&client, &msg]() -> void {
    if (msg != NULL && strlen(msg) > 0) Serial.println(msg);
    client.stop();
  };

  while (!client.available()) {
    delay(10);
  }

  Serial.println(client.remoteIP(client.fd()));

  // read request
  auto bytesRead = client.readBytes(readBuffer, sizeof(readBuffer));
  if (bytesRead >= sizeof(readBuffer)) {
    Serial.println(kOverflow);
    client.stop();
    return;
  }
  // null terminate
  readBuffer[bytesRead] = '\0';
  JsonWriter* writer = new JsonWriter(1024);

  // parse http
  HttpText httpText;
  HttpParser* request = BuildHttpParser(readBuffer, writer, &httpText);
  if (request->ok() == false) {
    Serial.println(request->ReadError(errBuffer, sizeof(errBuffer)));
    client.stop();
    return;
  }

  Process* process = new Process();
  ProcessParser* parser =
      BuildProcessParser(request->args()->body(), writer, process);
  if (parser->ok() == false) {
    Serial.println(request->ReadError(errBuffer, sizeof(errBuffer)));
    client.stop();
    return;
  }

  delete processRunner;
  processRunner = new ProcessRunner(process);
}
#endif                       // ARDUNIO
