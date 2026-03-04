#!/bin/sh

# Путь к файлам
INPUT_FILE="../ex00/hh.json"
OUTPUT_FILE="hh.csv"

# Запись заголовков в CSV
echo "id,created_at,name,has_test,alternate_url" > "$OUTPUT_FILE"

# Применение jq к фильтру и добавление данных в CSV файл
jq -r '.items[] | [.id, .created_at, .name, .has_test, .alternate_url] | @csv' "$INPUT_FILE" >> "$OUTPUT_FILE"

echo "Данные о вакансиях сохранены в ex01/hh.csv"