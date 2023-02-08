#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include <print.h>
#include "include/find_process.h"

#define FILE_TYPE 4

pthread_t *pht_id;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* phread_research(void* path_res);

void multy_research(uint8_t count_ph, char* argv_[]);

void mono_research();

int main(int argc, char* argv[])
{

    for(uint8_t i=0;i<argc; i++){
        print_debug("[FIND_PROCESS] ---> %s\n", argv[i]);
    }
    
    // mono_research(argv[1]);

    if(argc > 2){       // создаем потоки
        multy_research(1, (argv +1));
    }
    else{               // путей не указанно
        mono_research(argv[1]);
    }
    // sleep(5);
    exit(EXIT_SUCCESS);

    return 0;
}

void multy_research(uint8_t count_ph, char* argv_[])
{
    pht_id = (pthread_t*)malloc(count_ph-1); 

    if(NULL == pht_id){
        perror("Ошибка кучи\n");
        exit(1);
    }

    for(uint8_t i=0;i<count_ph;i++){
        pthread_create(&pht_id[i], NULL, phread_research, (void*)argv_[i]);
    }

    for(uint8_t i=0;i<count_ph;i++){
        pthread_join(pht_id[i], NULL);
    }
    

    free(pht_id);
}


void mono_research(char* path)
{
    char* name = find_path("start.sh", path);

    if((char*)NULL == name){
        print_debug(" Ничего не нашли\n");
        return;
    }
    printf("---Path - %s\n", name);
}


void* phread_research(void* path_res){
    

    int unused;
    int ret = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &unused);
    if(ret){
        errno = ret;
        perror("Не удалось задать настройки потока\n");
        return NULL;
    }   

    char* name = find_path("start.sh", (char*)path_res);

    if((char*)NULL == name){
        print_debug(" Ничего не нашли\n");
        return NULL;
    }
    printf("Path - %s\n", name);
    
    return NULL;
}


char* find_path( char*  name,   char*  c_name)
{
    struct dirent *entry;
    DIR *c_dir;

    c_dir = opendir(c_name);    
    if(c_dir == NULL){
        perror("error open dir\n");
        return NULL;
    }
    while ((entry = readdir(c_dir)) != NULL)
    {
        if(strcmp(entry->d_name, name) == 0){
            return strcat(c_name, entry->d_name) ;
        }

        if(FILE_TYPE == entry->d_type ){

            if( strcmp(entry->d_name, ".") == 0  || strcmp(entry->d_name, "..") == 0 ){
                continue;
            }

            char * res = find_path(name,  strcat(strcat(c_name, "/"), entry->d_name)) ;    

            if(res != NULL){
                return res;
            }
            
            memset(strstr(c_name,entry->d_name), '\0', 1);
            
        }
    
    }
    closedir(c_dir);

    return NULL;

}