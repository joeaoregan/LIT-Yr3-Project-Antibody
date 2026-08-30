# Game Object Abstract

## Overview (`GameObjectAbstract.h`)

```text
┌---------------------------┐
|    GameObjectAbstract     |
├---------------------------┤
| +move() : virtual void    | - Move the Game Object
| +destroy() : virtual void | - Destroy the Game Object
└---------------------------┘
```

A pure virtual abstract interface defining the mandatory contract for all game entities.

```cpp
class GameObjectAbstract {
public:
    virtual void move() = 0;
    virtual void destroy() = 0;
};

```

* `move()`: Forces derived objects to implement position and animation update logic.
* `destroy()`: Forces derived objects to implement boundary checking and deallocation triggers.
