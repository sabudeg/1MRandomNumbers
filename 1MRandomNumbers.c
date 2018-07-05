#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct RunnerArgs {
   int argsName;	
   int start;
   int end;
};

int control();
void createUnsortedDat();
void createSortedDat();
void printArray();
void *runner(void *params); 
void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);
int N[1000000];
int NUMBER = 1000000;


struct 	RunnerArgs args0,args1,args2,args3,args4,args5,args6,args7;
pthread_t th0,th1,th2,th3,th4,th5,th6,th7; /* the thread identifier */
pthread_attr_t attr; /* set of attributes for the thread */

int main(int argc, char *argv[]){

	
	int i = 0;
        //Rastgele sayı üretme
        srand(time(NULL));  //farklı sayı üretir
        for(i=0;i<1000000;i++){N[i] = rand()%1000000;}
	
		
	createUnsortedDat();
	
	
	args0.argsName=0;
	args0.start=0;
	args0.end=124999;
	
	args1.argsName=1;
	args1.start=125000;
	args1.end=249999;
	
	args2.argsName=2;
	args2.start=250000;
	args2.end=374999;
	
	args3.argsName=3;
	args3.start=375000;
	args3.end=499999;
	
	args4.argsName=4;
	args4.start=500000;
	args4.end=624999;
	
	args5.argsName=5;
	args5.start=625000;
	args5.end=749999;
	
	args6.argsName=6;
	args6.start=750000;
	args6.end=874999;
	
	args7.argsName=7;
	args7.start=875000;
	args7.end=999999;

	
	pthread_attr_init(&attr);

	
	 pthread_create(&th0,&attr,runner,(void *)&args0);
	printf("th0 is created\n");
	 pthread_create(&th1,&attr,runner,(void *)&args1);
	printf("th1 is created\n");
	 pthread_create(&th2,&attr,runner,(void *)&args2);
	printf("th2 is created\n");
	 pthread_create(&th3,&attr,runner,(void *)&args3);
	printf("th3 is created\n");
	 pthread_create(&th4,&attr,runner,(void *)&args4);
	printf("th4 is created\n");
	 pthread_create(&th5,&attr,runner,(void *)&args5);
	printf("th5 is created\n");
	 pthread_create(&th6,&attr,runner,(void *)&args6);
	printf("th6 is created\n");
	 pthread_create(&th7,&attr,runner,(void *)&args7);
	printf("th7 is created\n");
	 
	pthread_join(th0,NULL);
	printf("th0 has joined\n");
	
	
	createSortedDat();

/*	printArray();	*/	

	control();
	
	
return 0;	
}



void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}

void *runner(void *params) 
{
	struct RunnerArgs *args0 = (struct RunnerArgs *)params;
	int start = args0 -> start;
	int end = args0 -> end;
	int argsName =	args0 -> argsName;
	
	mergeSort(N, start, end);	
	printf("Argument = %d start = %d end = %d (completed)\n",argsName,start,end);
		
		if(argsName==0){
    	 pthread_join(th1,NULL);
    	 	merge(N,start,args1.start,args1.end);
    	 pthread_join(th2,NULL); 
    		merge(N,args2.start,args2.start,args3.end);
	 pthread_join(th6,NULL);
		merge(N,args6.start,args6.start,args7.end);
    	 pthread_join(th4,NULL);
		merge(N,start,args3.end,args7.end);
	
}
	
		if(argsName==2){
			pthread_join(th3,NULL);
		merge(N,args2.start,args3.start,args3.end);		
		}
		if(argsName==4){
			pthread_join(th5,NULL);		
			pthread_join(th6,NULL);
		merge(N,args5.start,args5.start,args6.end);
		}
		if(argsName==6){
			pthread_join(th7,NULL);
		}
}


/* void printArray(){
	int loop;
   for(loop = 0; loop < 1000000; loop++){
   printf("%d ", N[loop]); }
} */

void createUnsortedDat(){
int x = 1;
    FILE *fh = fopen ("1MRandomNumber.dat", "wb");
    if (fh != NULL) {
        fwrite (N, 1000000, 1, fh);
        fclose (fh);
		printf("\n1000000 Numbers have written\n");
    }
}

void createSortedDat(){
int x = 1;
    FILE *fh = fopen ("1MRandomNumberSorted.dat", "wb");
    if (fh != NULL) {
        fwrite (N, 1000000, 1, fh);
        fclose (fh);
		printf("\n1000000 Sorted Numbers has written.\n");
    }

} 


int control(){
	FILE *fp = fopen("1MRandomNumberSorted.dat","rb");
	int i,next=1;
	
	if(fp==NULL){
		printf("File couldn't be opened!\n");
		return -1;
 	}

	for(i=0;i<NUMBER-1;i++,next++){
		fread(&i,sizeof(int),1,fp);
		fread(&next,sizeof(int),1,fp);
		if(i>next){
			fclose(fp);
			printf("\nunsuccessful\n");
			return -1;
		}
	}
	fclose(fp);
	printf("\nsuccessful\n");
	return 1;
}
