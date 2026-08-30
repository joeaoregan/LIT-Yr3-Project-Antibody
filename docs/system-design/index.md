# System Design & Configuration

## Overview

The architecture of **AntiBody** is structured using C++ and the SDL2 library. It employs object-oriented principles such as inheritance, polymorphism, and the Singleton design pattern to manage game systems, rendering, physics, and state transitions.

```
GameObjectAbstract (Pure Virtual Interface)
 └── GameObject (Base Class)
      ├── Enemy (Base Class)
      │    ├── EnemyShip (Nano-bots)
      │    ├── EnemyVirus (Green, Orange, Blue Viruses)
      │    ├── EnemyBoss (Level Bosses)
      │    ├── Blockage (Cholesterol Wall Obstacles)
      │    └── BloodCell (Large, Small, White Blood Cells)
      ├── Player (Player 1 & Player 2 Ships)
      ├── PowerUp (Health, Laser, Life, Rocket, Checkpoint Clock)
      ├── Weapon (Base Class)
      │    ├── WeaponEnLaser (Enemy Lasers & Projectiles)
      │    ├── WeaponPlLaser (Single / Multi-beam Lasers)
      │    ├── WeaponPlNinjaStar (Rotating Stars)
      │    ├── WeaponPlRocket (Steerable Charged Rockets)
      │    └── WeaponPlSaw (Close-range Shielded Saw)
      ├── Explosion (Standard & Splatter Explosions)
      ├── ScoreValueText (Floating Score Indicators)
      └── ScrollingBackground (Looping Blood Vessel Textures)
```
