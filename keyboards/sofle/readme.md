# Sofle Keyboard

![SofleKeyboard version 1](https://i.imgur.com/S5GTKth.jpeg)

Compile the firmware:

    qmk compile -kb sofle -km rgb_default

Flash the keymap: 

    make sofle:default:avrdude

Press reset button on he keyboard when asked.

Disconnect the first half, connect the second one and repeat the process.
