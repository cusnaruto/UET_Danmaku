<a name="readme-top"></a>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">How to play</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]](https://example.com)

This is a bullet hell game, heavily inspired by Touhou Project made by Team Shanghai Alice.

This is made for my class's big project, INT2215.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Make with

* [![C++][C++]]
* [![SDL2][SDL2]]


<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites

To complie and run the project, you need [Mingw](https://sourceforge.net/projects/mingw/)_ installed.

Please follow [this instruction](https://www.geeksforgeeks.org/installing-mingw-tools-for-c-c-and-changing-environment-variable/)_to install it.
### Installation

1.Clone the repo.

2.Go to the path that you clone the repo and extract it.

3.Go to `UET_Danmaku`.

4. Open CMD by clicking on the address bar in WindowsExplorer, type `cmd` then `enter`.

5. Paste the line of code below.

`g++ -o Danmaku main.cpp Game.cpp TextureManager.cpp GameObject.cpp Vector2D.cpp Collision.cpp ECS.cpp AssetManager.cpp EnemyComponent.cpp MainMenu.cpp -I src\include -L src\lib -w  -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer`

6. Run `Danmaku.exe`.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## How to play

Arrow keys for movement, `z` key for shooting.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

- [x] WIP

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Le Cong Hoang @ UET - 22026555@vnu.edu.vn

Project Link: [https://github.com/cusnaruto/UET_Danmaku](https://github.com/cusnaruto/UET_Danmaku)

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Here's the things I used while making the game.

* [Game Sprite Sheets](https://www.spriters-resource.com/)
* [Let's Make Games's SDL2 Tutorial](https://www.youtube.com/@CarlBirch)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->

[C++-url]: https://cplusplus.com/
[C++]:https://img.shields.io/badge/C++-20232A?style=for-the-badge&logo=c++&logoColor=61DAFB
[SDL2]:https://img.shields.io/badge/SDL2-20232A?style=for-the-badge&logo=SDL2&logoColor=61DAFB
[SDL2-url]:https://www.libsdl.org/
