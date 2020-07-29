// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

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
void ok(WiFiClient client);
void showPage(WiFiClient client);
void createProcess(char* readBuffer);

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
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Indicate the IP address
  Serial.println(WiFi.localIP());

  createProcess(http_test_data);
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

  // read request
  auto bytesRead = client.readBytes(readBuffer, sizeof(readBuffer));
  if (bytesRead >= sizeof(readBuffer)) {
    Serial.println(kOverflow);
    client.stop();
    return;
  }
  // null terminate
  readBuffer[bytesRead] = '\0';
  createProcess(readBuffer);
  client.stop();
}

void createProcess(char* readBuffer) {
  JsonWriter writer(1024);

  // parse http
  HttpText httpText;
  HttpParser* httpParser = BuildHttpParser(readBuffer, &writer, &httpText);
  if (httpParser->ok() == false) {
    Serial.println(httpParser->ReadError(errBuffer, sizeof(errBuffer)));
    delete httpParser;
    return;
  }
  delete httpParser;

  Process* replaceProcess = new Process();
  ProcessParser* processParser =
      BuildProcessParser(httpText.body(), &writer, replaceProcess);
  if (processParser->ok() == false) {
    Serial.println(httpParser->ReadError(errBuffer, sizeof(errBuffer)));
    delete processParser;
    return;
  }

  delete processParser;
  delete process;
  delete processRunner;
  process = replaceProcess;
  processRunner = new ProcessRunner(process);
}
#endif  // ARDUNIO
