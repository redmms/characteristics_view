﻿# О чем проект:
Приложение для работы с табличными данными о деталях.

## Основные функции: 
1. Добавить строку:
Добавляем строку в конец таблицы.
Для заполнения строки открывается диалоговое окно, с соответствующими полями ввода.

2. Удалить строку:
Удаляет выделенную строку.

## Дополнительный функционал:
- Добавлены иконки в таблицу, чтобы их убрать в соответствующем хэлпере необходимо 
изменить метод getIcon()
- Добавлена возможность работать с деталями по указателю, при изменении их данных
это автоматически отобразится в таблице, в том числе можно удалять их.
- Каждый материал содержит полное имя name и сокращенное short_name, short_name 
содержит только первое слово из name
- Стрелка QComboBox::down-arrow "переворачивается" при нажатии

## Структура кода:
- MainWindow и ControllerDialog - UI классы.
- FillMode - класс описывающий режим ввода, какие поля показывать/скрывать, какие
разгреить/загреить, какие значения указывать по умолчанию и т.д. Можно создавать
по объекту этого класса для каждого способа расчёта параметров детали, если в них 
отличаются требуемые поля ввода и т.п.
- DetailItem - класс хранящий информацию о деталях, предназначенный для хранения в
табличной модели, испускает сигналы, когда его поля меняются.
- Material - класс хранящий информацию о материале и способе его штриховки.
- DetailModel - класс хранящий основую информацию - список деталей. Использует 
вспомогательные классы наследники AbstractHelper для каждой колонки.
Каждый столбец соответствует полю класса DetailItem, либо его внутренних классов.

## Работа вспомогательных классов:
Схема подключения сигналов деталей на примере трёх пелвых столбцов таблицы.
Каждый помощник отвечает за своё поле в DetailItem и, в некотором смысле, 
представляет собой один столбец табличной модели. Этот подход более
объектно-ориентированный и универсальный, позволяет проще реализовать остальные
роли ячеек.
![helpers chart]("./readme_media/helpers_net.png")  
