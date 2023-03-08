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
#include <bits/stdc++.h>
#include <random>
#include <cmath>
#include <vector>
#include <list>
#include <typeinfo>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <queue>
#include <errno.h>

using namespace std;

typedef struct
{
    char name[20];
    double price;
} Commodity;

int main(int argc, char *argv[])
{

    /*QUEUES OF 11 ELEMENTS */
    deque<double> GOLD;
    deque<double> SILVER;
    deque<double> CRUDOIL;
    deque<double> NATURALGAS;
    deque<double> ALUMINIUM;
    deque<double> COPPER;
    deque<double> NICKEL;
    deque<double> LEAD;
    deque<double> ZINC;
    deque<double> MENTHAOIL;
    deque<double> COTTON;

    GOLD.push_back(0.00);
    SILVER.push_back(0.00);
    CRUDOIL.push_back(0.00);
    NATURALGAS.push_back(0.00);
    ALUMINIUM.push_back(0.00);
    COPPER.push_back(0.00);
    NICKEL.push_back(0.00);
    LEAD.push_back(0.00);
    ZINC.push_back(0.00);
    MENTHAOIL.push_back(0.00);
    COTTON.push_back(0.00);
    double average_GOLD = 0.00;
    double average_SILVER = 0.00;
    double average_CRUDEOIL = 0.00;
    double average_NATURALGAS = 0.00;
    double average_ALUMINIUM = 0.00;
    double average_COPPER = 0.00;
    double average_NICKEL = 0.00;
    double average_LEAD = 0.00;
    double average_ZINC = 0.00;
    double average_MENTHAOIL = 0.00;
    double average_COTTON = 0.00;
    double before_avarege_GOLD=0.00;
    double before_avarege_SILVER=0.00;
    double before_avarege_CRUDEOIL=0.00;
    double before_avarege_NATURALGAS=0.00;
    double before_avarege_ALUMINIUM=0.00;
    double before_avarege_COPPER=0.00;
    double before_avarege_NICKEL=0.00;
    double before_avarege_LEAD=0.00;
    double before_avarege_ZINC=0.00;
    double before_avarege_MENTHAOIL=0.00;
    double before_avarege_COTTON=0.00;
    int comIndex = 0;
    Commodity *coms;
    // ftok to generate unique key
    int bufferSize = stoi(argv[1]); // change this to take argument
    //cout << "Buffer size is " << bufferSize << endl;
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, sizeof(Commodity) * bufferSize, 0666 | IPC_CREAT);
    coms = (Commodity *)shmat(shmid, NULL, 0);
    int *len_arr_ptr = (int *)&coms[bufferSize - 1];
    *len_arr_ptr = 0;
    key_t semKey;

    union semun
    {
        int val;
        struct semid_ds *buf;
        ushort array[1];
    } sem_attr;
    int s = semget(7, 1, 0666 | IPC_CREAT);
    int n = semget(8, 1, 0666 | IPC_CREAT);
    int e = semget(10, 1, 0666 | IPC_CREAT);
    if (s < 0 || n < 0 || e < 0)
    {
        perror("ERROR CREATING SEMAPHORES .");
        exit(1);
    }
    sem_attr.val = 1;
    if (semctl(s, 0, SETVAL, sem_attr) == -1)
    {
        perror("ERROR CREATING SEMAPHORES.");
        exit(1);
    }
    sem_attr.val = 0;
    if (semctl(n, 0, SETVAL, sem_attr) == -1)
    {
        perror("ERROR CREATING SEMAPHORES .");
        exit(1);
    }
    sem_attr.val = bufferSize;
    if (semctl(e, 0, SETVAL, sem_attr) == -1)
    {
        perror("ERROR CREATING SEMAPHORES .");
        exit(1);
    }

    struct sembuf sem[1];
    sem[0].sem_num = 0;
    sem[0].sem_op = 0;
    sem[0].sem_flg = 0;
    printf("\e[1;1H\e[2J");
    while (1)
    {
        before_avarege_GOLD=average_GOLD;
        before_avarege_SILVER=average_SILVER;
        before_avarege_CRUDEOIL=average_CRUDEOIL;
        before_avarege_NATURALGAS=average_NATURALGAS;
        before_avarege_ALUMINIUM=average_ALUMINIUM;
        before_avarege_COPPER=average_COPPER;
        before_avarege_NICKEL=average_NICKEL;
        before_avarege_LEAD=average_LEAD;
        before_avarege_ZINC=average_ZINC;
        before_avarege_MENTHAOIL=average_MENTHAOIL;
        before_avarege_COTTON=average_COTTON;


        sem[0].sem_op = -1;
        if (semop(n, sem, 1) == -1)
        {
            perror("semop");
            exit(1);
        }
        sem[0].sem_op = -1;
        if (semop(s, sem, 1) == -1)
        {
            perror("semopp");
            exit(1);
        }
        int len_arr = *len_arr_ptr;
        int tempLenArr = len_arr;
        char currname[10];
        strcpy(currname, coms[0].name);
        double currp = coms[0].price;
        // shift array
        for (int i = 0; i < len_arr; i++)
        {
            strcpy(coms[i].name, coms[i + 1].name);
            coms[i].price = coms[i + 1].price;
        }
        *len_arr_ptr = len_arr - 1;
        // printing
        /*GOLD*/
        
        if (strcmp(currname, "GOLD") == 0)
        {   
            if (GOLD.size()==1 && GOLD.back()==0.00)
            {
                GOLD.pop_front();
            }
            if (GOLD.size() < 5)
            {
                GOLD.push_back(currp);
            }

            else
            {
                GOLD.pop_front();
                GOLD.push_back(currp);
            }
            
            if (GOLD.size() == 5)
            {   
                
                for (auto x : GOLD)
                {
                    
                    average_GOLD += x;
                    
                }
                
                average_GOLD /= 5;
                
            }
   
        }
        
        /* SILVER */
        if (strcmp(currname, "SILVER") == 0)
        {   
            if (SILVER.size()==1 && SILVER.back()==0.00)
            {
                SILVER.pop_front();
            }
            if (SILVER.size() < 5)
            {
                SILVER.push_back(currp);
            }

            else
            {
                SILVER.pop_front();
                SILVER.push_back(currp);
            }
            if (SILVER.size() == 5)
            {
                for (auto x : SILVER)
                {
                    average_SILVER += x;
                }
                average_SILVER /= 5;
            }
           
        }
        /* CRUDEOIL*/
        if (strcmp(currname, "CRUDEOIL") == 0)
        {   
            if (CRUDOIL.size()==1 && CRUDOIL.back()==0.00)
            {
                CRUDOIL.pop_front();
            }
            if (CRUDOIL.size() < 5)
            {
                CRUDOIL.push_back(currp);
            }

            else
            {
                CRUDOIL.pop_front();
                CRUDOIL.push_back(currp);
            }
            if (CRUDOIL.size() == 5)
            {
                for (auto x : CRUDOIL)
                {
                    average_CRUDEOIL += x;
                }
                average_CRUDEOIL /= 5;
            }
            
        }
        /* NATURALGAS*/
        if (strcmp(currname, "NATURALGAS") == 0)
        {   
            if (NATURALGAS.size()==1 && NATURALGAS.back()==0.00)
            {
                NATURALGAS.pop_front();
            }
            if (NATURALGAS.size() < 5)
            {
                NATURALGAS.push_back(currp);
            }

            else
            {
                NATURALGAS.pop_front();
                NATURALGAS.push_back(currp);
            }
            if (NATURALGAS.size() == 5)
            {
                for (auto x : NATURALGAS)
                {
                    average_NATURALGAS += x;
                }
                average_NATURALGAS /= 5;
            }
            
        }
        /* ALUMINIUM*/
        if (strcmp(currname, "ALUMINIUM") == 0)
        {   
            if (ALUMINIUM.size()==1 && ALUMINIUM.back()==0.00)
            {
                ALUMINIUM.pop_front();
            }
            if (ALUMINIUM.size() < 5)
            {
                ALUMINIUM.push_back(currp);
            }

            else
            {
                ALUMINIUM.pop_front();
                ALUMINIUM.push_back(currp);
            }
            if (ALUMINIUM.size() == 5)
            {
                for (auto x : ALUMINIUM)
                {
                    average_ALUMINIUM += x;
                }
                average_ALUMINIUM /= 5;
            }
           
        }
        /* COPPER */
        if (strcmp(currname, "COPPER") == 0)
        {   
            if (COPPER.size()==1 && COPPER.back()==0.00)
            {
                COPPER.pop_front();
            }
            if (COPPER.size() < 5)
            {
                COPPER.push_back(currp);
            }

            else
            {
                COPPER.pop_front();
                COPPER.push_back(currp);
            }
            if (COPPER.size() == 5)
            {
                for (auto x : COPPER)
                {
                    average_COPPER += x;
                }
                average_COPPER /= 5;
            }
           
        }
        /* NICKEL */
        if (strcmp(currname, "NICKEL") == 0)
        {   
            if (NICKEL.size()==1 && NICKEL.back()==0.00)
            {
                NICKEL.pop_front();
            }
            if (NICKEL.size() < 5)
            {
                NICKEL.push_back(currp);
            }

            else
            {
                NICKEL.pop_front();
                NICKEL.push_back(currp);
            }
            if (NICKEL.size() == 5)
            {
                for (auto x : NICKEL)
                {
                    average_NICKEL += x;
                }
                average_NICKEL /= 5;
            }
            
        }
        /* LEAD */
        if (strcmp(currname, "LEAD") == 0)
        {
            if (LEAD.size()==1 && LEAD.back()==0.00)
            {
                LEAD.pop_front();
            }
            if (LEAD.size() < 5)
            {
                LEAD.push_back(currp);
            }

            else
            {
                LEAD.pop_front();
                LEAD.push_back(currp);
            }
            if (LEAD.size() == 5)
            {
                for (auto x : LEAD)
                {
                    average_LEAD += x;
                }
                average_LEAD /= 5;
            }
           
        }
        /* ZINC */
        if (strcmp(currname, "ZINC") == 0)
        {   
            if (ZINC.size()==1 && ZINC.back()==0.00)
            {
                ZINC.pop_front();
            }
            if (ZINC.size() < 5)
            {
                ZINC.push_back(currp);
            }

            else
            {
                ZINC.pop_front();
                ZINC.push_back(currp);
            }
            if (ZINC.size() == 5)
            {
                for (auto x : ZINC)
                {
                    average_ZINC += x;
                }
                average_ZINC /= 5;
            }
            
        }
        /* MENTHAOIL */
        if (strcmp(currname, "MENTHAOIL") == 0)
        {   
            if (MENTHAOIL.size()==1 && MENTHAOIL.back()==0.00)
            {
                MENTHAOIL.pop_front();
            }
            if (MENTHAOIL.size() < 5)
            {
                MENTHAOIL.push_back(currp);
            }

            else
            {
                MENTHAOIL.pop_front();
                MENTHAOIL.push_back(currp);
            }
            if (MENTHAOIL.size() == 5)
            {
                for (auto x : MENTHAOIL)
                {
                    average_MENTHAOIL += x;
                }
                average_MENTHAOIL /= 5;
            }
            
        }
        /* COTTON */
        if (strcmp(currname, "COTTON") == 0)
        {   
            if (COTTON.size()==1 && COTTON.back()==0.00)
            {
                COTTON.pop_front();
            }
            if (COTTON.size() < 5)
            {
                COTTON.push_back(currp);
            }

            else
            {
                COTTON.pop_front();
                COTTON.push_back(currp);
            }
            if (COTTON.size() == 5)
            {
                for (auto x : COTTON)
                {
                    average_COTTON += x;
                }
                average_COTTON /= 5;
            }
            
        }
       deque<double>::iterator itr_GOLD;
       deque<double>::iterator itr_SILVER;
       deque<double>::iterator itr_CRUDEOIL;
       deque<double>::iterator itr_NATURALGAS;
       deque<double>::iterator itr_ALUMINIUM;
       deque<double>::iterator itr_COPPER;
       deque<double>::iterator itr_NICKEL;
       deque<double>::iterator itr_LEAD;
       deque<double>::iterator itr_ZINC;
       deque<double>::iterator itr_MENTHAOIL;
       deque<double>::iterator itr_COTTON;       
       itr_GOLD=GOLD.end()-2;
       itr_SILVER=SILVER.end()-2;
       itr_CRUDEOIL=CRUDOIL.end()-2;
       itr_NATURALGAS=NATURALGAS.end()-2;
       itr_ALUMINIUM=ALUMINIUM.end()-2;
       itr_COPPER=COPPER.end()-2;
       itr_NICKEL=NICKEL.end()-2;
       itr_LEAD=LEAD.end()-2;
       itr_ZINC=ZINC.end()-2;
       itr_MENTHAOIL=MENTHAOIL.end()-2;
       itr_COTTON=COTTON.end()-2;
        printf("\033[1;1H");
        cout<<"\n";
        cout << "+-------------------------------------+" << endl;
        cout << "| Currency      |  Price   | AvgPrice |" << endl;
        cout << "+-------------------------------------+" << endl;

                /****************************GOLD**************************************/
        if(GOLD.back()==0.00){
            cout << "| GOLD          |"<< " ";printf("\033[;34m%7.2lf\033[0m", (double)(GOLD.back()));cout << "  |"<< " ";
            if(average_GOLD==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_GOLD);cout << "  |" << endl;
            }
            else{
            if(average_GOLD>before_avarege_GOLD){
                printf("\033[;32m%7.2lf↑\033[0m", average_GOLD);cout << " |" << endl;}
            else if(average_GOLD==before_avarege_GOLD){
                printf("\033[;34m%7.2lf\033[0m", average_GOLD);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_GOLD);cout << " |" << endl;
            }
                }
        }
        else{
        if(GOLD.back()>*itr_GOLD){
            cout << "| GOLD          |"<< " ";printf("\033[;32m%7.2lf↑\033[0m", (double)(GOLD.back()));cout << " |"<< " ";
            if(average_GOLD==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_GOLD);cout << "  |" << endl;
            }
            else{
            if(average_GOLD>before_avarege_GOLD){
                printf("\033[;32m%7.2lf↑\033[0m", average_GOLD);cout << " |" << endl;}
            else if(average_GOLD==before_avarege_GOLD){
                printf("\033[;34m%7.2lf\033[0m", average_GOLD);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_GOLD);cout << " |" << endl;
            }
                }
        }
        else{
            cout << "| GOLD          |"<< " ";printf("\033[;31m%7.2lf↓\033[0m", (double)(GOLD.back()));cout << " |"<< " ";
            if(average_GOLD==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_GOLD);cout << "  |" << endl;
            }
            else{
            if(average_GOLD>before_avarege_GOLD){
                printf("\033[;32m%7.2lf↑\033[0m", average_GOLD);cout << " |" << endl;}
            else if(average_GOLD==before_avarege_GOLD){
                printf("\033[;34m%7.2lf\033[0m", average_GOLD);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_GOLD);cout << " |" << endl;
            }
                }
        }}
/*******************************************************************************************************/
        /****************************SILVER**************************************/
        if(SILVER.back()==0.00){
            cout << "| SILVER        |"<< " ";printf("\033[;34m%7.2lf\033[0m", (double)(SILVER.back()));cout << "  |"<< " ";
            if(average_SILVER==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_SILVER);cout << "  |" << endl;
            }
            else{
            if(average_SILVER>before_avarege_SILVER){
                printf("\033[;32m%7.2lf↑\033[0m", average_SILVER);cout << " |" << endl;}
            else if(average_SILVER==before_avarege_SILVER){
                printf("\033[;34m%7.2lf\033[0m", average_SILVER);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_SILVER);cout << " |" << endl;
            }
                }
        }
        else{
        if(SILVER.back()>*itr_SILVER){
            cout << "| SILVER        |"<< " ";printf("\033[;32m%7.2lf↑\033[0m", (double)(SILVER.back()));cout << " |"<< " ";
           if(average_SILVER==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_SILVER);cout << "  |" << endl;
            }
            else{
            if(average_SILVER>before_avarege_SILVER){
                printf("\033[;32m%7.2lf↑\033[0m", average_SILVER);cout << " |" << endl;}
            else if(average_SILVER==before_avarege_SILVER){
                printf("\033[;34m%7.2lf\033[0m", average_SILVER);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_SILVER);cout << " |" << endl;
            }
                }
        }
        else{
            cout << "| SILVER        |"<< " ";printf("\033[;31m%7.2lf↓\033[0m", (double)(SILVER.back()));cout << " |"<< " ";
            if(average_SILVER==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_SILVER);cout << "  |" << endl;
            }
            else{
            if(average_SILVER>before_avarege_SILVER){
                printf("\033[;32m%7.2lf↑\033[0m", average_SILVER);cout << " |" << endl;}
            else if(average_SILVER==before_avarege_SILVER){
                printf("\033[;34m%7.2lf\033[0m", average_SILVER);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_SILVER);cout << " |" << endl;
            }
                }
        }}
/*******************************************************************************************************/
        /****************************CRUDOIL**************************************/
        if(CRUDOIL.back()==0.00){
            cout << "| CRUDEOIL      |"<< " ";printf("\033[;34m%7.2lf\033[0m", (double)(CRUDOIL.back()));cout << "  |"<< " ";
            if(average_CRUDEOIL==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_CRUDEOIL);cout << "  |" << endl;
            }
            else{
            if(average_CRUDEOIL>before_avarege_CRUDEOIL){
                printf("\033[;32m%7.2lf↑\033[0m", average_CRUDEOIL);cout << " |" << endl;}
            else if(average_CRUDEOIL==before_avarege_CRUDEOIL){
                printf("\033[;34m%7.2lf\033[0m", average_CRUDEOIL);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_CRUDEOIL);cout << " |" << endl;
            }
                }
        }
        else{
        if(CRUDOIL.back()>*itr_CRUDEOIL){
            cout << "| CRUDEOIL      |"<< " ";printf("\033[;32m%7.2lf↑\033[0m", (double)(CRUDOIL.back()));cout << " |"<< " ";
            if(average_CRUDEOIL==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_CRUDEOIL);cout << "  |" << endl;
            }
            else{
            if(average_CRUDEOIL>before_avarege_CRUDEOIL){
                printf("\033[;32m%7.2lf↑\033[0m", average_CRUDEOIL);cout << " |" << endl;}
            else if(average_CRUDEOIL==before_avarege_CRUDEOIL){
                printf("\033[;34m%7.2lf\033[0m", average_CRUDEOIL);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_CRUDEOIL);cout << " |" << endl;
            }
                }
        }
        else{
            cout << "| CRUDEOIL      |"<< " ";printf("\033[;31m%7.2lf↓\033[0m", (double)(CRUDOIL.back()));cout << " |"<< " ";
            if(average_CRUDEOIL==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_CRUDEOIL);cout << "  |" << endl;
            }
            else{
            if(average_CRUDEOIL>before_avarege_CRUDEOIL){
                printf("\033[;32m%7.2lf↑\033[0m", average_CRUDEOIL);cout << " |" << endl;}
            else if(average_CRUDEOIL==before_avarege_CRUDEOIL){
                printf("\033[;34m%7.2lf\033[0m", average_CRUDEOIL);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_CRUDEOIL);cout << " |" << endl;
            }
                }
        }}
/*******************************************************************************************************/
        /****************************NATURALGAS**************************************/
        if(NATURALGAS.back()==0.00){
            cout << "| NATURALGAS    |"<< " ";printf("\033[;34m%7.2lf\033[0m", (double)(NATURALGAS.back()));cout << "  |"<< " ";
            if(average_NATURALGAS==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_NATURALGAS);cout << "  |" << endl;
            }
            else{
            if(average_NATURALGAS>before_avarege_NATURALGAS){
                printf("\033[;32m%7.2lf↑\033[0m", average_NATURALGAS);cout << " |" << endl;}
            else if(average_NATURALGAS==before_avarege_NATURALGAS){
                printf("\033[;34m%7.2lf\033[0m", average_NATURALGAS);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_NATURALGAS);cout << " |" << endl;
            }
                }
        }
        else{
        if(NATURALGAS.back()>*itr_NATURALGAS){
            cout << "| NATURALGAS    |"<< " ";printf("\033[;32m%7.2lf↑\033[0m", (double)(NATURALGAS.back()));cout << " |"<< " ";
              if(average_NATURALGAS==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_NATURALGAS);cout << "  |" << endl;
            }
            else{
            if(average_NATURALGAS>before_avarege_NATURALGAS){
                printf("\033[;32m%7.2lf↑\033[0m", average_NATURALGAS);cout << " |" << endl;}
            else if(average_NATURALGAS==before_avarege_NATURALGAS){
                printf("\033[;34m%7.2lf\033[0m", average_NATURALGAS);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_NATURALGAS);cout << " |" << endl;
            }
                }
        }
        else{
            cout << "| NATURALGAS    |"<< " ";printf("\033[;31m%7.2lf↓\033[0m", (double)(NATURALGAS.back()));cout << " |"<< " ";
             if(average_NATURALGAS==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_NATURALGAS);cout << "  |" << endl;
            }
            else{
            if(average_NATURALGAS>before_avarege_NATURALGAS){
                printf("\033[;32m%7.2lf↑\033[0m", average_NATURALGAS);cout << " |" << endl;}
            else if(average_NATURALGAS==before_avarege_NATURALGAS){
                printf("\033[;34m%7.2lf\033[0m", average_NATURALGAS);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_NATURALGAS);cout << " |" << endl;
            }
                }
        }}
/*******************************************************************************************************/
        /****************************ALUMINIUM**************************************/
        if(ALUMINIUM.back()==0.00){
            cout << "| ALUMINIUM     |"<< " ";printf("\033[;34m%7.2lf\033[0m", (double)(ALUMINIUM.back()));cout << "  |"<< " ";
            if(average_ALUMINIUM==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_ALUMINIUM);cout << "  |" << endl;
            }
            else{
            if(average_ALUMINIUM>before_avarege_ALUMINIUM){
                printf("\033[;32m%7.2lf↑\033[0m", average_ALUMINIUM);cout << " |" << endl;}
            else if(average_ALUMINIUM==before_avarege_ALUMINIUM){
                printf("\033[;34m%7.2lf\033[0m", average_ALUMINIUM);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_ALUMINIUM);cout << " |" << endl;
            }
                }
        }
        else{
        if(ALUMINIUM.back()>*itr_ALUMINIUM){
            cout << "| ALUMINIUM     |"<< " ";printf("\033[;32m%7.2lf↑\033[0m", (double)(ALUMINIUM.back()));cout << " |"<< " ";
            if(average_ALUMINIUM==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_ALUMINIUM);cout << "  |" << endl;
            }
            else{
            if(average_ALUMINIUM>before_avarege_ALUMINIUM){
                printf("\033[;32m%7.2lf↑\033[0m", average_ALUMINIUM);cout << " |" << endl;}
            else if(average_ALUMINIUM==before_avarege_ALUMINIUM){
                printf("\033[;34m%7.2lf\033[0m", average_ALUMINIUM);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_ALUMINIUM);cout << " |" << endl;
            }
                }
        }
        else{
            cout << "| ALUMINIUM     |"<< " ";printf("\033[;31m%7.2lf↓\033[0m", (double)(ALUMINIUM.back()));cout << " |"<< " ";
             if(average_ALUMINIUM==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_ALUMINIUM);cout << "  |" << endl;
            }
            else{
            if(average_ALUMINIUM>before_avarege_ALUMINIUM){
                printf("\033[;32m%7.2lf↑\033[0m", average_ALUMINIUM);cout << " |" << endl;}
            else if(average_ALUMINIUM==before_avarege_ALUMINIUM){
                printf("\033[;34m%7.2lf\033[0m", average_ALUMINIUM);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_ALUMINIUM);cout << " |" << endl;
            }
                }
        }}
/*******************************************************************************************************/
        /****************************COPPER**************************************/
        if(COPPER.back()==0.00){
            cout << "| COPPER        |"<< " ";printf("\033[;34m%7.2lf\033[0m", (double)(COPPER.back()));cout << "  |"<< " ";
            if(average_COPPER==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_COPPER);cout << "  |" << endl;
            }
            else{
            if(average_COPPER>before_avarege_COPPER){
                printf("\033[;32m%7.2lf↑\033[0m", average_COPPER);cout << " |" << endl;}
            else if(average_COPPER==before_avarege_COPPER){
                printf("\033[;34m%7.2lf\033[0m", average_COPPER);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_COPPER);cout << " |" << endl;
            }
                }
        }
        else{
        if(COPPER.back()>*itr_COPPER){
            cout << "| COPPER        |"<< " ";printf("\033[;32m%7.2lf↑\033[0m", (double)(COPPER.back()));cout << " |"<< " ";
            if(average_COPPER==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_COPPER);cout << "  |" << endl;
            }
            else{
            if(average_COPPER>before_avarege_COPPER){
                printf("\033[;32m%7.2lf↑\033[0m", average_COPPER);cout << " |" << endl;}
            else if(average_COPPER==before_avarege_COPPER){
                printf("\033[;34m%7.2lf\033[0m", average_COPPER);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_COPPER);cout << " |" << endl;
            }
                }
        }
        else{
            cout << "| COPPER        |"<< " ";printf("\033[;31m%7.2lf↓\033[0m", (double)(COPPER.back()));cout << " |"<< " ";
            if(average_COPPER==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_COPPER);cout << "  |" << endl;
            }
            else{
            if(average_COPPER>before_avarege_COPPER){
                printf("\033[;32m%7.2lf↑\033[0m", average_COPPER);cout << " |" << endl;}
            else if(average_COPPER==before_avarege_COPPER){
                printf("\033[;34m%7.2lf\033[0m", average_COPPER);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_COPPER);cout << " |" << endl;
            }
                }
        }}
/*******************************************************************************************************/

        /****************************NICKEL**************************************/
        if(NICKEL.back()==0.00){
            cout << "| NICKEL        |"<< " ";printf("\033[;34m%7.2lf\033[0m", (double)(NICKEL.back()));cout << "  |"<< " ";
            if(average_NICKEL==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_NICKEL);cout << "  |" << endl;
            }
            else{
            if(average_NICKEL>before_avarege_NICKEL){
                printf("\033[;32m%7.2lf↑\033[0m", average_NICKEL);cout << " |" << endl;}
            else if(average_NICKEL==before_avarege_NICKEL){
                printf("\033[;34m%7.2lf\033[0m", average_NICKEL);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_NICKEL);cout << " |" << endl;
            }
                }
        }
        else{
        if(NICKEL.back()>*itr_NICKEL){
            cout << "| NICKEL        |"<< " ";printf("\033[;32m%7.2lf↑\033[0m", (double)(NICKEL.back()));cout << " |"<< " ";
           if(average_NICKEL==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_NICKEL);cout << "  |" << endl;
            }
            else{
            if(average_NICKEL>before_avarege_NICKEL){
                printf("\033[;32m%7.2lf↑\033[0m", average_NICKEL);cout << " |" << endl;}
            else if(average_NICKEL==before_avarege_NICKEL){
                printf("\033[;34m%7.2lf\033[0m", average_NICKEL);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_NICKEL);cout << " |" << endl;
            }
                }
        }
        else{
            cout << "| NICKEL        |"<< " ";printf("\033[;31m%7.2lf↓\033[0m", (double)(NICKEL.back()));cout << " |"<< " ";
            if(average_NICKEL==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_NICKEL);cout << "  |" << endl;
            }
            else{
            if(average_NICKEL>before_avarege_NICKEL){
                printf("\033[;32m%7.2lf↑\033[0m", average_NICKEL);cout << " |" << endl;}
            else if(average_NICKEL==before_avarege_NICKEL){
                printf("\033[;34m%7.2lf\033[0m", average_NICKEL);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_NICKEL);cout << " |" << endl;
            }
                }
        }}
/*******************************************************************************************************/
        /****************************LEAD**************************************/
        if(LEAD.back()==0.00){
            cout << "| LEAD          |"<< " ";printf("\033[;34m%7.2lf\033[0m", (double)(LEAD.back()));cout << "  |"<< " ";
            if(average_LEAD==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_LEAD);cout << "  |" << endl;
            }
            else{
            if(average_LEAD>before_avarege_LEAD){
                printf("\033[;32m%7.2lf↑\033[0m", average_LEAD);cout << " |" << endl;}
            else if(average_LEAD==before_avarege_LEAD){
                printf("\033[;34m%7.2lf\033[0m", average_LEAD);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_LEAD);cout << " |" << endl;
            }
                }
        }
        else{
        if(LEAD.back()>*itr_LEAD){
            cout << "| LEAD          |"<< " ";printf("\033[;32m%7.2lf↑\033[0m", (double)(LEAD.back()));cout << " |"<< " ";
            if(average_LEAD==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_LEAD);cout << "  |" << endl;
            }
            else{
            if(average_LEAD>before_avarege_LEAD){
                printf("\033[;32m%7.2lf↑\033[0m", average_LEAD);cout << " |" << endl;}
            else if(average_LEAD==before_avarege_LEAD){
                printf("\033[;34m%7.2lf\033[0m", average_LEAD);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_LEAD);cout << " |" << endl;
            }
                }
        }
        else{
            cout << "| LEAD          |"<< " ";printf("\033[;31m%7.2lf↓\033[0m", (double)(LEAD.back()));cout << " |"<< " ";
            if(average_LEAD==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_LEAD);cout << "  |" << endl;
            }
            else{
            if(average_LEAD>before_avarege_LEAD){
                printf("\033[;32m%7.2lf↑\033[0m", average_LEAD);cout << " |" << endl;}
            else if(average_LEAD==before_avarege_LEAD){
                printf("\033[;34m%7.2lf\033[0m", average_LEAD);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_LEAD);cout << " |" << endl;
            }
                }
        }}
/*******************************************************************************************************/
        /****************************ZINC**************************************/
        if(ZINC.back()==0.00){
            cout << "| ZINC          |"<< " ";printf("\033[;34m%7.2lf\033[0m", (double)(ZINC.back()));cout << "  |"<< " ";
            if(average_ZINC==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_ZINC);cout << "  |" << endl;
            }
            else{
            if(average_ZINC>before_avarege_ZINC){
                printf("\033[;32m%7.2lf↑\033[0m", average_ZINC);cout << " |" << endl;}
            else if(average_ZINC==before_avarege_ZINC){
                printf("\033[;34m%7.2lf\033[0m", average_ZINC);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_ZINC);cout << " |" << endl;
            }
                }
        }
        else{
        if(ZINC.back()>*itr_ZINC){
            cout << "| ZINC          |"<< " ";printf("\033[;32m%7.2lf↑\033[0m", (double)(ZINC.back()));cout << " |"<< " ";
            if(average_ZINC==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_ZINC);cout << "  |" << endl;
            }
            else{
            if(average_ZINC>before_avarege_ZINC){
                printf("\033[;32m%7.2lf↑\033[0m", average_ZINC);cout << " |" << endl;}
            else if(average_ZINC==before_avarege_ZINC){
                printf("\033[;34m%7.2lf\033[0m", average_ZINC);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_ZINC);cout << " |" << endl;
            }
                }
        }
        else{
            cout << "| ZINC          |"<< " ";printf("\033[;31m%7.2lf↓\033[0m", (double)(ZINC.back()));cout << " |"<< " ";
           if(average_ZINC==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_ZINC);cout << "  |" << endl;
            }
            else{
            if(average_ZINC>before_avarege_ZINC){
                printf("\033[;32m%7.2lf↑\033[0m", average_ZINC);cout << " |" << endl;}
            else if(average_ZINC==before_avarege_ZINC){
                printf("\033[;34m%7.2lf\033[0m", average_ZINC);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_ZINC);cout << " |" << endl;
            }
                }
        }}
/*******************************************************************************************************/
        /****************************MENTHAOIL**************************************/
        if(MENTHAOIL.back()==0.00){
            cout << "| MENTHAOIL     |"<< " ";printf("\033[;34m%7.2lf\033[0m", (double)(MENTHAOIL.back()));cout << "  |"<< " ";
            if(average_MENTHAOIL==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_MENTHAOIL);cout << "  |" << endl;
            }
            else{
            if(average_MENTHAOIL>before_avarege_MENTHAOIL){
                printf("\033[;32m%7.2lf↑\033[0m", average_MENTHAOIL);cout << " |" << endl;}
            else if(average_MENTHAOIL==before_avarege_MENTHAOIL){
                printf("\033[;34m%7.2lf\033[0m", average_MENTHAOIL);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_MENTHAOIL);cout << " |" << endl;
            }
                }
        }
        else{
        if(MENTHAOIL.back()>*itr_MENTHAOIL){
            cout << "| MENTHAOIL     |"<< " ";printf("\033[;32m%7.2lf↑\033[0m", (double)(MENTHAOIL.back()));cout << " |"<< " ";
           if(average_MENTHAOIL==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_MENTHAOIL);cout << "  |" << endl;
            }
            else{
            if(average_MENTHAOIL>before_avarege_MENTHAOIL){
                printf("\033[;32m%7.2lf↑\033[0m", average_MENTHAOIL);cout << " |" << endl;}
            else if(average_MENTHAOIL==before_avarege_MENTHAOIL){
                printf("\033[;34m%7.2lf\033[0m", average_MENTHAOIL);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_MENTHAOIL);cout << " |" << endl;
            }
                }
        }
        else{
            cout << "| MENTHAOIL     |"<< " ";printf("\033[;31m%7.2lf↓\033[0m", (double)(MENTHAOIL.back()));cout << " |"<< " ";
            if(average_MENTHAOIL==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_MENTHAOIL);cout << "  |" << endl;
            }
            else{
            if(average_MENTHAOIL>before_avarege_MENTHAOIL){
                printf("\033[;32m%7.2lf↑\033[0m", average_MENTHAOIL);cout << " |" << endl;}
            else if(average_MENTHAOIL==before_avarege_MENTHAOIL){
                printf("\033[;34m%7.2lf\033[0m", average_MENTHAOIL);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_MENTHAOIL);cout << " |" << endl;
            }
                }
        }}
/*******************************************************************************************************/
        /****************************COTTON**************************************/
        if(COTTON.back()==0.00){
           cout << "| COTTON        |"<< " ";printf("\033[;34m%7.2lf\033[0m", (double)(COTTON.back()));cout << "  |"<< " ";
            if(average_COTTON==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_COTTON);cout << "  |" << endl;
            }
            else{
            if(average_COTTON>before_avarege_COTTON){
                printf("\033[;32m%7.2lf↑\033[0m", average_COTTON);cout << " |" << endl;}
            else if(average_COTTON==before_avarege_COTTON){
                printf("\033[;34m%7.2lf\033[0m", average_COTTON);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_COTTON);cout << " |" << endl;
            }
                }
        }
        else{
        if(COTTON.back()>*itr_COTTON){
            cout << "| COTTON        |"<< " ";printf("\033[;32m%7.2lf↑\033[0m", (double)(COTTON.back()));cout << " |"<< " ";
            if(average_COTTON==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_COTTON);cout << "  |" << endl;
            }
            else{
            if(average_COTTON>before_avarege_COTTON){
                printf("\033[;32m%7.2lf↑\033[0m", average_COTTON);cout << " |" << endl;}
            else if(average_COTTON==before_avarege_COTTON){
                printf("\033[;34m%7.2lf\033[0m", average_COTTON);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_COTTON);cout << " |" << endl;
            }
                }
        }
        else{
            cout << "| COTTON        |"<< " ";printf("\033[;31m%7.2lf↓\033[0m", (double)(COTTON.back()));cout << " |"<< " ";
            if(average_COTTON==0.00){
                printf("\033[;34m%7.2lf\033[0m", average_COTTON);cout << "  |" << endl;
            }
            else{
            if(average_COTTON>before_avarege_COTTON){
                printf("\033[;32m%7.2lf↑\033[0m", average_COTTON);cout << " |" << endl;}
            else if(average_COTTON==before_avarege_COTTON){
                printf("\033[;34m%7.2lf\033[0m", average_COTTON);cout << "  |" << endl;}
            
            else{
                printf("\033[;31m%7.2lf↓\033[0m", average_COTTON);cout << " |" << endl;
            }
                }
        }}
/*******************************************************************************************************/

        cout << "+-------------------------------------+" << endl;
        // end printing
        sem[0].sem_op = 1;
        if (semop(s, sem, 1) == -1)
        {
            perror("ERR Semop");
            exit(1);
        }
        if (semop(e, sem, 1) == -1)
        {
            perror("ERR Semop");
            exit(1);
        }
    }
    // detach from shared memory
    shmdt(coms);
    // destroy the shared memory
    return 0;
}
