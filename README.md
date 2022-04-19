# Pools
## Описание алгоритма
В каждом бассейне будем хранить указатель на структуру, которая контролирует бассейн и все другие бассейны до которых можно дойти по существующим каналам. В этом решении операции Measure и Add проходят крайне быстро, так как фактически нужно лишь получить или изменить число в контролирующей структуре. Вся вычислительная сложность заключена в операции создания канала между бассейнами из разных групп. В этом случае нужно за линию пройтись по всем бассейнам из наименьшей группы и переназначить их управляющюю структуру.
## Requirments
1. Google tests - для тестов

## Сборка:
Стандартная сборка через cmake. Доступно 2 цели.

| target | description |
| ------ | ------ |
| Sanitizers_tests | Немного unit-тестов под ASAN-ом |
| Sanitizers_performance | Требуемый тест производительности с подключенным ASAN-ом |

## Тесты
Все тесты компилируются с флагом -O0

### Измеренное время для запрошенных чисел:
Число бассейнов = 8000000

Число каналов = 12000000

Число добавлений воды в бассейны = 40000000

![Alt text](img/benchmark.png?raw=true "Результаты теста")

## Улучшения алгоритма
### Первая попытка
Попробуем изменить сам алгоритм. Основная цель - избавиться от долгой операции merge, а именно от поэлементного копирования в этой фунцкии. Можно сделать эту операцию ленивой. Таким образом, при объединение двух групп будет создаваться новая управляющая структура, но она не будет сразу управлять бассейнами, а лишь управляющими структурами 2х групп. При любой последующей операции над бассейном, его нужно переподвесить к этой новой структуре. Таким образом, явный цикл из прошлого решения становится "размазанным" по другим операциям с бассейном, и, в теории, это может дать небольшой прирост производительности, так как не все бассейны будут переподвешены. К сожалению, на практике, данная процедура переподвешивания не является cache-friendly, и производительность упала ~ в 100 раз.   

### Вторая попытка
![Alt text](img/profiler.png?raw=true "Профилирование кода")
Профилирование кода показывает, что 33% всего времени программа проводит в функции CreateParent, при этом половина этой функции заключена в функции std::vector::push_back, а та в свою очередь много проводит в resize. Решение - вызывать resize самому, и выделять больше памяти. Данная оптимизация ускорила фнукцию connect ~ на 12%, но теперь для работы требуется больше памяти. 

Данному методу требуется поиск оптимальной константы, в данный момент resize при необходимости выделяет в 10 раз больше памяти чем вектору нужно, но неизвестен прирост производительности при других параметрах, возможно существует более оптимальное число.    

![Alt text](img/new_benchmark.png?raw=true "Новые результаты")

### Третья попытка
Объединим все наработки в один алгоритм. При объединении маленьких групп бассейнов будем просто объединять управляющие блоки, при объединении больших групп будем создавать parent структуру. 

По итогу всех оптимизаций, программа стала в раз быстрее.
