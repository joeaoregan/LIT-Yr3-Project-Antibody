# Buttons

## Overview (`Button.h`, `Button.cpp`)

```text
┌------------------------------┐
|            Button            |
├------------------------------┤
| -m_callbackID: int           | - Callback, assigns an action to button
| -m_bReleased: bool           | - Boolean value indicates if button is released
| +mPosition: SDL_Point        | - Holds the coordinates for button position
| +mCurrentSprite: ButtonSprite| - Enum holding value of current button
├------------------------------┤
| +getCallBackID() : int       | - Get callback ID integer value
| +setCallBack() : void        | - Set callback value
| +setPosition() : void        | - set top left position of button
| +handleEvent() : void        | - Handle button events
| +render() : void             | - Render button to screen
| +getButtonSprite() :         | - Return current button sprite enum value
| +setButtonSprite() : void    | - Set current button sprite enum value
└------------------------------┘
```

The Button class manages interactive UI buttons across the Main Menu, Settings Menu, and High Scores screens.

* **State Tracking**: Uses the `ButtonSprite` enum to track whether a button is unselected, hovered, or clicked.
* **Positioning**: Uses `SDL_Point` structures to define the 2D coordinates and boundaries of the clickable area.

## Key Functions

* `handleEvent()`: Evaluates mouse motion and mouse button events (`SDL_MOUSEMOTION`, `SDL_MOUSEBUTTONDOWN`, `SDL_MOUSEBUTTONUP`). It checks whether the cursor coordinates lie within the button's `SDL_Rect` and assigns the appropriate sprite state and callback action.
* `setCallback()` / `getCallbackID()`: Maps specific menu functions or state transitions to the button.
* `render()`: Draws the active button sprite clip and rendered text label to the screen.
