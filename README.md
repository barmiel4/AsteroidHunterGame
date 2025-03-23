# Asteroid Hunter - Unreal Engine 5

## Idea Origin
The project is a severe upgrade of the tutorial from the book. Later I used it during the Game Developement workshops in 2020 that I hosted in my High School, to teach students the basics of game developement.  

Number of mechanics were added, such as:
* Smoother player's ship movement
* Directional hit reactions
* Astroid destuction
* Second weapon
* Overheat system
* Shield and Ultra Bolt perks
* Weapon cooling system

## About the project

### Core Idea
The following project is a game inspired by _Asteroids_ and _Space Invaders_ with few custom gameplay features. During gameplay, players must dodge the asteroids by carefully moving the ship and shooting them to gain points. Each weapon should be used thoughtfully as they can quickly overheat, if fired rapidly. The main goal of the game is to survive as long as possible and reach high scores that can unlock special abilities.

### Gameplay
<p align="center">
  <img src="https://github.com/user-attachments/assets/10a67392-0c61-4a2f-a1fd-2aacb016fb45" width="800">
</p>

## Game Features

### Movement
Game features horizontal movement with A and D keys. Based on the movement direction, the ship is smoothly rotated and translated using the linear interpolation nodes to sell the feeling of moving through space.

### Hit Reactions
When the ship is hit, a direction vector to the asteroid is used to move and rotate it, giving the feel of impact and indicate serious damage.

### Weapons
The game allows players to choose between two weapons to gain advantage in the asteroid hunting:
* **Rifle** - overheats slowly and fires a single bolt that is capable of taking out one asteroid
* **Shotgun** - has higher overheating rate, but covers much wider space with a 5-bullet spread
Each weapon bolt is destroyed upon impact.

### Overheating mechanic
Each shot charges the overheat meter. Each weapon overheats differently and can be fired at different heat levels. Once player stops firing, each weapon gradually cools down, shown through the UI in the bottom-right corner of the sceen. Also there is a 25% chance that a destroyed asteroid drops a blue gun cooler that slighly reduces gun heat level.

### Special Perks
If players peform well during combat, they can get access to two special abilities, both unlocked once a specific score threshold is surpassed. Once used, players have to increase score furhter to unlock them again.
Those abilities are:
* **Shield (costs 25 points)** - gives player full protection from asteroids for four hits, then disables itself. By changing its color on each hit, it gives players a visual cues of how much integrity it has left.
* **Ultra Bolt (costs 45 points)** - special rifle bolt that penetrates through every asteroid on its way, droping mines on impact. Mines expolode once an asteroids triggers them, awarding players with additional 2 points.

### Destructible asteroids
When asteroid is destroyed, apart from incrementing player's score, it satisfyingly explodes into dozens of pieces. This feature was implemented with Unreal Engine's Chaos Destruction system that allows to fracture a static mesh and apply a strain during gameplay via Fields System. Here, the destruction pattern chosen was Cluster Fracutre and the destruction itself is handled by a custom field system.

### Pick-ups
The aid players during gameplay the game features few different items that can be picked up:
* **Gun Cooler** - randomly dropped by a destroyed asteroid. It flies to the player, and cools the random gun when picked up
* **Health Orb** - restores 10% of the player’s health when flown through. Has a random chance to be spawned instead of an asteroid

## Tools
Project was intialy created in Unreal Engine 4 and recently ported to Unreal Engine 5.3.2 with each mechanic reimplemented in C++. 
Other tools include:
* Blueprints
* Chaos Physics
* Events and Delegates

## Usage
### How to run it
Project can be run either directly from UE 5.3.2, after cloning the repository and building the binaries, or from the latest build that can be downloaded from the Releases section.

### How to play it
* **A and D** keys to move left and right
* **Space** to shoot
* **Tab** to switch weapons
* **Q** to enable shield
* **E** to use Ultra Bolt
* **ESC** to quit
