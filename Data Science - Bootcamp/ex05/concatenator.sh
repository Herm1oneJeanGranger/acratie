#!/bin/sh

# Скрипт concatenator.sh


if [ "$#" -lt 2 ]; then
  echo "Использование: $0 <выходной_csv_файл> <входные_файлы...>"
  exit 1
fi

OUTPUT_FILE=$1
shift

# Создаем выходной файл и записываем туда заголовок из первого файла
FIRST_FILE=$1

if [ ! -f "$FIRST_FILE" ]; then
  echo "Ошибка: Файл $FIRST_FILE не существует."
  exit 1
fi

# Копируем заголовок из первого файла в выходной файл
head -n 1 "$FIRST_FILE" > "$OUTPUT_FILE"

# Обрабатываем все входные файлы, пропуская заголовок
for FILE in "$@"; do
  if [ -f "$FILE" ]; then
    tail -n +2 "$FILE" >> "$OUTPUT_FILE"
  else
    echo "Предупреждение: Файл $FILE не существует и будет пропущен."
  fi
done

# Сообщение об успешном завершении
echo "Объединение завершено. Результат записан в $OUTPUT_FILE."
