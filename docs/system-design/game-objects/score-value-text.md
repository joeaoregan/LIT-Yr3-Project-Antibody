# Score Value Text

## Overview (`ScoreValueText.h`, `ScoreValueText.cpp`)

```text
┌----------------┐
| ScoreValueText |
├----------------┤
| +move()        | - Move Score Value to the Player who scored it
| +destroy()     | - Inherit destroy from GameObject
| +render()      | - Render texture to screen, different colour for each Player
└----------------┘
```

`ScoreValueText` provides floating point score indicators when enemies are destroyed.

* **Movement**: Spawns at the point of enemy destruction and drifts towards the scoring player's ship.
* **Visuals**: Uses distinct colour coding (red/orange for Player 1, blue/green for Player 2) with lowered alpha transparency to avoid obscuring gameplay.
* **Architecture**: Each score instance manages its own texture to prevent all onscreen scores snapping to the latest value.