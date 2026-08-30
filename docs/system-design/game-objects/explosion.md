# Explosion

## Overview (`Explosion.h`)

```text
┌---------------------------┐
|          Explosion        |
├---------------------------┤
| +move() : virtual void    | - Explosions are static, sets animation frame
| +destroy() : virtual void | - Destroy using Game Object destroy function
| +render() : virtual void  | - Use Game Objects animation rendering
└---------------------------┘
```

The `Explosion` class manages visual impact animations triggered by collisions and entity destructions.

* **Sprite Variations**: Includes mechanical ship explosions, red blood splatter animations for blood cells, and recoloured blue/orange splatter sheets for virus enemies.
* **Animation**: Each explosion instance tracks its own independent frame counter (`m_CurrentFrame`), allowing simultaneous explosions to start and finish independently without frame synchronization bugs.

# Sprite Sheets

![Explosion animation sprite sheet](../../images/explosion/Explosion.png)
    
    Explosion animation sprite sheet

![Blood explosion animation sprite sheet](../../images/explosion/ExplosionBlood.png)

    Blood explosion animation sprite sheet

![Blue virus explosion animation sprite sheet](../../images/explosion/ExplosionVirusBlue.png)

    Blue virus explosion animation sprite sheet

![Green virus explosion animation sprite sheet](../../images/explosion/ExplosionVirusGreen.png)

    Green virus explosion animation sprite sheet

![Orange virus explosion animation sprite sheet](../../images/explosion/ExplosionVirusOrange.png)

    Orange virus explosion animation sprite sheet