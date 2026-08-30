# Collisions

## Overview (`Collision.h`)

```text
┌-----------------------┐
|      Collision.h      |
├-----------------------┤
| +checkCollision(*a,*b)| - Check collision between two objects, return true/false
└-----------------------┘
```

Collision detection is handled using **Axis-Aligned Bounding Box (AABB)** intersection testing. Each active game object maintains an `SDL_Rect` bounding volume mapped to its `(X, Y)` position and dimensions.

## Collision Logic

The `checkCollision(SDL_Rect *a, SDL_Rect *b)` function compares the minimum and maximum boundaries of two bounding boxes:

* `leftA = a->x`, `rightA = a->x + a->w`
* `topA = a->y`, `bottomA = a->y + a->h`
* `leftB = b->x`, `rightB = b->x + b->w`
* `topB = b->y`, `bottomB = b->y + b->h`

If any side of box `A` is completely outside box `B` on either axis, the function returns `false`. If overlap occurs across both the X and Y axes simultaneously, it returns `true`, triggering the appropriate gameplay response (e.g., health reduction, weapon destruction, or power-up collection).
