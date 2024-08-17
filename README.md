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


