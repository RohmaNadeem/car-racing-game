# Car Racing Game

A 2D car racing game built with C++ and SFML. The player controls a car, avoids incoming traffic and obstacles, and survives as long as possible. Developed to deepen understanding of game loops, collision detection, and real‑time input handling.

## Features

🏎️ **Smooth Controls** – arrow keys or WASD for acceleration, braking, and steering.  
🚗 **Dynamic Obstacles** – randomly generated enemy cars and roadblocks.  
💥 **Collision Detection** – real‑time AABB collision with game‑over state.  
⏱️ **Score Tracking** – score increases based on distance or survival time.  
🎮 **Optimized Game Loop** – delta time ensures consistent speed across different frame rates.

## Technologies Used

- C++ (C++11/14/17) – core logic, object‑oriented design.
- SFML 2.6 – graphics, window management, input handling.
- Visual Studio 2022 – development environment.

## How to Run

Clone the repository:
```bash
git clone https://github.com/RohmaNadeem/car-racing-game.git
Open the solution file (.sln) in Visual Studio.

Make sure SFML is linked (see official tutorial).

Build and run: F5

Note: The .exe and .dll files are excluded via .gitignore. You must build the project locally.

Controls
Key	Action
Up Arrow / W	Accelerate
Down Arrow / S	Brake / Reverse
Left Arrow / A	Steer left
Right Arrow / D	Steer right
Project Structure
text
car-racing-game/
├── main.cpp                 # Entry point, game loop
├── Car.h / Car.cpp          # Player car logic
├── Obstacle.h / Obstacle.cpp # Enemy cars and obstacles
├── Game.h / Game.cpp        # Game state, collision, scoring
├── sfml/                    # SFML headers and libraries (not tracked)
├── .gitignore               # Excludes build files and DLLs
├── README.md
└── car-racing-game.sln      # Visual Studio solution
What I Learned
Implementing real‑time collision detection (AABB).

Managing game state (playing, game over, restart).

Using SFML for graphics, input, and window events.

Structuring a C++ project with object‑oriented design.

Debugging performance issues in a game loop.

Future Enhancements
Add sound effects and background music.

Implement different difficulty levels.

Add a high‑score system using file I/O.

Create a menu screen with options.
<img width="801" height="641" alt="image" src="https://github.com/user-attachments/assets/9b8c268e-793c-418d-9a4e-315bdc4e43cc" />
<img width="802" height="636" alt="image" src="https://github.com/user-attachments/assets/80ff6d8d-0809-4820-92aa-dad0c9f9377c" />
<img width="804" height="629" alt="image" src="https://github.com/user-attachments/assets/ea63b556-bc9b-4c1f-9ca0-fbb7f9d4ab76" />
<img width="799" height="639" alt="image" src="https://github.com/user-attachments/assets/c1ac6332-8a76-451e-961d-3e4a2b3ba8a0" />
<img width="802" height="634" alt="image" src="https://github.com/user-attachments/assets/ccaa5a0c-f5ff-496a-b266-338d5f44cb1c" />



Author
Rohma Nadeem – AI Engineering student

Connect with Me
https://www.linkedin.com/in/rohma-nadeem-25b041382/

