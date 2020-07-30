// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once

char http_bad_method[] = R"~~(GET /process/replace HTTP/1.1
Host: localhost
)~~";

char http_test_data[] = R"~~(POST /process/replace HTTP/1.1
Host: localhost
User-Agent: Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.5) Gecko/20091102 Firefox/3.5.5 (.NET CLR 3.5.30729)
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip,deflate
Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7
Keep-Alive: 300
Connection: keep-alive
Referer: http://localhost/test.php
Content-Type: application/x-www-form-urlencoded
Content-Length: 778
 
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
    "id": 2,
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
  },
  {
   "sequence": 4,
   "type": "HALL",
   "command": {
    "measurement": 500
   }
  }
 ]
} 
)~~";
