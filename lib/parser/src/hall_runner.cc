// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <hall_runner.h>

void HallRunner::Run() {
  auto hall = this->args();
#if defined(ARDUINO)
  int measurement = hallRead();
  hall->set_measurement(measurement);
#else
  // hall->set_measurement(measurement_);
  printf("hallRead() = %d;\n", hall->measurement());
#endif  // ARDUINO
  this->writer()->Write(hall->measurement());
}
