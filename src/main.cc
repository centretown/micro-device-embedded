// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#if !defined(ARDUINO)
#include "native_main.h"  // NOLINT
#else
#include <Arduino.h>
#include <WiFi.h>

// must define char *ssid and char *pass)
#include <builder.h>
#include <http_parser.h>
#include <json_writer.h>
#include <process_parser.h>
#include <process_runner.h>

#include "../include/credentials.h"
#include "../include/process_test_data.h"

WiFiServer server(80);
ProcessRunner* buildProcess(char* readBuffer, Writer* writer);

ProcessRunner* processRunner = NULL;
Process* process = NULL;

char readBuffer[4096];
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
  Serial.println("WiFi connected.");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Indicate the IP address
  Serial.println(WiFi.localIP());

  // start blink as default
  JsonWriter writer(1024);
  processRunner = buildProcess(http_test_data, &writer);
  if (processRunner == NULL) {
    Serial.println(writer.Read(errBuffer, sizeof(errBuffer)));
  } else {
    process = processRunner->args();
  }
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

  while (!client.available()) {
    delay(10);
  }

  Serial.println(client.remoteIP(client.fd()));

  auto bytesRead = client.readBytes(readBuffer, sizeof(readBuffer));
  if (bytesRead >= sizeof(readBuffer)) {
    Serial.println(kOverflow);
    client.stop();
    return;
  }
  readBuffer[bytesRead] = '\0';
  JsonWriter writer(1024);
  ProcessRunner* replaceRunner = buildProcess(readBuffer, &writer);
  if (replaceRunner == NULL) {
    Serial.println(writer.Read(errBuffer, sizeof(errBuffer)));
  } else {
    delete processRunner;
    delete process;
    processRunner = replaceRunner;
    process = processRunner->args();
  }
  client.stop();
}

#endif  // ARDUNIO
