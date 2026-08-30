<link href="styles.css" rel="stylesheet"></link>

# Antibody

![C++](https://img.shields.io/badge/C%2B%2B-14-00599C?logo=cplusplus&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D4?logo=windows&logoColor=white)
![IDE](https://img.shields.io/badge/Visual%20Studio-2015-5C2D91?logo=visualstudio&logoColor=white)
![Game Engine](https://img.shields.io/badge/Type-Custom%20Engine-orange?logo=game-developer&logoColor=white)
![Genre](https://img.shields.io/badge/Genre-Action%20%2F%20Shooter-red)

![SDL2](https://img.shields.io/badge/SDL2-2.0.5-5C2D91?logo=sdl&logoColor=white)
![SDL_image](https://img.shields.io/badge/SDL__image-Supported-blue)
![SDL_mixer](https://img.shields.io/badge/SDL__mixer-Supported-blue)
![SDL_ttf](https://img.shields.io/badge/SDL__ttf-Supported-blue)
![zlib](https://img.shields.io/badge/zlib-1.2.x-78c34c)

![Input](https://img.shields.io/badge/Input-Gamepad%20%26%20Keyboard-success)
![Audio](https://img.shields.io/badge/Audio-SDL__mixer-blueviolet)
![Graphics](https://img.shields.io/badge/Graphics-2D%20Particles-ff69b4)

![GitHub repo size](https://img.shields.io/github/repo-size/joeaoregan/LIT-Yr3-Project-Antibody?color=orange)
![GitHub last commit](https://img.shields.io/github/last-commit/joeaoregan/LIT-Yr3-Project-Antibody?color=blue)
![Stars](https://img.shields.io/github/stars/joeaoregan/LIT-Yr3-Project-Antibody?style=social)

---

## Limerick Institute of Technology: BSc Computing (Games Design and Development)

### Year 3 (2016/17), Semesters 5 and 6

#### Third-Year Group Project

Created by [Joe O'Regan (K00203642)](https://github.com/joeaoregan) and [Sean Horgan (K00196030)](https://github.com/sean-horgan)

---

# 🦠💉 Antibody

<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-Project-Antibody/master/Screenshots/Antibody1Logo.jpg" width=250 alt="Antibody Game Logo" title="Antibody Game Logo"/> \
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-Project-Antibody/master/Screenshots/Antibody2Credits.jpg" width=250 alt="Antibody Game Creators" title="Antibody Game Creators"/>

---

## 📖 About

Antibody is a 2D sidescrolling game create using C++ and the Simple DirectMedia Layer (SDL 2) cross-platform software development library.

> [!TIP]
> To set up an SDL project starting from scratch, the information needed for a number of platforms and IDE is available in the [Lazy Foo' SDL tutorials](http://lazyfoo.net/tutorials/SDL/)

---

## 🎮 Features
### Core Systems

- **State Management**: Uses a state-based architecture (e.g., StatePlay, SplashScreen, EnterName) for clean transitions between menus and gameplay.
- **Physics & Collisions**: Custom collision detection (CollisionStuff.h) handling interactions between players, enemies, and environmental hazards.
- **Input Handling**: Support for both Keyboard and Gamepads (Gamepad.h).
- **Frame Rate Control**: Integrated FPS management (FPS.h and Timer.h) to ensure consistent gameplay speed.

### Gameplay Mechanics
- **Entity Inheritance**: A robust OOP structure with GameObjectAbstract serving as the base for Player, Enemy, and PowerUp.
- **Diverse Arsenal**: Multiple weapon types including Lasers, Rockets, Saws, and Ninja Stars.
- **Enemy Variety**: Specialized AI types including EnemyShip, EnemyVirus, and environmental Blockage.
- **Scoring & Persistence**: High score entry system (EnterName.h) and dynamic score text rendering.

### Visuals & Audio
- **Particle System**: Dedicated system for effects like explosions and blood cell interactions (Particle.cpp).
- **Scrolling Backgrounds**: Support for parallax or continuous background movement.
- **Dynamic HUD**: Real-time health bars (StatusBar.h) and heads-up display info.
- **Full Audio Suite**: Integration with SDL_mixer for music and sound effects management.

---

## 🛠️ Versions

1. **Journey To The Center Of My Headache**: Original Game Title.
2. **Games Fleadh Entry Version**: Games Fleadh award winning entry from 8th of March, 2017.
3. **Third-Year Project Submission**: An improved version of Games Fleadh entry.
4. **CodeBlocks**: This is an adapted version of the third-year project submission version of Antibody 2D, so the project can be compiled in Code::Blocks, and run without the need for Visual Studio DLLs.

> [!NOTE]
> "Files Commont To V2 and V3/" contains files commong to the Games Fleadh entery and Project Submission.

---

## 🚀 Releases

Playable versions of game, bare in mind, the game is incomplete

[Release Page](https://github.com/joeaoregan/LIT-Yr3-Project-Antibody/releases)

---

## 🏆 Awards

<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-Project-Antibody/master/Screenshots/BestWindowsGame.jpg" width=250 alt="Antibody 2D: Best Windows Game" title="Antibody 2D: Best Windows Game"/>

**Best Windows Game** at [Games Fleadh 2017](http://gamesfleadh.ie/results/)

---

## 📸 Screenshots (Updated 31/01/2018)

<details closed>
<summary>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-Project-Antibody/master/Screenshots/Antibody3Multiplayer.jpg" title="Antibody 2D: Multiplayer" width="150"/> 
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-Project-Antibody/master/Screenshots/Antibody6Map.jpg" title="Antibody: Map" width="150"/> 
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-Project-Antibody/master/Screenshots/Antibody7InfoMessages.jpg" title="Antibody 2D: Information Messages" width="150"/> 
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-Project-Antibody/master/Screenshots/Antibody8Boss.jpg" title="Antibody 2D: Power Ups" width="150"/> 
<p>Click here for larger images, or individual thumbnails to go to raw images.</p>
</summary>

![Antibody 2D: Multiplayer](https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-Project-Antibody/master/Screenshots/Antibody3Multiplayer.jpg "Antibody 2D: Multiplayer")

###### Antibody 2D: 2 Player Local Multiplayer

---

![Antibody 2D: Menu](https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-Project-Antibody/master/Screenshots/Antibody4Menu.jpg "Antibody 2D: Menu")

###### Antibody 2D: Menu System

---

![Antibody 2D: Settings Menu](https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-Project-Antibody/master/Screenshots/Antibody5Settings.jpg "Antibody 2D: Settings Menu")

###### Antibody 2D: Settings Menu

---

![Antibody 2D: Map](https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-Project-Antibody/master/Screenshots/Antibody6Map.jpg "Antibody: Map")

###### Antibody 2D: Map

---

![Antibody 2D: Information Messages](https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-Project-Antibody/master/Screenshots/Antibody7InfoMessages.jpg "Antibody 2D: Information Messages")

###### Antibody 2D: Virus Enemies, Information Messages, and Power Ups

---

![Antibody 2D: End Of Level Boss](https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-Project-Antibody/master/Screenshots/Antibody8Boss.jpg "Antibody 2D: End Of Level Boss")

###### Antibody 2D: End Of Level Boss

---

![Antibody 2D: Power Ups](https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-Project-Antibody/master/Screenshots/Antibody9PowerUps.jpg "Antibody 2D: Power Ups")

###### Antibody 2D: Power Ups for time, health, lasers, lives, rockets

---

![Split Screen Race Mode](https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-Project-Antibody/master/Split-Screen%20Race%20Mode/Art/racing.png "Split Screen Race Mode")

###### Split screen race mode

</details>

---

<details>
  <summary>1. 🔗 Links</summary>

### Additional Repos:

#### 1. Year-Four Networked Games Project

As part of my forth-year project, I started creating a networked version of the game in Linux. The code base is cross platform, and I've included a finite state machine to help eliminate some of the problems with the original game.

[Yr4-Project-Networked-Games-Library Repo](https://github.com/joeaoregan/Yr4-Project-Networked-Games-Library)

#### 2. AntibodyPy

A Python based version of the game

[AntibodyPy Repo](https://github.com/joeaoregan/AntibodyPy)

---

</details>

<details>
  <summary>2. 🎵 Media</summary>

Game Trailer by Seán Horgan, and Original Game Tracks by Joe O'Regan

<table>
<tr>
    <th>Game Trailer</th><th colspan=2>Soundtrack</th>
</tr>
<tr>
    <td><a href="https://youtu.be/HQiAlmhXLqA"><img src="https://i.ytimg.com/vi/HQiAlmhXLqA/1.jpg" title="Game Trailer"/><br/>YouTube Trailer</a></td>
    <td><a href="https://youtu.be/ibIjSwFLAGo"><img src="https://i.ytimg.com/vi/ibIjSwFLAGo/1.jpg" title="Game Trailer"/><br />1. Blood Level</a></td>
    <td><a href="https://youtu.be/sHVVEVyt4xQ"><img src="https://i.ytimg.com/vi/sHVVEVyt4xQ/1.jpg" title="Game Trailer"/><br />2. Virus</a></td>
</tr>
<tr>
    <td>by Seán Horgan</td>
    <td colspan=2>by Joe O'Regan</td>
</tr>
</table>

---

</details>

<details>
  <summary>3. 📚 References</summary>

### References:

[Lazy Foo' Productions: Beginning Game Programming v2.0](http://lazyfoo.net/tutorials/SDL/)

[SDL Game Development by Shaun Mitchell](https://www.packtpub.com/game-development/sdl-game-development)

</details>

---

<div align="center">

[![GitHub](https://img.shields.io/badge/GitHub-181717?style=flat&logo=github&logoColor=white)](https://github.com/joeaoregan)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-0A66C2?style=flat&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/joeaoregan/)
[![Email](https://img.shields.io/badge/Email-D14836?style=flat&logo=gmail&logoColor=white)](mailto:joeaoregan@yahoo.ie)

&copy; 2017 Joe O'Regan &bull; LIT | Group Project

[⬆️ Back to Top](https://github.com/joeaoregan/LIT-Yr3-Project-Antibody)

</div>
