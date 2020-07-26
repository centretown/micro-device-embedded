// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "mode_parser.h"  // NOLINT

const int maxPins = 16;

void ModeParser::Parse(const JsonObject &obj) {
  const char *mode = obj["mode"];
  if (strlen(mode) == 0) this->WriteError("Mode missing");

  const char *signal = obj["signal"];
  if (strlen(signal) == 0) this->WriteError("Signal missing");

  if (obj["id"].isNull() == true) {
    this->WriteError("Pin id missing");
  }

  if (this->ok() == false) return;

  uint8_t pin = obj["id"];
  if (pin < 0 || pin >= maxPins) {
    this->WriteError("Pin id out of range");
    return;
  }

  auto args = this->args();

  args.set_mode(*mode);
  args.set_signal(*signal);
  args.set_pin(pin);

  if (args.signal() != 'd' && args.signal() != 'a')
    this->WriteError("Signal must be analog or digital");

  if (args.mode() != 'o' && args.mode() != 'i')
    this->WriteError("Mode must input or output");

  if (args.mode() == 'o' && args.signal() != 'd')
    this->WriteError("Output to digital only");
}
