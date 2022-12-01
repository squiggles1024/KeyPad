# Custom Gaming KeyPad

My second 'finished' prototype of an embedded systems project. This is largely inspired by professional gaming 'keypads' developed by Logitech and Razer. They are essentially a small formfactor keyboard with a button layout that is (supposedly) more ergonomic for gaming. It was programmed on an STM32F4 "Black Pill Board".

This keypad was designed for use with "MMO" style games that require large numbers of easily accessible keys that will map to your character's attacks, abilities, and interface windows (such as the 'pause' menu). In particular, this was designed with World of Warcraft in mind. It features 64 buttons, an LCD capactive touch screen with 12 'touch buttons', and an analog joystick which currently funtions as a mousewheel. The purpose of this project was largely to see how many keybinds I could comfortably fit in the footprint of a typical 'gaming keypad'.
![Final Prototype](images/keypad_front.jpg)

The buttons in the 2nd row from the top are "Navigation switches". These can be tilted in 4 directions and pressed in; thus this single device can function as 5 different buttons. All keys, switches, touch buttons, and joy stick directions (up to 8) can be programmed to function as 1 modifier key (ctrl, shift, alt), a mouse click, mousewheel movement, or a keystroke. As an example, a button can be programmed to be the equivalent of pressing "Mouse Button 3", "Q", "Left Ctrl", and "Mouse Wheel Up" at the same time. It cannot do multiple keystoes/mouse clicks at one: as in pressing a key cannot be the equivalent of pressing "Q + W", or "Mouse 4 + Mouse 5" simultaneously.
![KeyPadModel Final](images/KeyPadModel_Final.png)

The touchscreen is intended to be used to access the users 'menu interface windows' such as opening their inventory or friends list (buttons that don't need to be pressed often or need to be easily within reach in a pinch). The icons are stored as uchar arrays in the mcu's flash which is programmed into the lcd screen at startup. 
![TopDownView](images/keypad_topdown.jpg)

The Black pill board does not have enough GPIO pins to serve all 64 buttons, and the SPI bus for the touch screen, so GPIO expander bonnets were used instead (thank you Adafruit). There are 4 expanders in total, and these are polled using DMA in a round-robin fashion.
![Bonnet](images/ExpanderBonnet.png)

