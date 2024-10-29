# Cube3D

A repository containing the cub3d project of 42 Malaga. The aim of this project is to read files with the .cub extension that contain data for representing a 2D map into a 3D projection. The project uses raycasting in order to make the projection.

This project has been developed for Linux, but it should also work with MacOs too.
You can find all of the project details inside the subject pdf. Also, you can use your own maps if you want, just make sure to stick to the requirements listed in the subject pdf.

If you are a fellow student at 42, DO NOT COPY ANYTHING FROM THIS REPOSITORY THAT 
YOU DO NOT UNDERSTAND, use it to learn instead.

## Dependencies

For this project to compile you will need a C compiler, Cmake and the Make command. Also, you will need to install the necessary dependencies for the MLX42 graphic libray to function according to your operating system (POSIX compliant system's are recommended). You can find said dependencies and how to install them here: (https://github.com/codam-coding-college/MLX42).


## Run Locally

Clone the project

```bash
  git clone https://github.com/MiguelAngel456/Cube3D.git
```
Install dependencies (MacOs)

```bash
  brew install glfw
  brew install cmake
```

Install dependencies (Debian distributions)
```bash
  sudo apt update
  sudo apt install build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev
```

Go to the project directory

```bash
  cd Cube3D
```

Compile the program
```bash
  make
```

Run the executable
```bash
  ./cub3D mapss/correctMaps/*Whatever map you want*
```

To delete the .o files and the executable
```bash
  make fclean
```
