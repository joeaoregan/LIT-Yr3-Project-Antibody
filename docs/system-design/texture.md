# Texture

## Overview (`Texture.h`, `Texture.cpp`)

```text
┌-------------------------------┐
|            Texture            |
├-------------------------------┤
| -m_TextureMap: std::map       | - Map to store textures
| -s_pInstance: Texture*        | - Single Instance of Texture class used in Game
| -m_Texture: SDL_Texture*      | - The actual hardware texture
| -m_TextSurface: SDL_Surface*  | - Surface used to create textures
| -m_Width: int                 | - Texture width
| -m_Height: int                | - Texture height
| -m_X: int                     | - Texture X coordinate
| -m_Y: int                     | - Texture Y coordinate
| -m_Alpha: int                 | - Texture Alpha value (moved to Game Object)
| -m_Flash: bool                | - Flash the texture
├-------------------------------┤
| +Instance() : static Texture* | - Single instance of Textures used throughout Game
| +loadTextureMedia() : bool    | - Load media for Texture class
| +load() : bool                | - Load an image to the texture map
| +loadTexture() : SDL_Texture* | - Loads individual image as texture
| +loadFromFile() : bool        | - Loads image at specified path
| +renderTextToTexture() : bool | - Create a texture from text
| +renderMap() : void           | - Render a texture from the map, given an ID
| +renderP() : void             | - render to a point
| +render() : void              | - Texture Render function
| +free() : void                | - Deallocates texture
| +setColor() : void            | - Set color modulation
| +setBlendMode() : void        | - Set blending
| +modifyAlpha() : void         | - Set alpha modulation
| +flashGameObject() : void     | - Flash texture for game object
| +getFlash() : void            | - Flash the object or not
| +setFlash() : void            | - Set the object to flash or not
| +getAlpha() : int             | - Get alpha value for flashing / transparent textures
| +setAlpha() : void            | - Set alpha value for flashing / transparent textures
| +getX() : int                 | - Get X coordinate
| +setX() : void                | - Set X coordinate
| +getY() : int                 | - Get Y coordinate
| +setY() : void                | - Set Y coordinate
| +getWidth() : int             | - Get texture width
| +getHeight() : int            | - Get texture height
| +getTextureMap() : std::map   | - Get entire texture map
| +clearTextureMap() : void     | - Clear the entire texture map
| +clearFromTextureMap() : void | - Clear the texture from the map using ID
| +getTexture() : SDL_Texture*  | - Get a texture from the map using ID
| +weaponIndicator() : void     | - Custom function to render weapon indicators
| +loadInputText() : void       | - Custom render function for input text
| +loadEnterNameText() : void   | - Custom function for rendering text for name
| +UIText() : void              | - Render Text for player scores, FPS, and Level
| +UITextTimer() : void         | - Render Text for Game Timer
| +UITextPlayerMessage() : void | - Custom function to render Player Message
| +numRocketsLeft() : void      | - Indicate the number of rockets each player has left
| +speedBoostText() : void      | - Indicates a speedboost is active
└-------------------------------┘
```

The `Texture` class manages all hardware-accelerated rendering operations using `SDL_Texture` and `SDL_Surface`.

!!! tip "Singleton Design Pattern"
    The Singleton design pattern (`s_pInstance`) in core managers provides global access to shared assets and eliminates redundant loader calls.

## Core Capabilities

* **Central Texture Map**: Stores loaded textures in a `std::map<std::string, SDL_Texture*>` indexed by string IDs, loaded from an array via `loadTextureMedia()`.
* **Font Rendering**: Uses `TTF_RenderText_Solid()` to convert TrueType font strings into hardware textures.
* **Transformations**: Handles texture rotation around `SDL_Point` centres, colour modulation (`SDL_SetTextureColorMod`), blending modes, and alpha transparency flashing (`modifyAlpha()`).
