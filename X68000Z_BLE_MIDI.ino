/*

  X68000Z UART-MIDI to BLE-MIDI adapter

  Copyright (c) 2023 Prime9999
  Released under the MIT license
  https://opensource.org/licenses/mit-license.php

  Wiring:
    X68000Z UART    ESP32 development board
         RED(RX) -- IO17
        BLUE(TX) -- IO16
      GREEN(GND) -- GND

 */
#include <Arduino.h>
#include <HardwareSerial.h>
#include <MIDI.h>
#include <BLEMIDI_Transport.h>
#include <hardware/BLEMIDI_ESP32.h>

#define UART_SPEED 38400
#define UART_RX 16
#define UART_TX 17

HardwareSerial uartSerial(2);

struct uartSettings : public midi::DefaultSettings
{
   static const long BaudRate = UART_SPEED;
};
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, uartSerial, uartMIDI, uartSettings);
BLEMIDI_CREATE_INSTANCE("", bleMIDI);

void setup() {
  // Initialize X68000Z UART-MIDI port
  uartSerial.begin(UART_SPEED, SERIAL_8N1, UART_RX, UART_TX);
  uartMIDI.begin(MIDI_CHANNEL_OMNI);
  uartMIDI.turnThruOff();

  // Initialize BLE-MIDI port
  bleMIDI.begin(MIDI_CHANNEL_OMNI);
  bleMIDI.turnThruOff();
}

void loop() {
  // X68000Z UART-MIDI -> BLE-MIDI
  if (uartMIDI.read()) {
    bleMIDI.send(
      uartMIDI.getType(),
      uartMIDI.getData1(),
      uartMIDI.getData2(),
      uartMIDI.getChannel()
    );
  }

  // BLE-MIDI -> X68000Z UART-MIDI
  if (bleMIDI.read()) {
     uartMIDI.send(
      bleMIDI.getType(),
      bleMIDI.getData1(),
      bleMIDI.getData2(),
      bleMIDI.getChannel()
    );
 }
}
