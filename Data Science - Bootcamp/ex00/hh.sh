#!/bin/bash

# Проверка аргументов
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <job_title>"
    exit 1
fi

JOB_TITLE="$1"

# Создаем директорию, если она не существует
mkdir -p ../ex00

# Выполняем запрос к API
response=$(curl -s -w "%{http_code}" -G 'https://api.hh.ru/vacancies' \
    --data-urlencode "text=$JOB_TITLE" \
    --data "per_page=20" \
    --data "page=0")

# Извлекаем код ответа
http_code="${response: -3}"
json_response="${response:0:${#response}-3}"

# Проверяем код ответа
if [ "$http_code" -ne 200 ]; then
    echo "Ошибка: Код ответа от API: $http_code"
    echo "$json_response"  # Выводим тело ответа для анализа
    exit 1
fi

# Обработка JSON с помощью jq
formatted_data=$(echo "$json_response" | jq -r '{
    page: .page,
    found: .found,
    clusters: .clusters,
    arguments: .arguments,
    per_page: .per_page,
    pages: .pages,
    items: [.items[] | {
        apply_alternate_url: .apply_alternate_url,
        id: .id,
        created_at: .created_at,
        name: .name,
        has_test: .has_test,
        alternate_url: .alternate_url,
        lat: (.address.lat // null),         
        lng: (.address.lng // null),
        address: (.address.raw // ""),
        salary: .salary,
        metro: (.address.metro // ""),
        station_id: (.address.station_id // ""),
        line_name: (.address.line_name // ""),
        line_id: (.address.line_id // ""),
        station_name: (.address.station_name // ""),
        street: (.address.street // ""),
        building: (.address.building // ""),
        city: (.address.city // ""),
        description: .description,
        raw: (.address.raw // "")
    }]
}')

# Сохраним отформатированные данные в файл
echo "$formatted_data" > ../ex00/hh.json

echo "Данные о вакансиях сохранены в ex00/hh.json"