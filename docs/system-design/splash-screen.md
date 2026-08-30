# Splash Screen

## Overview (`SplashScreen.h`, `SplashScreen.cpp`)

```text
┌----------------------------------------------┐
|                SplashScreen                  |
├----------------------------------------------┤
| +gFont: TTF_Font* = NULL                     | - Font used to render text
| +textColour: SDL_Color                       | - Colour used for text
| +gFinalScoreTextTexture: Texture             | - Final score displayed at end of level / end of game
| +gGameWinnerTextTexture: Texturer            | - Game winner displayed at end of game
| +gGameOverTextTexture: Texture               | - End of game, game over texture
| +gPressEnterSpriteSheetTexture: Texture      | - Press Enter to Continue sprite sheet
| +gObjectiveTextTexture: Texture              | - Objective for each level
| +gStoryA: Texture                            | - Story Text 1
| +gStoryB: Texture                            | - Story Text 2
| +gStoryC: Texture                            | - Story Text 3
| +levelObjective: std::string                 | - Objective for each level
| +storyPage1: std::string                     | - The story, can spread over 3 screens
| +storyPage2: std::string                     | - Text for story 2
| +storyPage3: std::string                     | - Text for story 3
| +gPressButtonToContinueSpriteClips: SDL_Rect | - Sprite frames for Press Button to Continue animation
├----------------------------------------------┤
| +initSplashScreens() : bool                  | - Load media for Splash Screens
| +closeSplashScreens() : void                 | - Free the media for Splash Screens from memory
| +displayGameTitleScreens() : bool            | - Display intro screens at start of game before menu
| +levelIntroScreens() : bool                  | - Level background with scrolling text for objective
| +infoScreenEnemies() : void                  | - Scroll text & image information about level enemies
| +infoScreenPowerUps() : void                 | - Render information for each levels Power Ups
| +infoScreenStory() : void                    | - Display each levels story, up to 3 pages
| +endOfGame() : void                          | - Display final score, game winner, game or level over message
| +scrollUpText() : void                       | - Scroll text up the screen, from start point to end point
| +pressButtonToContinue() : void              | - Press Any Key To Continue
| +chooseBackground() : std::string            | - Choose the level background image to display
| +scrollRandomBackground() : void             | - Random direction to scroll the background
| +scrollLogoHorizontal() : void               | - Scroll message Up or Down
| +scrollLogoVertical() : void                 | - Scroll message from left or right
└----------------------------------------------┘
```

Handles non-interactive narrative and transition screens.

* **Story & Intro Screens**: Displays introductory narrative text, level objectives, enemy dossiers, and power-up guides across up to 3 pages per stage.
* **Transitions**: Features randomized multi-directional background scrolling (up, down, left, right) between screen transitions.
* **Game Over**: Renders final scores, victor announcements, and the "Press Enter to Continue" prompt.
