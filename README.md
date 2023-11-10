# X68000Z UART-MIDI to BLE-MIDI adapter
Simple MIDI adapter implementation which converts X68000Z UART-MIDI to BLE-MIDI.

## Requirments
* X68000Z
* X68000Z UART cable
* ESP32 development board (ex. ESP32-DevKitC)
* BLE-MIDI Device (ex. CME WIDI Jack w/MIDI DIN-5 Cable)
* MIDI Sound Module (ex. Roland MT-32)

## Wiring
|X6800Z UART cable|ESP32 development board|
|:-:|:-:|
|RED(RX)|IO17|
|BLUE(TX)|IO16|
|GREEN(GND)|GND|

## How to use
1. Open Arduino IDE
2. Add "BLE-MIDI" library
3. Compile and write this sketch to ESP32 development board