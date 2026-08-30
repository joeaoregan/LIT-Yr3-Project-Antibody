# Status Bar

## Overview (`StatusBar.h`, `StatusBar.cpp`)

```text
┌----------------------------┐
|          StatusBar         |
├----------------------------┤
| +startTime: float = 3.0    | - Start time for countdown timer bars
| +endTime: float = 0.0      | - End time for countdown timer bars
| +fgColour: SDL_Color       | - Set bar foreground colour as green
| +fgColourBlue: SDL_Color   | - Set bar foreground colour as Blue
| +bgColour: SDL_Color       | - Set bar background colour as red
| +bgColourOrange: SDL_Color | - Set bar background colour as Orange
| +bgColourBlue: SDL_Color   | - Set bar background colour as Blue
├----------------------------┤
| +createStatusBar() : void  | - Main status bar creation function
| +playerHealthBar() : void  | - Health bar for players
| +virusTimer() : bool       | - Countdown timer bar for exploding Orange Virus
| +virusTimerBlue() : bool   | - Countdown timer bar for Blue Virus Enemies
| +rocketPowerBar() : void   | - Rocket power bar timer
| +speedBoostBar() : void    | - Speed boost timer bar
| +enemyBossBar() : void     | - Enemy Boss health bar
└----------------------------┘
```

`StatusBar` is a utility class for drawing dynamic horizontal and vertical progress bars.

## Rendering Technique

Constructed using two overlapping `SDL_Rect` shapes:

1. A background rectangle representing maximum capacity.
2. A foreground rectangle whose width or height scales proportionally to the remaining percentage of the tracked value.

* **Applications**: Used for Player Health, Boss Health, Rocket Charge Power, Speed Boost duration, and Orange/Blue Virus countdown timers.
