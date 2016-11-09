#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef int index;

void seqsearch(int n, const int S[], int x, index* loc){
	*loc = 0;
	while(*loc < n && S[*loc] != x) (*loc)++;
	if(*loc > n) *loc = -1;
}
void binsearch(int n, const int S[], int x, index* loc){
	index low, high, mid;
	low = 0;
	high = n-1;
	*loc = -1;
	while(low <= high && *loc == -1) {
		mid = (low + high) / 2;
		if (x == S[mid]) *loc = mid;
		else if (x < S[mid]) high = mid - 1;
		else low = mid + 1;
	}
}
int fibit(int n){
	index i;
	int f[n+1];

	f[0] = 0;
	if (n > 0) {
		f[1] = 1;
		for( i = 2; i <= n; i++)
			f[i] = f[i-1] + f[i-2];
	}
	return f[n];
}
int fibre(int n){
	if(n <= 1)
		return n;
	else 
		return fibre(n-1) + fibre(n-2);
}
void merge(int h, int m, const int U[], const int V[], int S[]){
	index i = 0, j = 0, k = 0;
	while(i < h && j < m) {
		if(U[i] < V[j]) {
			S[k] = U[i];
			i++;
		}else {
			S[k] = V[j];
			j++;
		}
		k++;
	}
	if(i >= h)
		for(;k < h+m; k++,j++)
			S[k] = V[j];
	else
		for(;k < h+m; k++, i++)
			S[k] = U[i];
}
void mergesort(int n, int S[]){
	if(n > 1){
		const int h = n/2, m = n - h;
		int U[h], V[m];

		for(int i = 0; i < h; i++)
			U[i] = S[i];
		for(int i = h; i < n; i++)
			V[i-h] = S[i];
		mergesort (h, U);
		mergesort (m, V);
		merge(h, m, U, V, S);
	}
}
void partition (index low, index high, index* pivotpoint, int S[]) {
	index i, j;
	int pivotitem;

	pivotitem = S[low];
	j = low;
	for(i = low + 1; i <= high; i++)
		if(S[i] < pivotitem){
			j++;
			int temp;
			temp = S[i];
			S[i] = S[j];
			S[j] = temp;
		}
	*pivotpoint = j;
	{
		int temp;
		temp = S[low];
		S[low] = S[*pivotpoint];
		S[*pivotpoint] = temp;
	}
}
void quicksort (index low, index high, int S[]) {
	index pivotpoint;

	if (high > low) {
		partition(low, high, &pivotpoint, S);
		quicksort(low, pivotpoint - 1, S);
		quicksort(pivotpoint + 1, high, S);
	}
}
void reset (int n, int S[]){
	for(int i = 0; i < n; i++)
		S[i] = rand()%100000;
}
int main(){
	clock_t start, end;
	srand(time(NULL));
	{
		int arr[300000];
		for(int i = 0; i < 300000; i++)
		arr[i] = i;
		int sc[5], bc[5];
		index loc;
		for(int i = 0; i < 5; i++){
			start = clock();
			seqsearch(300000,arr,i*70000,&loc);
			end = clock();
			sc[i] = end - start;
		}
		for(int i = 0; i < 5; i++){
			start = clock();
			binsearch(300000,arr,i*70000,&loc);
			end = clock();
			bc[i] = end - start;
		}
		printf("find	seqsearch	binsearch\n");
		for(int i = 0; i < 5; i++)
			printf("%dK	%3d clock	%3d clock\n",i*70,sc[i],bc[i]);
	}
	printf("\n");
	{
		int itc[5], rec[5];
		for(int i = 0; i < 5; i++){
			start = clock();
			fibit((i+1)*8);
			end = clock();
			itc[i] = end - start;
		}
		for(int i = 0; i < 5; i++){
			start = clock();
			fibre((i+1)*8);
			end = clock();
			rec[i] = end - start;
		}
		printf("num	fibit		fibre\n");
		for(int i = 0; i < 5; i++)
			printf("%d	%d clock		%d clock\n",(i+1)*8,itc[i],rec[i]);
	}
	printf("\n");
	{
		int arr[5000];
		int mc[5], qc[5];
		for(int i = 0; i < 5; i++){
			reset((i+1)*1000,arr);
			start = clock();
			mergesort((i+1)*1000,arr);
			end = clock();
			mc[i] = end - start;
		}
		for(int i = 0; i < 5; i++){
			reset((i+1)*1000,arr);
			start = clock();
			quicksort(0,(i+1)*1000,arr);
			end = clock();
			qc[i] = end - start;
		}
		printf("size	merge	quick\n");
		for(int i = 0 ; i < 5; i++)
			printf("%d	%d clock	%d clock\n",(i+1)*1000,mc[i],qc[i]);
	}
}
