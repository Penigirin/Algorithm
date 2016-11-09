#include<stdio.h>
#include<stdlib.h>

int Pow(int n, int p){
	int sum = 1;
	for(int i = 0; i < p; i++)
		sum *= n;
	return sum;
}
int bitnum(int n, int A){
	int b=0;
	for(int i = 0; i < n; i++)
		if((A>>=1)&1) b++;
	return b;
}
void travel(int n, int W[][n], short P[][Pow(2,n)], int *minlength){
	int D[n][Pow(2,n)];
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < Pow(2,n); j++)
			D[i][j] = 99;

	for(short i = 1; i < n; i++)
		D[i][0] = W[i][0];

	for(short k = 1; k <= n-2; k++)
		for(int A = 2; A < Pow(2,n); A+=2){
			if(bitnum(n,A) == k){
				for(int i = 1; i < n; i++)
					if(!(Pow(2,i) & A))
					{
						int tmp = 999;
						int x = 1;
						for(int j = 1; j < n; j++)
							if((i != j) && (Pow(2,j) & A))
								if(tmp > W[i][j] + D[j][A-Pow(2,j)]){
									tmp = W[i][j] + D[j][A-Pow(2,j)];
									x = j;
								}
						D[i][A] = tmp;
						P[i][A] = x;
					}
			}
		}
		{
			int A = Pow(2,n) -1 -1;
			int tmp = 999;
			int x = 1;
			for(int j = 1; j < n; j++)
				if((j != 0) && (Pow(2,j) & A))
					if(tmp > W[0][j] + D[j][A-Pow(2,j)]){
						tmp = W[0][j] + D[j][A-Pow(2,j)];
						x = j;
					}
			D[0][A] = tmp;
			P[0][A] = x;
			*minlength = D[0][A];
		}
}

int main(){
	int *min;
	int n;
	min = (int *)malloc(sizeof(int));

	printf("input n : ");
	scanf("%d",&n);

	int W[n][n];
	short P[n][Pow(2,n)];
	for(int i = 0; i < n; i++)
		for(int j = 0; j < Pow(2,n); j++)
			P[i][j] = 0;
	printf("input W[n][n](inf = -1) :\n");
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			scanf("%d",&W[i][j]);

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			if(W[i][j] == -1) W[i][j] = 99;

	travel(n,W,P,min);
	printf("minlength : %d\n",*min);
	printf("Path :");
	{
		int tmp = 0, tmp2 = Pow(2,4) -1 -1;
		for(int i = 0; i < n; i++){
			printf("-> %d ",P[tmp][tmp2]+1);
			int tmp3 = P[tmp][tmp2];
			tmp = tmp3;
			tmp2 -= Pow(2,tmp3);
		}
		printf("\n");
	}

}
