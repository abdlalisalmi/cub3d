# cub3D
First-person 3D representation of a maze using raycasting, This project’s objectives are similar to all school 42 first year’s objectives: Rigor, use of C, use of basic algorithms, information research etc.
The goal of cub3d is to make something using raycasting like <a href="https://fr.wikipedia.org/wiki/Wolfenstein_3D">Wolfenstein 3D</a>.
<br>
<p align="center">
  <img src="https://github.com/abdlalisalmi/cub3d/blob/master/src/screenshot.png" width="85%">
</p>

## Prerequisites:
The project runs using the MiniLibX, a simplified version of the Xlib. It can therefore only run in MacOSX, preferably on a computer with a solid CPU !

## How to run it:
Using ``make run`` will make and run the game.
You can also use ``make`` to generate the ``cub3D`` executable. You can launch it with ``./cub3D map.cub``.
<br>
You can also just create a secreen shot with ``make save``, or ``./cub3D map.cub --save``.

## Controls:
- You can move around the maze with ``W`` ``A`` ``S`` ``D``.
- You can also rotate the view with the directional arrows ``←`` and ``→``.
- To exit the game, press ``ESC`` or click the red cross.
