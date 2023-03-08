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
using namespace std;
typedef struct
{
	char name[20];
	double price;
} Commodity;

int main(int argc , char*argv[])
{
    int bufferSize=stoi(argv[1]);
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,sizeof(Commodity)*bufferSize,0666|IPC_CREAT);
    shmctl(shmid,IPC_RMID,NULL);
    cout<<"Memory destroyed"<<endl;
}
