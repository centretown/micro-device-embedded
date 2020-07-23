// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once

const char* process_test_data = R"~~(
{
 "label": "Process 1",
 "deviceKey": "esp32-200",
 "purpose": "Blink",
 "setup": [
  {
   "sequence": 0,
   "type": "MODE",
   "command": {
    "id": 2,
    "signal": "digital",
    "mode": "output"
   }
  }
 ],
 "loop": [
  {
   "sequence": 0,
   "type": "PIN",
   "command": {
    "id": 2,
    "signal": "digital",
    "mode": "output",
    "value": 1
   }
  },
  {
   "sequence": 1,
   "type": "DELAY",
   "command": {
    "duration": 200
   }
  },
  {
   "sequence": 2,
   "type": "PIN",
   "command": {
    "id": 3,
    "signal": "digital",
    "mode": "output",
    "value": 0
   }
  },
  {
   "sequence": 3,
   "type": "DELAY",
   "command": {
    "duration": 500
   }
  }
 ]
} 
)~~";
