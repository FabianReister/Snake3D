# Snake3D

![Travis Build Status](https://travis-ci.org/FabianReister/Snake3D.svg?branch=master)

Play Snake on a 8x8x8 LED Cube using a Wii Nunchuck. This project is written to run on a Raspberry Pi, but you can run this on any linux computer providing an I2C bus.

## Things you need

  - Embedded device (e.g. Raspberry Pi >=2)
  - Wii Nunchuck to control snake movement
  - LED Cube

There is also a simulation mode available. If you are curious about playing Snake in Blender, see the section `Simulator` below.

### Wii Nunchuck

To learn more about how to connect a Nunchuck, read [this article](https://bootlin.com/labs/doc/nunchuk.pdf).

## Building this project

### Prerequisites

In order to build this project, ensure that the following dependencies are met:

- CMake >= 3.28
- GCC >= 9 with C++20 support

Optional:

- GTest (e.g., through `libgtest-dev`)

### Building

From the root of the project

    mkdir build
    cd build

    cmake ..

    make

    # Optionally, install the project
    (sudo) make install


In order to configure the project, the following CMake options are available:

- `SNAKE3D_BUILD_TESTS`: Build the tests (requires GTest)
- `SNAKE3D_BUILD_SIMULATOR`: Build the simulator

After a successful build, the following executables will be available:

- `build/app/snake3d/snake3d`: the *main* application to run on a Raspberry Pi
- `build/app/snake3d_sim/snake3d_sim`: the *simulation* application to run on any PC

## Simulator

There is a simulator available as a substitute for a real LED cube. It is based on Blender.

Starting the simulator is quite simple. Either (1) on your embedded device (with a connected Wii Nunchuck), or (2) any PC with a keyboard, execute `build/app/snake3d_sim/snake3d_sim`.

Then, on your desktop, open Blender (download from blender.org). client.py should be opened by default. Run the script (by pressing the button **Run script**) and see the snake move based on the jockstick's state.


## Real LED Cube

*Schematics will follow.*
