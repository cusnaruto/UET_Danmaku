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
    <li><a href="#How to play">How to play</a></li>
    <li><a href="#Roadmap">Roadmap</a></li>
    <li><a href="#Gameplay">Gameplay</a></li>
    <li><a href="#Screenshot">Screenshots</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->

## About The Project

This is a bullet hell game, heavily inspired by the [Touhou Project series](https://en.wikipedia.org/wiki/Touhou_Project) made by [Team Shanghai Alice](https://en.wikipedia.org/wiki/Team_Shanghai_Alice).

This is made for my class's big project, INT2215.

![reimu-fumo](https://user-images.githubusercontent.com/119999945/236684505-7d706d5d-e074-46ac-9ff6-6af26d822513.gif)


<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Make with

* [![C++][C++]]
* [![SDL2][SDL2]]

I used VS Code as my code editor, Photoshop and Audacity to edit the assets.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

This is an example of how to set up the project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites

*This is on Windows 10.

To complie and run the project, you need [Mingw](https://sourceforge.net/projects/mingw/) installed.

Please follow [this instruction](https://www.geeksforgeeks.org/installing-mingw-tools-for-c-c-and-changing-environment-variable/) to install it.
### Installation

1.Clone the repo.

2.Go to the path that you clone the repo and extract it.

3.Go to `UET_Danmaku`.

4.Open CMD by clicking on the address bar in WindowsExplorer, type `cmd` then `enter`.

5.Paste the line of code below and run it.

`g++ -o Danmaku main.cpp Game.cpp TextureManager.cpp GameObject.cpp Vector2D.cpp Collision.cpp ECS.cpp AssetManager.cpp EnemyComponent.cpp MainMenu.cpp GameOver.cpp YouWin.cpp -I src\include -L src\lib -w  -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer`

6.Run `Danmaku.exe`.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## How to play

Arrow keys for movement, `z` key for shooting.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

- [x] Have graphics
- [x] Have musics
- [x] Have SFXs
- [x] The player character has animation
- [x] Running the game takes only ~30 mb of ram, no memory leak
- [x] Enemies can aim the bullets at the player
- [x] Bosses have their own bullet pattern
- [x] Have a lose / win screen
- [x] Mostly bugless

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- Gameplay -->
## Gameplay

- There will be 55 enemies, consist of 50 normal mobs and 5 bosses. 
- Every 10 enemies killed, a boss will spawn and have an unique bullet pattern.
- Enemies after killing the bosses will be shooting faster, and have more health points.
- Kill all enemies to win.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- Screenshot -->
## Screenshot

![Screenshot_3](https://user-images.githubusercontent.com/119999945/236684763-c3577a6f-ed66-4488-bfd7-ba01dcdb8670.png)
![Screenshot_6](https://user-images.githubusercontent.com/119999945/236684778-7ce8f670-7a7d-474d-bf43-858ebc9f8bea.png)
![Screenshot_7](https://user-images.githubusercontent.com/119999945/236684793-a22ad1ca-e312-4247-95a8-31b2ec6665fb.png)
![Screenshot_8](https://user-images.githubusercontent.com/119999945/236684804-50894ade-9eb5-4b02-a39f-567a829b0eb6.png)
![Screenshot_5](https://user-images.githubusercontent.com/119999945/236684821-b6ceda45-c9fa-4b4b-aa9c-e67af913fad0.png)


<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Le Cong Hoang @ UET - 22026555@vnu.edu.vn

Project Link: [UET_Danmaku](https://github.com/cusnaruto/UET_Danmaku)

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Here's the things I used while making the game.

* [Game Sprite Sheets](https://www.spriters-resource.com/)
* [Let's Make Games's SDL2 Tutorial](https://www.youtube.com/@CarlBirch)
* [Main Menu BGM](https://www.youtube.com/watch?v=ihhvufZWDkU)
* [Stage BGM](https://www.youtube.com/watch?v=M9wHYiicY5I)
* [Vine boom sound effect](https://www.youtube.com/watch?v=Oc7Cin_87H4)
* [Bruh sound effect](https://www.youtube.com/watch?v=2ZIpFytCSVc)
* [Lazy Foo Productions](https://lazyfoo.net/tutorials/SDL/index.php)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->

[C++-url]: https://cplusplus.com/
[C++]:https://img.shields.io/badge/C++-20232A?style=for-the-badge&logo=c++&logoColor=61DAFB
[SDL2]:https://img.shields.io/badge/SDL2-20232A?style=for-the-badge&logo=SDL2&logoColor=61DAFB
[SDL2-url]:https://www.libsdl.org/
