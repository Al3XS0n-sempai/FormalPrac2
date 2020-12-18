# **Algorithm Early(version 1.0)**

## Кратка информация

Был написан Алгоритм Эрли для проверки принадлежности слова языку языку заданному КС-Грамматикой.

Для использования нужно передать в аргументах программы файл с грамматикой в следующем формате:

```c++
N // integer, количество правил вывода
RULE_1
.
.
.
RULE_N  // RULE_i = "A->B", где A - нетерминал из алфавита {'A', ..., 'Z'}, B - терминал из алфавита {'a', ..., 'z'}.
S // Стартовый нетерминал из алфавита {'A', ... 'Z'}
```

После этого можно вводить слова которые вы хотите проверить на принадлежность языку.
> P.S.(1) Предпологается что заданна корректная КС-грамматика.

> P.S.(2)  Я зыбыл добавить сигнальное слово для остановки.
> <details>
>  <summary>Поэтому </summary>
>    пока что ctrl+c
> </details>

---

## Что планируется

- [ ] Покрытие кода unit-тестами(В первую очередь).
- [ ] Изменение формата ввода слова для проверки
- [ ] Измение формата файла с грамматикой, в частности:

  - [ ] Расширение функционала в виде возможности задания алфавита
  - [ ] Возможность задания правил вида A->B|C|D...
  
---

## Источники
* [Google](google.ru)
* [Конспект с семинаров](https://drive.google.com/file/d/13Dl96yDiYXGOMoqB2fYzv1GgfyYE7JqN/view)
* Супер сосед