# Snake3D

![Travis Build Status](https://travis-ci.org/FabianReister/Snake3D.svg?branch=master)

Play Snake on a 8x8x8 LED Cube using a Wii Nunchuck. This project is written to run on a raspberry pi,
but you can run this on any linux computer providing a I2C bus.

## Things you need
  - embedded device (e.g. Raspberry Pi 2)
  - Wii Nunchuck to control snake movement
  - LED Cube


### Wii Nunchuck
To learn more about how to connect a Nunchuck, read [this article](http://web.engr.oregonstate.edu/~johnstay/ece375/pdf/nunchuk.pdf).

## Howto run

Open a terminal and cd into the Snake3D directory. To compile this code, execute
<code>mkdir build && cd build && cmake .. && make </code>

To run, execute
<code> ./build/src/snake3d</code> for now

## Simulator

There is also a simulator available that is a substitute for a led cube. Starting the simulator is quite simple. On your embedded device (with connected Wii Nunchuck), execute <code> ./build/sim/snake3dsim</code> for now.
Then, on your desktop, open Blender (download from blender.org). client.py should be opened by default. Press button **Run script** and see the snake move based on the jockstick's state.


## Dependencies

Ubuntu 24

libgtest-dev