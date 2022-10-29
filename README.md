# 42-so_long

![so_longm](https://user-images.githubusercontent.com/81260589/198842273-22a3ce7f-1287-4110-b646-c6741d5b0bf3.png)

## Table of contents

- [Introduction](#Introduction)
- [How to run](#How-to-run)
- [How it works](#How-it-works)
- [How to play](#How-to-play)
- [What I have learned](#What-I-have-learned)

## Introduction
This is my fourth project as a student at school 42 São Paulo. 
The goal of this project was develop skills in computer graphics, such as: window management,
handling events, colors, textures and so on.

## How to run?

### __This project only runs on Linux!__

### Dependencies
MiniLibX requires `xorg`, `x11` and `zlib`, so you will need to install the following dependencies:

````
sudo apt update && sudo apt install -y xorg libxext-dev zlib1g-dev libbsd-dev
````

If you're on WSL, you must have installed <a src="https://sourceforge.net/projects/xming/">Xming</a>. <br>
Start Xming Launch with `Multiple windows`, `Start no client` and `No Access Control` options.

Finally, in your WSL execute the following command:

on WSL2:
````
echo "export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0.0" >> ~/.bashrc && source ~/.bashrc
````
on WSL1:
````
echo "export DISPLAY=localhost:0.0" >> ~/.bashrc && source ~/.bashrc
````

### Cloning

- Clone the repository:
````
git clone --recurse-submodules git@github.com:victor-ln/42-so_long.git
````
- Access the cloned folder:
````
cd 42-so_long
````
- Run the Makefile:
````
make
````
- To clean objects files execute:
````
make clean
````
- To clean `so_long` file:
````
make fclean
````
- Recompile:
````
make re
````

## How it works?

To run the game, you must pass as first argument a map description file with the .ber extension.

### __Map configuration__

The map construction is composed by the following characters:

- `'1'` for walls
- `'0'` for empty spaces
- `'C'` for a collectible,
- `'E'` for a map exit,
- `'P'` for the player’s starting position.

- The map must contain at least 1 exit, 1 collectible, and 1 starting position, be rectangular and closed/surrounded by walls

Map example:

````
1111111111111111111111111111111111
1E0000000000000C00000C000000000001
1010010100100000101001000000010101
1010010010101010001001000000010101
1P0000000C00C0000000000000000000C1
1111111111111111111111111111111111
````

## How to play?

The player’s goal is to collect every collectible present on the map, then escape
chosing the shortest possible route.

- The `'W'`, `'A'`, `'S'`, and `'D'` keys allow you to move the player up, left, down and right, respectively.
- `'Esc'` key exits the game.

## What I have learned

- Computer graphics
- Level up in C programming
- Game events management
