#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define _GNU_SOURCE
#include <unistd.h>

#include <find.h>
#include <print.h>


#include <dirent.h>

/**
 * @brief Пока заглушка, в падлу тыкать строки
 * 
 * @param argc_[in] кол-во переданных аргументов
 * @param argv_[in] указатель на строку входных символов
 * @param out_names[out] - указатель на найденные пути
 * @return true если пути указанны
 * @return false если пуни не указанны
 */
bool get_name(int argc_, char* argv_[], char* out_names[] )
{

    if(NULL == argv_){
        return false;
    }

    if(2 > argc_){
        return false;
    }

    for(uint8_t i=1;i<argc_;i++){
        print_debug("[%d] ---->  %s\n", i,  argv_[i]);
        out_names[i-1] = argv_[i];
    }
    return true;
}

int main(int argc, char* argv[])
{
    find(argc, argv);

    return 0;
}

