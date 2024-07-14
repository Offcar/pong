# Design notes

## Gameloop
The players goal is to make the most ammount of points up until loosing all its lives.

The players will have **three lives**, each time the rival paddle makes a point, it will subctract one life from the player.
When the players looses a life, the ball resets in the center of the screen and waits for the player to press **ENTER**
, when pressed, the ball will be shot in a random direction, starting another round of Pong.

The player **cannot** control the rival paddle.

The player paddel must be contained within the playable area *(Either restrict window size or specific borders)*

## Player
A paddle that can only move upwards and downwards the screen, limited by the window resolution (?).

    ¿What should be the speed of the player paddle?
    idk, fast enough to catch up to the ball but not fast enought so that it wont be so forgiving

## Controls
- **While in the titlescreen**
    - **Enter** : Start game
- **While in game** 
    - **W / Up-arrow** : Move paddle upwards
    - **S / Down-arrow** : Move paddle downwards
    - **ESC** : Pause game

## Rival Paddle AI
The rival paddle AI should be good enough for it to make a fun and challenging game against the AI, but not good enough so that every round is 30 minutes long if the player is skilled.

    ¿Maybe the rival paddle AI could be tuned? 
    Maybe there could be a configurable difficulty or something

    ¿Simulate AI mistakes?
    There could be a randomized wrong direction chance, so that it gives the impression
    to the player that it has "tricked" the AI with a good shot.

    ¿Randomized speed values?
    So that the rival paddle wont always catch up to the ball, it has to be tuned enough
