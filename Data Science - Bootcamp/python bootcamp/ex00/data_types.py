def data_types():
    intger_var = 7
    str_var = 'string'
    float_var = 5.6
    bool_var = True
    list_var = [1, 2, 3]
    dict_var = {'key': 1, 'key_long': 2}
    tuple_var = (1, 2, 4)
    set_var = {1, 3, 5}

    types_list = [
        type(intger_var).__name__,
        type(str_var).__name__,
        type(float_var).__name__,
        type(bool_var).__name__,
        type(list_var).__name__,
        type(dict_var).__name__,
        type(tuple_var).__name__,
        type(set_var).__name__
    ]
    
    return types_list

if __name__ == '__main__':
    result = data_types()
    
    # Форматируем вывод без кавычек
    formatted_output = "[" + ", ".join(result) + "]"
    print(formatted_output)
