#!/bin/bash

# Путь к файлам
INPUT_FILE="../ex02/hh_sorted.csv"
OUTPUT_FILE="hh_positions.csv"

echo '"id","created_at","name","has_test","alternate_url"' > "$OUTPUT_FILE"

 tail -n +2 "$INPUT_FILE" | while IFS=',', read -r id created_at name has_test alternate_url; do
 #Удаляем кавычки из названия должности
 name=$(echo "$name" | tr -d '"')

 if echo "$name" | grep -q -E 'Junior|Middle|Senior'; then
 levels=$(echo "$name" | grep -o -E 'Junior|Middle|Senior' | tr '\n' '/' | sed 's/\/$//')
 else 
 levels="-"
 fi

 # Записываем результат в hh_positions.csv
  echo "\"$id\",\"$created_at\",\"$levels\",$has_test,\"$alternate_url\"" >> "$OUTPUT_FILE"
done

echo "Очистка завершена. Результат сохранен в $OUTPUT_FILE."