 X. Треугольная карта Винду — База 2024 2 сем. Задание 2\. Алгоритмы — Яндекс.Контест



X. Треугольная карта Винду
==========================




|  | Все языки | Java 21 (Temurin JDK) |
| --- | --- | --- |
| Ограничение времени | 60 секунд | 10 секунд |
| Ограничение памяти | 512Mb | 512Mb |
| Ввод | стандартный ввод или input.txt | |
| Вывод | стандартный вывод или output.txt | |





В одной небезызвестной вселенной есть N планет, пронумерованных для вашего удобства от 1 до N. Если три планеты соединены гипертоннелями друг с другом (все гипертоннелями двусторонние), то они образуют транспортный
 союз, чья эффективность определяется суммой номеров планет, входящих в него.
 

У известного астронома Винду есть карта, на которой для каждого транспортного союза обозначена его сила. К сожалению, фиолетовый
 меч оставляет лишь временные следы, поэтому часть карты утрачена, более того остались только эффективности транспортных союзов,
 тогда как номера планет бесследно утеряны.
 


Вы, как падаван магистра Винду, вызвались восстановить с помощью оставшихся данных исходные номера планет. Также вам известно,
 что в этой вселенной есть хотя бы три крупных планеты, соединенных со всеми остальными планетами.
 


Для удобства решения задачи, планеты как\-то случайно пронумерованы от 1 до N, так что формально вам надо восстановить перестановку планет (или массив p\[] такой, что если во входных данных планета имела номер i, то ее истинный номер будет p\[i]).
 


Учтите, что так как магистр Винду уже не молодой, в его карте тоже могли быть ошибки, поэтому решения задачи вообще может
 не существовать.
 



Формат ввода
------------



В первой строке даны два натуральных числа N и T (4 ≤ N ≤ 105, 3N \- 8 ≤ T ≤ 106) — количество планет и транспортных союзов.
 

Далее идет T строк в формате «i j k s» (1 ≤ i \< j \< k ≤ N, 6 ≤ s ≤ 3N \- 3\) — описания союзов, где i, j, k — номера планет, а s — эффективность транспортного союза.
 



Формат вывода
-------------



Если ответ на задачу существует, то выведите Possible и на следующей строке перестановку (любую, если таких несколько). Иначе выведите Impossible.
 


### Пример 1




| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| ``` 4 4 1 2 4 6 2 3 4 7 1 2 3 8 1 3 4 9  ``` | ``` Possible 3 1 4 2   ``` |


### Пример 2




| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| ``` 5 10 2 4 5 9 1 3 4 6 1 2 5 12 1 2 4 10 3 4 5 6 2 3 4 8 2 3 5 10 1 3 5 9 1 2 3 11 1 4 5 8  ``` | ``` Impossible  ``` |

