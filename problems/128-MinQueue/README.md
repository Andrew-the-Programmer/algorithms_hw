 D. MinQueue — База 2023 1 сем. Задание 2\. C\+\+ — Яндекс.КонтестВаше участие в соревновании завершено. Вы можете дорешивать задачи и отправлять решения вне соревнования



D. MinQueue
===========




| Ограничение времени | 1 секунда |
| --- | --- |
| Ограничение памяти | 64Mb |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |





Реализуйте тип данных «очередь c поддержкой минимума», который поддерживает следующие операции: 
 * «enqueue n» Добавить в хвост очереди число n (1 ≤ n ≤ 109) (значение n задается после команды). Программа должна вывести «ok».
* «dequeue» Удалить из очереди головной элемент. Программа должна вывести его значение.
* «front» Программа должна вывести значение головного элемента, не удаляя его из очереди.
* «size» Программа должна вывести количество элементов в очереди.
* «clear» Программа должна очистить очередь и вывести «ok».
* «min» Программа должна вывести минимум в очереди, не удаляя его из очереди.




Если во входных данных встречается операция «front», «dequeue» или «min», и при этом очередь пуста, то программа должна вместо числового значения вывести строку «error».



Формат ввода
------------



В первой строке входных данных записано единственное число M (1 ≤ M ≤ 2 ⋅ 105) — количество команд. В следующих М строках дано по одной команде из тех, что идут выше.
 


Формат вывода
-------------



Для каждой команды выведите одну строчку — результат ее выполнения.


Пример
------




| Ввод Скопировать ввод | Вывод Скопировать вывод |
| --- | --- |
| ``` 9 enqueue 2 front dequeue size dequeue enqueue 1 enqueue 2 size min  ``` | ``` ok 2 2 0 error ok ok 2 1  ``` |

