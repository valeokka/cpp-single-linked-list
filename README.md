# cpp-single-linked-list
# Яндекс Практикум: односвязный список, финальный проект
`Односвязный список`, также известный как линейный однонаправленный список, является структурой данных, представляющей собой последовательность элементов одного типа. Элементы списка связаны между собой с помощью указателей. Каждый элемент указывает на следующий элемент, а последний элемент указывает на значение nullptr. Данные элементов списка хранятся в динамической памяти.

`SingleLinkedList` предоставляет возможность эффективно добавлять и удалять элементы в начале и конце списка. Однако, передвигаться по элементам списка можно только в прямом направлении. Невозможно получить адрес предыдущего элемента, основываясь только на содержимом текущего элемента.

# Основные функции 
## Конструкторы:
- `Конструктор по умолчанию:` создает пустой список.
- `Конструктор на основе initializer_list:` создает список, содержащий элементы переданного initializer_list.
- `Конструктор копирования:` создает копию списка. Обеспечивает строгую гарантию безопасности исключений.
- `Операция присваивания:` присваивает один список другому. Обеспечивает строгую гарантию безопасности исключений.
## Деструктор:
- При разрушении списка удаляются все его элементы.
## Основные методы:
- `GetSize:` возвращает количество элементов в списке.
- `IsEmpty:` возвращает true, если список пуст, и false в противном случае.
- `PushFront:` вставляет элемент в начало списка. Обеспечивает строгую гарантию безопасности исключений.
- `Clear:` очищает список.
- `PopFront:` удаляет первый элемент непустого списка за время O(1).
- `InsertAfter:` вставляет новый элемент следом за элементом, на который ссылается переданный итератор, за время O(1). Обеспечивает строгую гарантию безопасности исключений.
- `EraseAfter:` удаляет элемент, следующий за элементом, на который ссылается переданный итератор, за время O(1).
- Методы `before_begin и cbefore_begin:` возвращают итераторы, указывающие на фиктивную позицию перед первым элементом списка. Используются в методах InsertAfter и EraseAfter для вставки или удаления элемента в начале списка. Нельзя разыменовывать эти итераторы.
- Методы `begin, end, cbegin и cend:` возвращают итераторы на первый элемент и позицию, следующую за последним элементом списка.
- `Операции сравнения ==, !=, <, >, <=, >=:` сравнивают два списка.
- `swap:` обменивает содержимое двух списков.

# Сложность операций выполняемых над `SingleLinkedList:`
- Доступ к `begin` и `end` - константа O(1)
- Доступ к произвольному элементу контейнера - линейно по расстоянию до конца вектора O(n)
- Вставка или удаление элемента в начале списка - константа O(1)
- Вставка или удаление элемента следом за переданным итератором - константа 0(1)

# Сборка и установка
Сборка с помощью любой IDE либо сборка из командной строки

# Системные требования
Компилятор С++ с поддержкой стандарта C++17  и выше

