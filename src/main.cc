// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#ifndef UNIT_TEST
// Import required libraries
#include <Arduino.h>
#include <WiFi.h>

#include "../include/credentials.h"

// must define char *ssid and char *pass)
#include "builder.h"         // NOLINT
#include "http_parser.h"     // NOLINT
#include "process_parser.h"  // NOLINT
#include "process_runner.h"  // NOLINT

// Create an instance of the server
WiFiServer server(80);

ProcessRunner* processRunner = NULL;

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

  String msg;

  auto stop = [&client, &msg]() -> void {
    if (msg.length() > 0) client.println(msg);
    client.stop();
  };

  while (!client.available()) {
    delay(10);
  }

  Serial.println(client.remoteIP(client.fd()));

  // parse http
  HttpParser* request = BuildHttpParser(client.readString());
  if (request->ok() == false) {
    msg = request->err();
    stop();
    return;
  }

  ProcessParser* parser = BuildProcessParser(request->body());
  if (parser->ok() == false) {
    msg = parser->err();
    stop();
    return;
  }

  delete processRunner;
  processRunner = BuildProcessRunner(parser);
  stop();
}
#endif  // UNIT_TEST
