# cub3D

[![saltmer's 42 cub3d Score](https://badge42.vercel.app/api/v2/cl1mc7bhg006309kzftm5w40f/project/2363506)](https://github.com/JaeSeoKim/badge42)

This project is inspired by the world-famous Wolfenstein 3D game, which
was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to
make a dynamic view inside a maze, in which you’ll have to find your way

Проект нацелен на создание «реалистичной» трехмерной графики. Создание внутренней части лабиринта с перспективой от первого лица с использованием принципов Ray-Casting.

Используется библиотека miniLibX.

В аргументах подается карта с информацией:

<ul>
  <li> Пути до изображений текстур стен,</li>
<li> Цвет пола и неба в формате RGB,</li>
<li> Карта, окруженная стенами (возможна любой формы):
  <ul>
    <li>1 - стена</li>
    <li>0 - пустое место</li>
    <li>N, S, W, E - расположение игрока и его направление угла обзора,</li>
    <li>Пробелы - не изображаемые участки на карте.</li>
  </ul>
  </li>
</ul>

Пример карты:
<img href="./map.">

Программа отображает изображение в окне и соблюдает следующие правила:

◦ Клавиши со стрелками влево и вправо на клавиатуре должны позволять смотреть влево и
направо в лабиринте.
◦ Клавиши W, A, S и D должны позволять перемещать точку зрения по лабиринту.
◦ Нажатие клавиши ESC должно закрывать окно и завершать работу программы.
◦ Нажатие на красный крестик на рамке окна должно закрывать окно и
выход из программы.

## Usage

```
make && ./cub3D maps/map_subject.cub
```

Полный subject на английском можно прочитать <a href="./en.subject.pdf">тут</a>.

