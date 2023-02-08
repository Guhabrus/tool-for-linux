#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/wait.h>

#include <find.h>
#include <print.h>

int get_status_exit(int status);


char* get_process_name( char* argv[]){
    if(NULL == argv){
        return (char*)NULL;
    }
    char* result = strrchr(argv[0],'/');

    if((char*)NULL == result ){
        return argv[0];
    }else{
        return result+1;
    }
}




bool find(int argc_, char* argv_[])
{
    if(! argc_){
        return false;
    }

    pid_t f_pid = fork();

    if(-1 == f_pid){
        perror(" ошибка создания процесса\n");
        return false;
    }

    if(!f_pid)           // Дочерний процесс
    {
        print_debug("%s\n",  get_process_name(argv_));

        int ret = execv("/home/maksim/Myfolder/Scince/C/Linux/ProgManager/obj/find_proces", argv_);
        if(-1 == ret)  {
            perror(" Ошибка создания процесса\n");
        }
        
    }
    else                // Процесс родитель
    {   
        int status = 0;
        pid_t p_id = wait(&status);
        if(-1 == p_id){
            perror("error\n");
        }

        if(!get_status_exit(status)){
            fprintf(stderr, "Дочерний процесс завершился со статусом %d\n", status);
        }
    }
    
    return true;

}



int get_status_exit(int status)
{
    if (WIFEXITED (status)){
        return 0;
    }

    if(ECHILD ==  errno ){
        return 1;
    }

    if(errno == EINTR){
        return 2;
    }
    
    if(WIFSIGNALED (status)){
        return 3;
    }
    if(WIFSTOPPED (status)){
        return 4;
    }
    
    if (WIFCONTINUED (status)){
        return -1;
    }      

    return 0; 
}