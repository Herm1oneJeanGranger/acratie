def process_csv(input_file, output_file):
    with open('ds.csv', 'r') as csvfile:
        reader = csvfile.readlines()

        processed_lines = []
        in_quotes = False
        current_row = []

        for row in reader:
            if row.count('"') % 2 == 0:
                processed_row = row.replace(',', '\t')
            else:
                processed_row = row

            processed_lines.append(processed_row)

    with open('ds.tsv', 'w') as tsvfile:
        tsvfile.writelines(processed_lines)

if __name__ == '__main__':
    process_csv('ds.csv', 'ds.tsv')

    