#!/bin/bash

# Путь к файлам
INPUT_FILE="../ex03/hh_positions.csv"
OUTPUT_FILE="hh_uniq_positions.csv"

{
    echo '"name", "count"'
    tail -n +2 "$INPUT_FILE" | cut -d',' -f3 | tr -d '"' | sort | uniq -c | sort -nr | awk '{print "\"" $2 "\", " $1}' 
} > "$OUTPUT_FILE"

echo "Подсчет уникальных позиций завершен. Результат сохранен в $OUTPUT_FILE."

