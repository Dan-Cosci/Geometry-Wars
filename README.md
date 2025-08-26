# ECS Game Project

This project is a simple 2D game built using **C++** and **SFML**, following a game development course by **Dave Churchill**.
The goal of the project is to learn and implement an **Entity-Component-System (ECS)** architecture, while practicing modern C++ game programming techniques.

---

## ✨ Features

- **Entity-Component-System (ECS)** architecture for flexible game object management
- **Player-controlled entity** with movement and shooting
- **Shape rendering** using SFML (circles, squares, polygons)
- **Lifespan system** where entities fade out and get destroyed after some time
- **Input system** for both keyboard (WASD) and mouse interactions
- **Random spawning** of entities
- **Collision detection & physics basics** (WIP depending on course progress)

---

## 🛠️ Technologies Used

- **C++17/20**
- **SFML 2.6.2** for graphics, input, and window handling
- **ECS design pattern** for structuring game logic
- Modern C++ memory management (`std::shared_ptr`, `std::unique_ptr`)

---

## 📖 Course Reference

This project follows along with the **Game Development Course** by [Dave Churchill](https://davechurchill.github.io/) (Computer Science professor at Memorial University of Newfoundland).
The course provides a structured approach to building a game engine from scratch using C++ and SFML.

---

## 🚀 Getting Started

### Prerequisites

- **C++ compiler** (GCC, Clang, or MSVC)
- **CMake** or Make (depending on your setup)
- **SFML 2.6.2** (installed and linked correctly)

### Build Instructions

Clone the repo:

```bash
git clone https://github.com/your-username/ecs-game.git
cd ecs-game
```

Compile (example with g++):

```bash
g++ -std=c++17 -I headers src/*.cpp -o build/game -lsfml-graphics -lsfml-window -lsfml-system
```

Run:

```bash
./build/game
```

---

## 🎮 Controls

- **W / A / S / D** → Move player
- **Mouse Left Click** → Shoot projectiles
- **Mouse Right Click** → Shoot special projectiles
- **ESC** → Quit game

---

## 📂 Project Structure

```
ecs-game/
│── src/            # Source files
    │── headers/    # Header files
│── build/          # Compiled output
│── README.md       # Project documentation
```

---

## 📌 Notes

- This is a **learning project**, not a finished game.
- The code evolves as new concepts are introduced in the course (ECS systems, collisions, spawning, etc.).
- Future extensions may include scoring, enemies, and UI.

---

## 🙏 Acknowledgments

- **Dave Churchill** for his excellent teaching and game dev course
- **SFML** community for the graphics library
- Fellow learners following the same course
