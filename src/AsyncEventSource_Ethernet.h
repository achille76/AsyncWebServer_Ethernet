/****************************************************************************************************************************
  AsyncEventSource_Ethernet.h - Dead simple AsyncWebServer for ESP8266 using W5x00/ENC8266 Ethernet

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

#pragma once

#ifndef ASYNCEVENTSOURCE_ETHERNET_H_
#define ASYNCEVENTSOURCE_ETHERNET_H_

#include <Arduino.h>

#if defined(ESP32)
  #include <AsyncTCP.h>
#endif

#include <AsyncWebServer_Ethernet.hpp>
#include "AsyncWebSynchronization_Ethernet.h"

// Ethernet
#include <Crypto/Hash.h>

/////////////////////////////////////////////////////////

#define SSE_MAX_QUEUED_MESSAGES 32
//#define SSE_MAX_QUEUED_MESSAGES 8

#define DEFAULT_MAX_SSE_CLIENTS 8
//#define DEFAULT_MAX_SSE_CLIENTS 4

/////////////////////////////////////////////////////////

class AsyncEventSource;
class AsyncEventSourceResponse;
class AsyncEventSourceClient;
typedef std::function<void(AsyncEventSourceClient *client)> ArEventHandlerFunction;

/////////////////////////////////////////////////////////

class AsyncEventSourceMessage
{
  private:
    uint8_t * _data;
    size_t _len;
    size_t _sent;
    //size_t _ack;
    size_t _acked;

  public:
    AsyncEventSourceMessage(const char * data, size_t len);
    ~AsyncEventSourceMessage();
    size_t ack(size_t len, uint32_t time __attribute__((unused)));
    size_t send(AsyncClient *client);

    /////////////////////////////////////////////////

    inline bool finished()
    {
      return _acked == _len;
    }

    /////////////////////////////////////////////////

    inline bool sent()
    {
      return _sent == _len;
    }
};

/////////////////////////////////////////////////
/////////////////////////////////////////////////

class AsyncEventSourceClient
{
  private:
    AsyncClient *_client;
    AsyncEventSource *_server;
    uint32_t _lastId;
    LinkedList<AsyncEventSourceMessage *> _messageQueue;
    void _queueMessage(AsyncEventSourceMessage *dataMessage);
    void _runQueue();

  public:

    AsyncEventSourceClient(AsyncWebServerRequest *request, AsyncEventSource *server);
    ~AsyncEventSourceClient();

    /////////////////////////////////////////////////

    inline AsyncClient* client()
    {
      return _client;
    }

    /////////////////////////////////////////////////

    void close();
    void write(const char * message, size_t len);
    void send(const char *message, const char *event = NULL, uint32_t id = 0, uint32_t reconnect = 0);

    /////////////////////////////////////////////////

    inline bool connected() const
    {
      return (_client != NULL) && _client->connected();
    }

    /////////////////////////////////////////////////

    inline uint32_t lastId() const
    {
      return _lastId;
    }

    /////////////////////////////////////////////////

    inline size_t  packetsWaiting() const
    {
      return _messageQueue.length();
    }

    /////////////////////////////////////////////////

    //system callbacks (do not call)
    void _onAck(size_t len, uint32_t time);
    void _onPoll();
    void _onTimeout(uint32_t time);
    void _onDisconnect();
};

/////////////////////////////////////////////////
/////////////////////////////////////////////////

class AsyncEventSource: public AsyncWebHandler
{
  private:
    String _url;
    LinkedList<AsyncEventSourceClient *> _clients;
    ArEventHandlerFunction _connectcb;

  public:
    AsyncEventSource(const String& url);
    ~AsyncEventSource();

    /////////////////////////////////////////////////

    inline const char * url() const
    {
      return _url.c_str();
    }

    /////////////////////////////////////////////////

    void close();
    void onConnect(ArEventHandlerFunction cb);
    void send(const char *message, const char *event = NULL, uint32_t id = 0, uint32_t reconnect = 0);
    size_t count() const; //number clinets connected
    size_t  avgPacketsWaiting() const;

    //system callbacks (do not call)
    void _addClient(AsyncEventSourceClient * client);
    void _handleDisconnect(AsyncEventSourceClient * client);
    virtual bool canHandle(AsyncWebServerRequest *request) override final;
    virtual void handleRequest(AsyncWebServerRequest *request) override final;
};

/////////////////////////////////////////////////
/////////////////////////////////////////////////

class AsyncEventSourceResponse: public AsyncWebServerResponse
{
  private:
    String _content;
    AsyncEventSource *_server;

  public:
    AsyncEventSourceResponse(AsyncEventSource *server);
    void _respond(AsyncWebServerRequest *request);
    size_t _ack(AsyncWebServerRequest *request, size_t len, uint32_t time);

    /////////////////////////////////////////////////

    inline bool _sourceValid() const
    {
      return true;
    }
};

#endif /* ASYNCEVENTSOURCE__ETHERNET_H_ */
