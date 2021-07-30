# WIP: Sofle Mario Theme Keyboard Settings with IBM PC/AT Layout

> Configured only for macOS.

This is a fork of default keymap of Sofle. Layout is highly close to **BM PC/AT** layout since my primary keyboard is HHKB.

![IMG_5815](https://user-images.githubusercontent.com/196477/127565134-b600c1fa-9dc1-452d-a192-5a569ed2f756.jpg)

## OLED Features
- Left Screen
  - A jumping mushroom while CAPS LOCK
  - Show current layer
  - Show currently pressed key
- Right Screen
  - Mario game animation with WPM information (originally forked and rescaled for 128x32 OLED display from https://github.com/b0rv3g4r4/Kyria-Mario-Keymap/)

## Left Screen on Action

### Left OLED Layers
- Star or Mushroom Animation on CAPS LOCK
- Layer Info: Base, Lower or Raise
- CAPS LOCK or empty space
- Pressed Key Name

![IMG_5818](https://user-images.githubusercontent.com/196477/127566150-43367c5d-bcd5-4e49-9346-d2035087faed.gif)


## Right Screen on Action

### Right OLED Layers
- WPM information
- Mario Animation

![IMG_5836](https://user-images.githubusercontent.com/196477/127719384-867004ad-91c9-4116-8516-7534da9af985.gif)

## Encoders

### ENCODER_RESOLUTION Setting
Some encoders' resolution may need to be set to `4`, otherwise the encoders will double action per tick.

On file `qmk_firmware/keyboards/sofle/rev1/config.h`, you may need to change following setting to `4`.

```C
#define ENCODER_RESOLUTION 4
```

## Layouts

Layout is very close to **IBM PC/AT** configuration similar to **HHKB**.

- CTRL is at left

### Base Layout

