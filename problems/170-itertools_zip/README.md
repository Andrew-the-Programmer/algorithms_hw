 F. Itertools.Zip — База 2024 2 сем. Задание 3\. C\+\+ — Яндекс.КонтестВаше участие в соревновании завершено. Вы можете дорешивать задачи и отправлять решения вне соревнования


F. Itertools.Zip
================




| Ограничение времени | 0\.15 секунд |
| --- | --- |
| Ограничение памяти | 16\.0 Мб |
| Ввод | стандартный ввод или input.txt |
| Вывод | стандартный вывод или output.txt |






[https://gitlab.com/ibr11/cpp\_psami\_base\_2023/\-/tree/main/itertools/zip](https://gitlab.com/ibr11/cpp_psami_base_2023/-/tree/main/itertools/zip)


### Itertools


*Одним из минусов языка C\+\+ является отсутствие удобного интерфейса работы с последовательностями и промежутками
 значений, который, по большому счету сводится к ручному написанию циклов и работе со встроенными итераторами. С
 введением библиотеки  в C\+\+20 ситуация заметно улучшилась. В этом
 цикле задач мы попытаемся решить заявленную проблему средствами C\+\+17\.*


### Zip


Для одновременного прохода по нескольким контейнерам приходится вручную поддерживать итераторы на каждый из них:




```
auto fit = first.begin();
auto sit = second.begin();
for (; fit != first.end() && sit != second.end(); ++fit, ++sit) {
    // ...
}
```


Сравните, например, с языком Python:
 `python
 for x, y in zip(first, second):
 # ...` 



Хотелось бы иметь подобный лаконичный код и в C\+\+ (благо range\-based for завезли в C\+\+11\):




```
for (auto&& [x, y] : zip(first, second)) {
    // ...
}
```


Проблема в том, что в стандартной библиотеке (до C\+\+20\) нет сущности `zip`, которую можно было использовать в
 подобном контексте. Ну а раз так \- надо ее реализовать самостоятельно!


### Детали реализации


Необходимо реализовать `Zip` (класс или функцию), который возвращает объект некоторого класса (вам нужно его
 реализовать) с определенными методами `begin` и `end`. Эти методы должны возвращать итераторы, которые при разыменовании
 возвращают набор результатов (`std::tuple`) разыменования итераторов переданных контейнеров.


**Примеры:** (больше примеров см. в тестах)




```
std::list<int> l{1, 2, 3, 4, 5};
std::vector<double> v{1.0, 2.0, 3.0, 4.0};

for (auto&& [x, y] : Zip(l, v)) { ... };  // [x, y] in {[1, 1.0], [2, 2.0], [3, 3.0], [4, 4.0]}

for (auto&& [x, y] : Zip(l, v)) {
    x = 1;
    y = 0;
}
// l == {1, 1, 1, 1, 5}
// v == {0, 0, 0, 0}
```


*Указание: вспомните как работает range\-based for в C\+\+*.


### Дополнительная часть


Пожержите работу Zip с временными контейнерами. Добавьте директиву `#define TEMPORARY_ZIP_IMPLEMENTED`, если реализовали данную часть.



