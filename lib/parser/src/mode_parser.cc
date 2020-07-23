// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include "mode_parser.h"  // NOLINT

const int maxPins = 16;

void ModeParser::Parse(const JsonObject &obj) {
  String mode = obj["mode"];
  if (mode.length() == 0) this->AppendError("Mode missing");

  String signal = obj["signal"];
  if (signal.length() == 0) this->AppendError("Signal missing");

  if (obj["id"].isNull() == true) {
    this->AppendError("Pin id missing");
  }

  if (this->ok() == false) return;

  uint8_t pin = obj["id"];
  if (pin < 0 || pin >= maxPins) {
    this->AppendError("Pin id out of range");
    return;
  }

  this->set_mode(mode);
  this->set_signal(signal);
  this->set_pin(pin);

  if (this->signal() != 'd' && this->signal() != 'a')
    this->AppendError("Signal must be analog or digital");

  if (this->mode() != 'o' && this->mode() != 'i')
    this->AppendError("Mode must input or output");

  if (this->mode() == 'o' && this->signal() != 'd')
    this->AppendError("Output to digital only");
}
