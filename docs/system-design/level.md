# Level

## Overview (`Level.h`, `Level.cpp`)

```text
┌---------------┐
|     Level     |
├---------------┤
| +loadMedia()  | - Load media for each level
| +update()     | - Update level objects movement etc
| +render()     | - Render level objects to screen
| +clearMedia() | - Free level media from memory
└---------------┘
```

The `Level` class was designed to encapsulate level-specific assets, background scripts, enemy spawn tables, and update routines.

* **Purpose**: Intended to decouple level management from the monolithic `Game` class, enabling modular loading, execution, and clearing of level media.

## Sprites

![Level 1](../images/ui/Level1.png)

    Level 1

![Level 2](../images/ui/Level2.png)

    Level 2

![Level 3](../images/ui/Level3.png)

    Level 3