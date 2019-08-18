# Dodge-v2 (October 2015)

New version of old Dodge project with new enemies, powers and HUD. Developed in C++ and SFML. Rebuilt in August 2019 with SFML 2.5.1.

## Project Description

The goal is to collect points (stationary and moving) all while avoiding enemies (stationary, reflecting and chasing) in order to achieve a high score. Everytime the player collects a prize (teal or yellow orb), an enemy will spawn. There is also an enemy displayed as a crosshair, which follows the player around and kills him if stays for too long without moving.

![](dodge.gif)

The player has 5 abilities as its disposal:
* Slow enemies - slows the movement speed of enemies
* Freeze enemies - pauses the movement of the enemies
* Magnet prize - attracts the moving prizes to the player
* Player shrink - player size is reduced
* Player speed boost - player movement speed is increased

## Usage

* Enter to start and restart the game
* Player Moves with WASD or Arrow keys
* Player activates powers with keys J, K, L, U, I, for the 5 powers mentioned.
