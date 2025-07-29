#!/bin/sh

# Путь к файлам
INPUT_FILE="../ex01/hh.csv"
OUTPUT_FILE="hh_sorted.csv"

{
    head -n 1 "$INPUT_FILE"
    tail -n +2 "$INPUT_FILE" | sort -t ','  -k1,1 -k2,2n
} > hh_sorted.csv
