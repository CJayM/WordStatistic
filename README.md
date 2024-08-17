# Решение тестового задания

> Напишите приложение на Qt с использованием QML, которое считывает слова из файла и выводит топ 15 слов (по количеству вхождений) в режиме реального времени в виде гистограммы. Приложение должно быть многопоточным - чтение и обработка файла должны происходить в отдельном от UI потоке, гистограмма должна обновляться в условно реальном времени (без видимых продолжительных задержек). Интерфейс приложения должен быть адаптивным и учитывать размеры текущего окна.
>
> Приложение должно содержать следующие элементы интерфейса:
>
> - Гистограмма (нежелательно использовать ChartView из модуля charts)
> - Прогресс бар обработки открытого файла
> - Кнопка "Открыть" для выбора файла, из которого будут считаны слова.
> - Кнопка "Старт", для запуска чтения файла и подсчета статистики слов.
> - Кнопка "Пауза", для приостановки чтения файла. (Опционально, наличие кнопки будет плюсом)
> - Кнопка "Отмена", для прерывания чтения файла и сброса статистики. (Опционально, наличие кнопки будет плюсом)
>
> Существенным плюсом будет наличие readme файла с описанием архитектуры и логики работы приложения.



## Этапы решения

### Этап 1

- [x] Раскидать базовый UI с выделением пространства для будущей гистограммы, кнопок и прогресс бара
- [x] Создать статичную модель в qml для первых шагов в реализации гистограммы
- [x] Создать компонент гистограммы, использующий модель

### Этап 2

- [ ] Создать модель С++ со случайными данными
- [ ] Передать С++ модель в qml при нажатии кнопки `Старт`

### Этап 3

- [ ] создать свойство пути для файла и отобразить его в UI
- [ ] Вызывать диалог выбора файла при нажатии кнопки `Открыть`
- [ ] Сбрасывать значение свойства пути при нажатии кнопки `Отмена`
- [ ] Заполнять и передавать модель данными из файла по пути при нажатии на кнопку `Старт`
- [ ] Сохранить свойство пути для восстановления при последующем запуске приложения

### Этап 4

- [ ] Читать слова из файла в отдельном потоке
- [ ] Передавать в qml прогресс чтения (для прогресс бара)
- [ ] Использовать кнопку `Пауза` для приостановки чтения и обработки файла
- [ ] Использовать кнопку `Отмена` для сброса модели и отмены обработки файла
- [ ] Добавить состояния "Чтение/Пауза/Сброс"

### Этап 5

- [ ] Использовать `QFileSystemWatcher` для отслеживания изменения файла
- [ ] Считать статистику по прочтённым словам в несколько потоков
- [ ] Добавить искусственную задержку (для визуально заметного обновления UI)

### Этап 6

- [ ] Добавить изменение количества слов в гистограмме
- [ ] Добавить красивой анимации
- [ ] Рисовать гистограмму через Canvas