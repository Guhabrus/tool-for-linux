#ifndef _DEBUG_H_
#define _DEBUG_H_

#define PRINT_DEBUG


#ifdef  PRINT_DEBUG
    #include <stdio.h>
    #define print_debug(...) printf(__VA_ARGS__)

#else
    #define print_debug(...) while(0){}

#endif  /*PRINT_DEBUG*/

#define PRINT_ERROR

#ifdef  PRINT_ERROR
    #ifndef PRINT_DEBUG
        #include <stdio.h>
    #endif  

    #define print_error(...) fprintf(stderr,__VA_ARGS__)

#else
    #define print_error(...) while(0){}
#endif /*PRINT_ERROR*/


#define PRINT_INFO

#define STREAM_OUT stdout

#ifdef PRINT_INFO
    #ifndef PRINT_DEBUG
        #ifndef PRINT_ERROR
            #include <stdio.h>
        #endif
    #endif

    #define print_info(...) fprintf(STREAM_OUT,__VA_ARGS__)
#else    
    #define print_info(...) while(0){}
#endif /*PRINT_INFO*/

#endif /*_DEBUG_H*/