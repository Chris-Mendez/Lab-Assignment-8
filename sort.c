#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void max_heapify(int arr[], int i, int n)
{
  int temp, max;
  int l = (2 * i) + 1;//finds left node of the parent node
  int r = (2 * i) + 2;//finds right node of the parent node

  if((l <= n) && (arr[l] > arr[i]))//if left node is larger than parent node
    max = l;//parent node becomes left node
  else
    max = i;

  if((r <= n) && (arr[r] > arr[max]))//if right node is larger than parent node
    max = r;//parent node becomes right node

  if(max != i)//if largest node is not the parent node
  {
    temp = arr[i];
    arr[i] = arr[max];
    arr[max] = temp;
    max_heapify(arr, max, n);
  }
}

void build_max_heap(int arr[], int n)
{
  int i;
  for(i = n/2;i >= 0; i--)
    {
      max_heapify(arr, i, n);
    }
}

void heapSort(int arr[], int n)
{
  int i, temp;
  
  build_max_heap(arr, n);

  for(i = n;i>0;i--)
    {
      temp = arr[i];
      arr[i] = arr[0];
      arr[0] = temp;
      n--;

      max_heapify(arr, 0, n);
    }
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int pData[], int l, int m, int r)
{
  for(int j = 0; j<r;j++){
    
  }
  int i, j, k;
  int left_len = m - l + 1;
  int right_len = r - m;

  int *L = (int*) malloc(left_len*sizeof(int));
  extraMemoryAllocated += sizeof(L);
  
  int *R = (int*) malloc(right_len*sizeof(int));
  extraMemoryAllocated += sizeof(R);
  
  for (i = 0; i < left_len; i++)
    L[i] = pData[l + i];
  
  for (j = 0; j < right_len; j++)
    R[j] = pData[m + 1+ j];

  i = 0; 
  j = 0; 
  k = l;
  
  while (i < left_len && j < right_len)
  {
    if (L[i] <= R[j])
    {
      pData[k] = L[i];
      i++;
    }
    else
    {
      pData[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < left_len)
  {
    pData[k] = L[i];
    i++;
    k++;
  }

  while (j < right_len)
  {
    pData[k] = R[j];
    j++;
    k++;
  }
  free(L);
  free(R);
}

void mergeSort(int pData[], int l, int r)
{
  if (l < r)
  {
    int m = (l+r)/2;

    mergeSort(pData, l, m);
    mergeSort(pData, m+1, r);
    merge(pData, l, m, r);
  }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
    if(i >= dataSz){
    printf("\n\n");
    return;
}
    else
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}
