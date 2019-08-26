# Bomberman
3D adaption of the classic bomberman game
https://www.retrogames.cz/play_085-NES.php?emulator=js

This is currenly a POC branch for using conan.

### Pre-Install
This requires the c++ package manager conan. These are the install instructions I found the most convient. If you you like please visit https://conan.io/ for more information.

#### Linux

```pip install conan```

#### OSX

```brew install conan```

#### Add remote repo
This will add the repo where sfml lives.

```conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan```

### Install

```make```

### Running the Game

```make run```

## Dependancies
* CMake
* pkg-config
* SFML
* GLEW
* GLM
* ASSIMP

### MacOS dependancy installation
    brew install cmake
    brew install pkg-config
    brew install sfml
    brew install glew
    brew install glm
    brew install assimp

### Linux dependancy installation
    sudo apt-get install cmake
    sudo apt-get install pkg-config
    sudo apt-get libsfml-dev
    sudo apt-get libglew-dev
    sudo apt-get libglm-dev
    sudo apt-get libassimp-dev
