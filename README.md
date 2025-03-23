# AsteroidHunter - Unreal Engine 5

## About the project
### Core Idea
The following project is a game inspired by _Asteroids_ and _Space Invaders_ with few custom gameplay features. Playeres must carefully dodge the asteroids by carefully moving the ship and destroy them to gain points. Each weapon should be used thoughtfully as they can quickly overheat, if fired rapidly. The main goal of the game is to survive as long as possible and reach high score that can unlock two special abilities.

### Gameplay


## Game Features

### Movement
Game features horizontal movement with A and D keys. Based on the direction the ship is smoothly rotated and translated using the linear interpolation nodes to sell the feeling of moving through space.

### Hit Reactions
When the ship is hit, a direction to the asteroid is used to move and rotate the ship to give the feelling of impact and getting serious damage.

### Weapons
The game allows players to choose between two weapons to gain advantage in the asteroid hunting:
* **Rifle** - 
* **Shotgun** -

### Overheating mechanic
Each shot charges the overheat meter. Eeach weapon overheats differently and can be fired at differenct overheat levels. Once players stop firing each weapon, it gradually cools down, which is shown on the UI in the bottom-right corner of the sceen. Also the is 25% chance that a destroyed asteroid drops a blue gun cooler, the slighly reduces gun heat.

### Special Perks
If players peform well during gameplay, they can get access to two special abilities, both unlocked once a specific score threshold is surpassed. When uses, players have to increase score furhter to unlock them again.
Those abilities are:
* **Shield (costs 25 points)** - gives player full protection from asteroids for four hits, then disables itself. By changeing its color on each hit, gives players a visual cues how much integrity it has left.
* **Ultra Bolt (costs 45 points)** - special rifle bolt that penetrates through every asteroid on its way, droping mines on impact. Mines expolode once asteroids trigger them, awarding players with additional 2 points.

### Health System?

### Destructible astroids
When asteroid is destroyed, apart from increasing players score, it satisfyingly explodes into dozens of pieces. This feature was implemented with Unreal Engine's Chaos Destruction system that allows to fracture a static mesh and apply a strain during gameplay via Fields System. Here, the destruction pattern chosen was Cluster Fracutre and the destruction itself is handled by a custom field system.

### Pick-ups
The aid players during gameplay the game features few different items that can be picked up:
* **Gun Cooler** - 
* **Health Orb** - 

## Tools
Project was created in Unreal Engine 5.3.2 with addition of
* C++
* Blueprints
* Chaos Physics
* Events and Delegates

## Usage
### How to run it
Project can be run either directly from UE, after clonning the repository and building the binaries project can by run in Unreal Engine 5.3.2, or by downloading the latest build from the Releases section.
### How to play it
* A and D keys to move left and right
* Space to shoot
* Tab to switch weapons
* Q to enable shield
* E to use Ultra Bolt

## Idea Origin

