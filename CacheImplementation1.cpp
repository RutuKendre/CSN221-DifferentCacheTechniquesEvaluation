#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
using namespace std;
int main_memory[32][3];
int cache[8][4];
int input[1024][10];
	int k=2;
	int hits=0;
	int tag=0;
	int set_index=0;
	int no_of_sets=0;
	int start=0;
	int replace_index=0;
	int mx=0;
	bool check=false;


bool isempty(int start,int k)
{
    for (int i=start ;i<start+k  ;i++)
        if (cache[i][3]==0)return true;
    return false;
}

void LRU(int start,int k,int mm_index,int mx)
{
    int index=start;int mn=cache[start][3];
    for (int i=start+1 ; i<start+k  ;i++)
    {
                 if (cache[i][3]<mn){mn=cache[i][3]; index=i;}
    }
    mx++;
    cache[index][3]=mx;
    for (int i=0 ; i<3 ;i++)
        cache[index][i]=main_memory[mm_index][i];

}

int mm_search(int val)
{
    for (int i=0 ;i<32  ;i++)
        {
            for (int j=1  ; j<3   ;j++)
                if (main_memory[i][j]==val)return i;
        }
    return 0;
}

void cache_simulate(int ii,int total_inputs)
{
    using namespace std::chrono;
     high_resolution_clock::time_point t1 = high_resolution_clock::now();

	no_of_sets=8/k;
	
	hits =0;
	for (int inp=0  ; inp <total_inputs ; inp++)
    {
        tag=(input[inp][ii]+1)/2;
        set_index = (((tag-1)%8+1)-1)/k+1;
        start=(set_index-1)*k;
        check=false;
        for (int j=start  ; j<start+k  ;j++)
        {
            if (cache[j][0]==tag)
                {
                   hits++;
                   mx++;
                   cache[j][3]=mx;
                   check=true;
                   break;
                }
        }
        if (!check)
                {
                     replace_index=mm_search(input[inp][ii]);
                     LRU(start,k,replace_index,mx);
                }
    }
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	double hit_rate=hits/(total_inputs*1.0);

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    cout<<"k is "<<k<<endl;

    std::cout << "Time taken: " << time_span.count() << " seconds.";
    std::cout << std::endl;

	printf("Hit rate is %f\n", hit_rate);
	

}

void create_input()
{
    for(int i=0 ; i<10 ; i++)
    {
        for(int j=0 ; j<1024 ; j++)
        {
            if(1024/(pow(2,i)) <= j) input[j][i] = input[j-(1024/int(pow(2,i)))][i];
            else input[j][i] = rand()%64 + 1;
        }
    }

}

int main()
{
   using namespace std::chrono;
   //1 column will be for tag
   int val=1;
   for (int i=0 ; i<32 ; i++)
   {
       for (int j=1 ; j<3  ;j++)
       {
           main_memory[i][j]=val;
           val++;
       }
       main_memory[i][0]=i+1;
   }

   create_input();
   for ( k=1 ; k<=8  ; k=k*2)
   for (int ii=0 ; ii<10  ;ii++)
   { 
   	  cout<<"repition of elements is :"<<ii<<" times"<<endl;
   	   cache_simulate(ii,1024);
   }
   
   cout<<"testing on the basis of data size"<<endl;
   
   for (k=1 ; k<=8  ; k=k*2)
   for (int input_size=16  ;input_size<=1024  ; input_size*=2)
   {
   	cout<<"data size is :"<<input_size<<endl;
   	 cache_simulate(0,input_size);
   }
    return 0;
}



