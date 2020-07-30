// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <mode_parser.h>

const int maxPins = 16;

void ModeParser::Parse(const JsonObject &obj) {
  Writer *writer = this->writer();
  const char *mode = obj["mode"];
  if (strlen(mode) == 0) writer->Write("Mode missing");

  const char *signal = obj["signal"];
  if (strlen(signal) == 0) writer->Write("Signal missing");

  if (obj["id"].isNull() == true) {
    writer->Write("Pin id missing");
  }

  if (this->ok() == false) return;

  uint8_t pin = obj["id"];
  if (pin < 0 || pin >= maxPins) {
    writer->Write("Pin id out of range");
    return;
  }

  auto args = this->args();

  args->set_mode(*mode);
  args->set_signal(*signal);
  args->set_pin(pin);

  if (args->signal() != 'd' && args->signal() != 'a')
    writer->Write("Signal must be analog or digital");

  if (args->mode() != 'o' && args->mode() != 'i')
    writer->Write("Mode must input or output");

  if (args->mode() == 'o' && args->signal() != 'd')
    writer->Write("Output to digital only");
}
