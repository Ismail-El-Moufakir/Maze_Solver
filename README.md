# Maze Solver with Q-Learning
This project is part of the IN104 course at ENSTA. It demonstrates the application of the Q-learning algorithm to solve mazes. The maze solver uses a reinforcement learning approach where the agent learns to navigate through the maze by avoiding walls and finding the shortest path to the goal.

### How It Works
The maze solver initializes a grid-based environment from a text file (maze.txt). The Q-learning algorithm is then applied where the agent learns to navigate through the maze by:
Exploring the environment using ε-greedy policy.
Learning from the rewards (or penalties) it receives for hitting walls, moving towards, or reaching the goal.
The agent's movement is rendered on the console, showing its path through the maze with a delay between steps for visibility.
