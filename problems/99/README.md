 L. Джонсон — База 2024 2 сем. Задание 3\. Алгоритмы — Яндекс.КонтестВаше участие в соревновании завершено. Вы можете дорешивать задачи и отправлять решения вне соревнования



L. Джонсон
==========




| Ограничение времени | 1 секунда |
| --- | --- |
| Ограничение памяти | 16Mb |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |





Урбанист Варлам Ильинов каждый день катается на своем велосипеде по городу, оценивая качество велосипедных дорог, а также
 доступность его любимых кофеен. За годы своих трудов он смог составить подробную карту каждого района и выяснить за какое
 время он сможет добраться от одной кофейни до другой. Кроме того, если от одной кофейни до другой есть трамвайная линия, то
 он впадает в неистовый восторг и считает, что время на этом пути не тратится, а наоборот приобретается.
 

Теперь он хочет измерить удобность транспортной инфраструктуры. Чем меньше максимальное расстояние между кофейнями, тем более
 удобным считается город. При этом, если от одной кофейни нельзя добраться до другой ни по велосипедным дорожкам, ни с помощью
 трамвая, то такая (упорядоченная) пара игнорируется при подсчете удобности.
 


Необходимо найти пару кофеен, кратчайшее расстояние от одной из которых до другой максимально среди всех пар, между которыми
 есть какой\-либо путь.
 



Формат ввода
------------



В первой строке вводятся числа N и M (1 ≤ N ≤ 103, 1 ≤ M ≤ 5 ⋅ N) — количество кофеен и общее количество велосипедных дорожек и трамвайных путей. В следующих M строках задаются числа a, b, w, что означает наличие пути от кофейни a до кофейни b длины w ∈ \[\-100, 100] (но не наоборот!). Кофейни нумеруются с 0\. Кольцевых трамвайных линий в городе не предусмотрено.
 


Формат вывода
-------------



Выведите искомое максимальное конечное кратчайшее расстояние между кофейнями.


Пример
------




| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| ``` 5 8 0 3 3 2 1 -1 0 2 6 1 3 4 1 2 3 3 0 2 0 4 6 4 2 -4  ``` | ``` 12  ``` |

