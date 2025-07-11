/****************************************************************************************************************************
  AsyncWebServer_Ethernet.h - Dead simple AsyncWebServer for ESP8266 using W5x00/ENC8266 Ethernet

  AsyncWebServer_Ethernet is a library for the Ethernet with lwIP_5100, lwIP_5500 or lwIP_enc28j60 library

  Based on and modified from ESPAsyncWebServer (https://github.com/me-no-dev/ESPAsyncWebServer)
  Built by Khoi Hoang https://github.com/khoih-prog/AsyncWebServer_Ethernet

  Copyright (c) 2016 Hristo Gochkov. All rights reserved.
  This file is part of the esp8266 core for Arduino environment.
  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
  as published bythe Free Software Foundation, either version 3 of the License, or (at your option) any later version.
  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
  You should have received a copy of the GNU General Public License along with this program.
  If not, see <https://www.gnu.org/licenses/>.

  Version: 1.5.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.4.1   K Hoang      18/03/2022 Initial coding for ESP8266 using W5x00/ENC8266 Ethernet.
                                  Bump up version to v1.4.1 to sync with AsyncWebServer_STM32 v1.4.1
  1.5.0   K Hoang      05/10/2022 Option to use non-destroyed cString instead of String to save Heap
  1.5.1   K Hoang      10/11/2022 Add examples to demo how to use beginChunkedResponse() to send in chunks
 *****************************************************************************************************************************/

#ifndef _ASYNC_WEBSERVER_ETHERNET_H_
#define _ASYNC_WEBSERVER_ETHERNET_H_

/////////////////////////////////////////////////////////

#if defined(ESP32)
  #include <AsyncTCP.h>
#endif



/////////////////////////////////////////////////////////

#include "AsyncWebServer_Ethernet.hpp"

#include "AsyncWebResponseImpl_Ethernet.h"
#include "AsyncWebHandlerImpl_Ethernet.h"
#include "AsyncWebSocket_Ethernet.h"
#include "AsyncEventSource_Ethernet.h"

#endif /* _ASYNC_WEBSERVER_ETHERNET_H_ */
