#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *thread_routinel1(void *arg){
    fprintf(stdout, "thread1: hello world!
");
    sleep(1);
    return NULL;
}

void *thread_routinel2(void *arg){
    fprintf(stdout, "thread2: I'm running...
");
    pthread_t main_thread = (pthread_t)arg;
    /* detach??? */
    pthread_detach(pthread_self());

    if(!pthread_equal(main_thread, pthread_self())){
        fprintf(stdout, "thread2: main thread id is not equal thread2
");
    }
    pthread_join(main_thread, NULL);
    fprintf(stdout, "thread2:main thread exit!
");

    fprintf(stdout, "thread2:exit!
");
    fprintf(stdout, "thread2:process exit!
");
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    pthread_t t1;
    if(pthread_create(&t1, NULL, thread_routinel1, NULL)!=0){
        fprintf(stderr, "create thread fail.
");
        exit(-1);
    }
    pthread_join(t1, NULL);
    fprintf(stdout, "main thread: thread1 terminated!

");

    pthread_t t2;
    if(pthread_create(&t2, NULL, thread_routinel2, (void*)pthread_self())!=0){
        fprintf(stderr, "create thread fail.
");
        exit(-1);
    }
    fprintf(stdout, "main thread: sleeping...
");
    sleep(3);
    fprintf(stdout, "main thread:exit!
");
    pthread_exit(NULL);
    fprintf(stdout, "never reach here!
");
    return 0;
}

