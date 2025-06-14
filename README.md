# Лабораторная работа №4  
_Обобщённая работа с бинарными деревьями на шаблонах_

---

## Постановка задачи  

Реализовать шаблонное бинарное дерево с базовыми операциями и поддержкой функциональных методов `Map`, `Where`, `Reduce`.  
Обеспечить интерфейс взаимодействия с деревом через консольное меню.

---

## Описание решения  

### Используемые типы данных  
- `Leaf<Type>` — структура узла дерева с ключом и двумя потомками  
- `BinaryTree<Type>` — основная структура бинарного дерева  
- `Mapper<Type>` — функция отображения одного значения (`Map`)  
- `Condition<Type>` — предикат-функция фильтрации (`Where`)  
- `Reducer<Type>` — функция свёртки (`Reduce`)  

---

## Функции

### Tree.hpp

#### Структура `Leaf<Type>`

> Узел бинарного дерева

```cpp
template<typename Type>
class Leaf {
private:
    Type value;
    Leaf* left;
    Leaf* right;
public:
    ...
};
```

##### Поля:
- `value` — значение, хранимое в узле
- `left` — левый потомок
- `right` — правый потомок

---

##### Методы:

- `Leaf()`  
    > Конструктор по умолчанию.  
    > Инициализирует пустой узел (`value = NULL`, потомки `nullptr`)

- `explicit Leaf(val: Type)`  
    > Конструктор с заданным значением  
    >
    > _ПАРАМЕТРЫ:_  
    >   * **val** — значение, сохраняемое в узле

- `Get() -> Type&`  
    > Возвращает ссылку на значение, хранимое в узле

- `Left() -> Leaf*&`  
    > Возвращает ссылку на указатель левого поддерева  
    >
    > _ВОЗВРАЩАЕТ:_  
    >   * Ссылка на `left`

- `Right() -> Leaf*&`  
    > Возвращает ссылку на указатель правого поддерева  
    >
    > _ВОЗВРАЩАЕТ:_  
    >   * Ссылка на `right`

---

#### Шаблонный класс `BinaryTree<Type>`

> Класс бинарного дерева поиска с поддержкой операций `Map`, `Where`, `Reduce`

```cpp
template<typename Type>
class BinaryTree {
private:
    Leaf<Type>* root;
    int size;
public:
    ...
};
```

---

##### Поля:

- `root` — корневой узел дерева
- `size` — текущее количество элементов

---

#### Методы:

- `BinaryTree()`  
    > Конструктор по умолчанию. Инициализирует пустое дерево

- `~BinaryTree()`  
    > Деструктор. Рекурсивно удаляет все узлы дерева

- `Root() -> Leaf<Type>*&`  
    > Возвращает ссылку на корневой узел

- `Size() -> int&`  
    > Возвращает ссылку на размер дерева

- `Insert(key: Type)`  
    > Вставляет элемент в дерево по правилу BST  
    >
    > _ПАРАМЕТРЫ:_  
    >   * **key** — значение для вставки

- `Remove(key: Type)`  
    > Удаляет элемент из дерева (BST-логика)

- `Find(key: Type) -> bool`  
    > Проверяет наличие элемента в дереве

- `PrintPLR(leaf: Leaf<Type>*)`  
    > Обходит дерево в прямом порядке (лево → право → корень)  
    >
    > _ПАРАМЕТРЫ:_  
    >   * **leaf** — начальный узел

- `PrintPRL(leaf: Leaf<Type>*)`  
    > Обходит дерево в обратном порядке (право → лево → корень)

- `Clear(leaf: Leaf<Type>*)`  
    > Удаляет поддерево, начиная с заданного узла

- `deleteTree(leaf: Leaf<Type>*)`  
    > Рекурсивно удаляет всё дерево  
    >
    > _ПАРАМЕТРЫ:_  
    >   * **leaf** — текущий узел, с которого начать удаление

---

#### Функциональные методы:

- `Map(func: Mapper<Type>)`  
    > Применяет функцию ко всем элементам дерева

    > _ПАРАМЕТРЫ:_  
    >   * **func** — функция `Type func(Type&)`

- `Where(filter: Condition<Type>)`  
    > Удаляет все элементы, не удовлетворяющие условию

    > _ПАРАМЕТРЫ:_  
    >   * **filter** — логическая функция `bool func(Type&)`

- `Reduce(reduce: Reducer<Type>)`  
    > Сворачивает всё дерево в один элемент  
    > Заменяет дерево одним новым узлом — результатом

    > _ПАРАМЕТРЫ:_  
    >   * **reduce** — функция `Type func(const Type&, const Type&)`

---

#### Вспомогательные приватные методы:

- `ChangerMap(...)` — рекурсивно применяет `Map`
- `ChangerWhere(...)` — собирает в `set` все неподходящие элементы
- `ChangerReduce(...)` — рекурсивно применяет аккумуляцию `Reduce`

---

### Test.hpp

#### Назначение

Файл `Test.hpp` содержит модульные тесты для проверки корректности работы бинарного дерева `BinaryTree<Type>`.

---

#### Функции:

- `testTree()`  
    > Запускает последовательные проверки основных операций над деревом:  
    > создание, вставка, фильтрация (`Where`), отображение (`Map`), свёртка (`Reduce`).

---

#### Итог:

Если все `assert`-проверки проходят успешно, выводятся подтверждения:
```
Create tests were passed!
Insert tests were passed!
Where tests were passed!
Map tests were passed!
Reduce tests were passed!
Tree tests were passed!
```

---

### menu.hpp

#### Назначение

Файл `menu.hpp` реализует консольное меню для взаимодействия с бинарным деревом поиска `BinaryTree<int>`. Пользователь может выполнять над деревом базовые и функциональные операции.

---

#### Макросы

- `EMPTY`  
    > Проверяет, пусто ли дерево (`tree->Root() == nullptr`)  
    > Если да — выводит `Empty` и завершает текущую операцию

- `PRINT_PLR`  
    > Обходит дерево в порядке: Лево → Право → Корень (`PrintPLR`)  
    > Только если дерево не пустое

- `PRINT_PRL`  
    > Обходит дерево в порядке: Право → Лево → Корень (`PrintPRL`)  
    > Только если дерево не пустое

---

#### Функции

- `void talker()`  
    > Выводит на экран список доступных команд:
    ```
    1. New tree from array  
    2. Insert the note  
    3. Find the key  
    4. Print the tree (PLR)  
    5. Print the tree (PRL)  
    6. Remove the note  
    7. Map()  
    8. Where()  
    9. Reduce()  
    10. Get the Size of tree  
    0. Finish program
    ```

---

- `void menu()`  
    > Основной цикл взаимодействия с пользователем через стандартный ввод/вывод  
    > Создаётся объект `BinaryTree<int>`, и обрабатываются пользовательские команды
  