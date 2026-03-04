def process_csv(input_file, output_file):
    with open(input_file, 'r', encoding='utf-8') as csvfile:
        processed_lines = []
        in_quotes = False  # Флаг для отслеживания, находимся ли мы внутри кавычек
        current_row = []

        for line in csvfile:
            # Убираем символы новой строки в конце строки
            line = line.rstrip('\n')
            for char in line:
                if char == '"':
                    in_quotes = not in_quotes  # Меняем состояние флага при встрече кавычки
                elif char == ',' and not in_quotes:
                    current_row.append('\t')  # Заменяем запятую на табуляцию, если не внутри кавычек
                    continue
                current_row.append(char)  # Добавляем текущий символ в строку

            processed_lines.append(''.join(current_row))  # Объединяем символы в строку
            current_row = []  # Сбрасываем текущую строку для следующей итерации

    with open(output_file, 'w', encoding='utf-8') as tsvfile:
        tsvfile.write('\n'.join(processed_lines))  # Записываем обработанные строки в выходной файл

if __name__ == '__main__':
    process_csv('ds.csv', 'ds.tsv')