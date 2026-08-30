# Gamepad

## Overview (`Gamepad.h`)

The `Gamepad.h` module provides helper functions and diagnostics for direct hardware controller integration via SDL GameController and Joystick APIs.

* **Hardware Polling**: Detects connected controllers, logging names, button counts, axis counts, trackballs, and hat switches.
* **Diagnostics**: Helped resolve driver issues where controllers (such as the NVIDIA Shield controller) registered duplicate device instances due to built-in touchpads.
