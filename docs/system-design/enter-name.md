# Enter Name

## Overview (`EnterName.h`, `EnterName.cpp`)

```text
┌------------------------------┐
|          EnterName           |
├------------------------------┤
| +gFont: TTF_Font* = NULL     | - Font used when rendering Enter Name text
| +gNameMenuTextTexture1:      | - Texture for Enter Name title text
| +gNameMenuTextTexture2:      | - Return to Main Menu button text
| +gNameMenuTextTexture3:      | - Reset text entered button text
| +gNameMenuTextTexture4:      | - Enter Name prompt text
| +gNameButtons: Button        | - Array of buttons
| +gSpriteClipsName: SDL_Rect  | - Sprite clips for button animations
| +gButtonSpriteSheetTexture4: | - Sprite animation Texture
├------------------------------┤
| +loadNameMedia() : bool      | - Load media for Enter Name state
| +closeNameMedia() : void     | - Free media for Enter Name from memory
| +handleNameEvents() : void   | - Handle button events
| +draw() : void               | - Render Enter Name state to screen
└------------------------------┘
```

The `EnterName` class was designed as a dedicated input state to capture player names for high score recording.

* **Purpose**: Isolates SDL text-input events (`SDL_TEXTINPUT`) from game flight controls to prevent input conflicts and overhead during active gameplay.
* **Components**: Manages font textures, prompt labels, character buffers, and menu return buttons.
