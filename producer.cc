#include <iostream>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cstring>
#include<bits/stdc++.h>
#include <random>
#include <cmath>
#include <vector>
#include<list> 
#include <typeinfo>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <chrono>
#include <iomanip>


using namespace std;

typedef struct
{
	char name[20];
	double price;
} Commodity;


int validateCommodityName(char* name)
{
    if(strcmp(name,"GOLD")==0 || strcmp(name,"SILVER")==0 || strcmp(name,"CRUDEOIL")==0|| strcmp(name,"NATURALGAS")==0|| strcmp(name,"ALUMINIUM")==0|| strcmp(name,"COPPER")==0|| strcmp(name,"NICKEL")==0|| strcmp(name,"LEAD")==0|| strcmp(name,"ZINC")==0|| strcmp(name,"MENTHAOIL")==0|| strcmp(name,"COTTON")==0){
        return 1;
    }
    printf("Invalid Commodity Name");
    return 0;
}

int main(int argc,char*argv[])
{   
    int bufferSize=stoi(argv[5]);
    int comIndex=0;
    Commodity *coms;
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,sizeof(Commodity)*bufferSize,0666|IPC_CREAT);
    coms = (Commodity*) shmat(shmid,0,0);
    char *name=argv[1];
    default_random_engine generator;
    double variance=(double)sqrt(stof(argv[3]));
    double mean=(double)sqrt(stof(argv[2]));
    normal_distribution<double> distribution(mean,variance);
    int * len_arr_ptr= (int *) &coms[bufferSize-1];
    int s = semget(7, 1, 0666);
    int n = semget(8, 1, 0666);
    int e = semget(10, 1, 0666);
    if(s < 0 || n < 0 || e < 0){
        perror("ERROR CREATING SEMAPHORES.");
        exit(1);
    }

    struct sembuf sem[1];
    sem[0].sem_num = 0;
    sem[0].sem_op = 0; 
    sem[0].sem_flg = 0;

    while (1){
        time_t t = time(NULL);
        
        double price = distribution(generator);
        // awl log  
        struct timespec ts;
    clock_gettime(CLOCK_REALTIME,&ts);
     struct tm tm = *localtime(&t);
  printf("[%d/%02d/%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);cout<<"."<<ts.tv_nsec<<"]";
        cerr<<name<<": generating a new value "<<price<<endl;
        //int len_arr = *len_arr_ptr;
        if(validateCommodityName(name)){
           // tany log
           printf("[%d/%02d/%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);cout<<"."<<ts.tv_nsec<<"]";
        cerr<<name<<": trying to get mutex on shared buffer "<<endl;
            sem[0].sem_op = -1;
            semop(e,sem,1);
            //sem[0].sem_op = -1;
            semop(s,sem,1);
            int len_arr = *len_arr_ptr;
            //talt log
            printf("[%d/%02d/%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);cout<<"."<<ts.tv_nsec<<"]";
        cerr<<name<<": placing "<<price<<" on shared buffer "<<endl;
            strcpy(coms[len_arr].name,name);
            coms[len_arr].price=price;
            *len_arr_ptr = len_arr+1;  
            sem[0].sem_op = 1;
            semop(s,sem,1);
            semop(n,sem,1);                 
        }else{
            cout<<"Invalid Commodity"<<endl;
            exit(1);
        }
        //rab3 log
        printf("[%d/%02d/%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);cout<<"."<<ts.tv_nsec<<"]";
        cerr<<name<<": sleeping for "<<stoi(argv[4])<< " ms"<<endl; 
        sleep(stoi(argv[4])/1000);//getfrom arg
    //sleep for time 
    }
    //detach from shared memory 
    shmdt(coms);
    //shmctl(shmid,IPC_RMID,NULL);
    return 0;
}
