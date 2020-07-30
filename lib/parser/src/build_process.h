// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <process_runner.h>
#include <writer.h>

ProcessRunner* buildProcess(char* readBuffer, Writer* writer);
