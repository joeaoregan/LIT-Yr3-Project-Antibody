# High Scores

## Overview (`HighScores.h`, `HighScores.cpp`)

```text
┌-------------------------┐
|        HighScores       |
├-------------------------┤
| +gFont: TTF_Font*       | - Font used to render High Scores menu text
| +gScoresMenuText1       | - The Title for the High Scores menu
| +gScoresMenuText2       | - Button text
| +gReturnTomen           | - Button to return to the main menu
| +gScoresMenuButtons     | - Array of buttons
| +gSpriteClipsScores     | - The current frame of button animation
| +gButtonSpriteSheet2    | - Button animation sprite sheet
├-------------------------┤
| +loadHighScoresMedia()  | - Load high scores media for buttons, render text to textures
| +closeHighScoresMedia() | - Free the High Scores media from memory
| +handleHighScoresEv()   | - Handle events for each button
| +draw()                 | - Render the buttons and text textures
└-------------------------┘
```

Manages the High Scores leaderboard screen.

* **Data Storage**: Reads existing leaderboard entries from an external text file (`highscore.txt`) using file stream readers (`std::ifstream`, `getline()`).
* **Rendering**: Formats score entries and names into texture elements displayed within the menu UI table.
* **Navigation**: Provides return buttons to navigate back to the Main Menu.
