#ifndef FIND_PROCESS_H
#define FIND_PROCESS_H


/**
 * @brief Функция поиска файла
 * 
 * @param name  - искомое имя
 * @param c_name - исходная дериктория поиска
 * @return char* - NULL в случае если файл не нашелся, имя если нашли
 */
char* find_path( char*  name,   char*  c_name);

#endif