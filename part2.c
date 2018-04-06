/*
 ----------------- COMP 310/ECSE 427 Winter 2018 -----------------
 Assignment 3  part 2
 
 -----------------------------------------------------------------
 I declare that the awesomeness below is a genuine piece of work
 and falls under the McGill code of conduct, to the best of my knowledge.
 -----------------------------------------------------------------
 */

//Please enter your name and McGill ID below
//Name: Xi Meng Huang
//McGill ID: 260608596


#include <stdio.h>  //for printf and scanf
#include <stdlib.h> //for malloc

#define LOW 0
#define HIGH 199
#define START 53

//compare function for qsort
//you might have to sort the request array
//use the qsort function 
// an argument to qsort function is a function that compares 2 quantities
//use this there.
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

//function to swap 2 integers
void swap(int *a, int *b)
{
    if (*a != *b)
    {
        *a = (*a ^ *b);
        *b = (*a ^ *b);
        *a = (*a ^ *b);
        return;
    }
}

//Prints the sequence and the performance metric
void printSeqNPerformance(int *request, int numRequest)
{
    int i, last, acc = 0;
    last = START;
    printf("\n");
    printf("%d", START);
    for (i = 0; i < numRequest; i++)
    {
        printf(" -> %d", request[i]);
        acc += abs(last - request[i]);
        last = request[i];
    }
    printf("\nPerformance : %d\n", acc);
    return;
}

//access the disk location in FCFS
void accessFCFS(int *request, int numRequest)
{
    //simplest part of assignment
    printf("\n----------------\n");
    printf("FCFS :");
    printSeqNPerformance(request, numRequest);
    printf("----------------\n");
    return;
}

//access the disk location in SSTF
void accessSSTF(int *request, int numRequest)
{
    int *diff, i, j;
    //initializing a new array to keep track of the differences
    diff = malloc(numRequest * sizeof(int));

    for(i = 0;i<numRequest;i++){
        diff[i]=abs(START - request[i]);
    }

    for(i = 0; i< numRequest; i++){
        for(j = i+1; j<numRequest; j++){
            //bubble this up
            if(diff[i] > diff[j]){
                swap(&diff[i],&diff[j]);
                swap(&request[i],&request[j]);
            }
        }
    }

    printf("\n----------------\n");
    printf("SSTF :");
    printSeqNPerformance(request, numRequest);
    printf("----------------\n");
    return;
}

//access the disk location in SCAN
void accessSCAN(int *request, int numRequest)
{
    int *newRequest, newCnt=numRequest+1, i, j=0;
    //decrease the count if one of the requests actually has a 0 or a 199 track, otherwise
    //assume it will be one more to account for the 0 transition
    for(i=0;i<numRequest;i++){
        if(request[i] == LOW || request[i] == HIGH){
            newCnt--;
        }
    }
    newRequest = malloc(newCnt * sizeof(int));
    
    qsort(request,numRequest,sizeof(int),cmpfunc);

    int indexOfStart;
    for(i=0;i<numRequest-1;i++){
        if(request[i] < START && request[i+1] > START){
            indexOfStart = i;
        }
    }
    //go right to left for the smaller elements
    for(i=indexOfStart;i>=0;i--){
        newRequest[j] = request[i];
        j++;
    }
    //reaches the end
    newRequest[j] = 0;
    j++;
    //go left to right for the larger elements
    for(i=indexOfStart+1;i<numRequest;i++){
        newRequest[j] = request[i];
        j++;
    }

    printf("\n----------------\n");
    printf("SCAN :");
    printSeqNPerformance(newRequest, newCnt);
    printf("----------------\n");
    return;
}

//access the disk location in CSCAN
void accessCSCAN(int *request, int numRequest)
{
    int *newRequest, newCnt = numRequest + 2, i, j=0;
    //decrease the count if one of the requests actually has a 0 or a 199 track, otherwise
    //assume it will be two more to account for the 199 transition to 0 begin
    for(i=0;i<numRequest;i++){
        if(request[i] == LOW || request[i] == HIGH){
            newCnt--;
        }
    }
    newRequest = malloc(newCnt * sizeof(int));
    
    qsort(request,numRequest,sizeof(int),cmpfunc);

    int indexOfStart;
    for(i=0;i<numRequest-1;i++){
        if(request[i] < START && request[i+1] > START){
            indexOfStart = i;
        }
    }

    //go left to right for the larger elements
    for(i=indexOfStart+1;i<numRequest;i++){
        newRequest[j] = request[i];
        j++;
    }
    //reaches the end
    newRequest[j] = 199;
    j++;
    //start back at the beginning
    newRequest[j] = 0;
    j++;
    //go left to right for the smaller elements
    for(i=0;i<=indexOfStart;i++){
        newRequest[j] = request[i];
        j++;
    }
    
    
    printf("\n----------------\n");
    printf("CSCAN :");
    printSeqNPerformance(newRequest, newCnt);
    printf("----------------\n");
    return;
}

//access the disk location in LOOK
void accessLOOK(int *request, int numRequest)
{
    int *newRequest, newCnt=numRequest, i, j=0;
    //decrease the count if one of the requests actually has a 0 or a 199 track, otherwise
    newRequest = malloc(newCnt * sizeof(int));
    
    qsort(request,numRequest,sizeof(int),cmpfunc);

    int indexOfStart;
    for(i=0;i<numRequest-1;i++){
        if(request[i] < START && request[i+1] > START){
            indexOfStart = i;
        }
    }
    
    //go left to right for the larger elements
    for(i=indexOfStart+1;i<numRequest;i++){
        newRequest[j] = request[i];
        j++;
    }
     //go right to left for the smaller elements
    for(i=indexOfStart;i>=0;i--){
        newRequest[j] = request[i];
        j++;
    }

    printf("\n----------------\n");
    printf("LOOK :");
    printSeqNPerformance(newRequest, newCnt);
    printf("----------------\n");
    return;
}

//access the disk location in CLOOK
void accessCLOOK(int *request, int numRequest)
{
    int *newRequest, newCnt=numRequest+2, i, j=0;
    //decrease the count if one of the requests actually has a 0 or a 199 track, otherwise
    //assume it will be two more to account for the 199 and 0 transition

    newRequest = malloc(newCnt * sizeof(int));
    
    qsort(request,numRequest,sizeof(int),cmpfunc);

    int indexOfStart;
    for(i=0;i<numRequest-1;i++){
        if(request[i] < START && request[i+1] > START){
            indexOfStart = i;
        }
    }
    
    //go left to right for the larger elements
    for(i=indexOfStart+1;i<numRequest;i++){
        newRequest[j] = request[i];
        j++;
    }
    //reaches the end
    newRequest[j] = 199;
    j++;

    //start back at the beginning
    newRequest[j] = 0;
    j++;
    //go left to right for the smaller elements
    for(i=0;i<=indexOfStart;i++){
        newRequest[j] = request[i];
        j++;
    }

    printf("\n----------------\n");
    printf("CLOOK :");
    printSeqNPerformance(newRequest, newCnt);
    printf("----------------\n");
    return;
}

int main()
{
    int *request, numRequest, i,ans;

    //allocate memory to store requests
    printf("Enter the number of disk access requests : ");
    scanf("%d", &numRequest);
    request = malloc(numRequest * sizeof(int));

    printf("Enter the requests ranging between %d and %d\n", LOW, HIGH);
    for (i = 0; i < numRequest; i++)
    {
        scanf("%d", &request[i]);
    }

    printf("\nSelect the policy : \n");
    printf("----------------\n");
    printf("1\t FCFS\n");
    printf("2\t SSTF\n");
    printf("3\t SCAN\n");
    printf("4\t CSCAN\n");
    printf("5\t LOOK\n");
    printf("6\t CLOOK\n");
    printf("----------------\n");
    scanf("%d",&ans);

    switch (ans)
    {
    //access the disk location in FCFS
    case 1: accessFCFS(request, numRequest);
        break;

    //access the disk location in SSTF
    case 2: accessSSTF(request, numRequest);
        break;

        //access the disk location in SCAN
     case 3: accessSCAN(request, numRequest);
        break;

        //access the disk location in CSCAN
    case 4: accessCSCAN(request,numRequest);
        break;

    //access the disk location in LOOK
    case 5: accessLOOK(request,numRequest);
        break;

    //access the disk location in CLOOK
    case 6: accessCLOOK(request,numRequest);
        break;

    default:
        break;
    }
    return 0;
}