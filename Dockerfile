# Используем официальный образ Ubuntu
FROM ubuntu:20.04

# Устанавливаем необходимые пакеты для сборки Qt
RUN apt-get update && apt-get install -y \
    build-essential \
    qt5-default \
    qtbase5-dev \
    qtbase5-dev-tools \
    qtchooser \
    qtscript5-dev \
    git \
    cmake \
    g++

# Устанавливаем X11 для отображения GUI из контейнера на хосте
RUN apt-get install -y libx11-dev

# Создаем рабочую директорию для приложения
WORKDIR /usr/src/app

# Копируем исходный код в контейнер
COPY . .

# Собираем приложение
RUN qmake && make

# Запуск Qt приложения
CMD ["./my_qt_app"]
