#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

struct matrisler{
   int*mata;
   int*matb;
   int*matc;
   int k;
   int n;
   int r;
};

typedef struct matrisler Matris ;

static void * multiplication(void *arg){
	
    Matris* current = arg;
    int *matrisA = (current->mata);
    int *matrisB = (current->matb);
    int *matrisC = (current->matc);
    int k = current->k;
    int n = current->n;
    int r = current->r;
	int c;
	
	if(pthread_self() == 2){     
			for(c=0;c<10000000;c++); //�rne�in burada sleep(1000) metodu da kullan�labilinir;
	}
		//*(a + (s�t�n_say�s� * sat�r_index) + s�t�n_index)
	int i, j;
    for (i = 0 ; i < r; i++) {
        for (j = 0; j < n; j++) {																	 														    
              *(matrisC+(r*(pthread_self()-1))+i) +=  (*(matrisA + (n * (pthread_self()-1)) + j) ) * (*(matrisB+(r*j)+i));
		}
    }
    
  	printf("Thread id : %d islemini bitirdi \n",pthread_self());
   
		printf("C MATRIS :\n");
		for(i = 0; i < k; i++){
			printf("[ ");
        	for(j = 0; j < r; j++){
        		printf("%-2d ",*(matrisC + (r * i) + j));
        	 	if(j+1 == r){
        		printf("]");
        		printf("\n");
			}
        }
    } 
    return 0;
}


int main(void)
{
	time_t t;
	srand((unsigned) time(&t));
	
	int k,n,r; 
	printf("k giriniz: ");
	scanf("%d",&k);
	printf("n giriniz: ");
	scanf("%d",&n);
	printf("r giriniz: ");
	scanf("%d",&r);
    
   	//  A MATR�S� K SATIR N SUTUN    
	//  B MATR�S� N SATIR R SUTUN    
	//  C MATR�S� K SATIR R SUTUN
	// (int*)malloc(*sizeof(int)); int tipinde bir de�i�ken i�in yer ayr�ld�.
    int *a = (int*)malloc(k*n*sizeof(int));
    int *b = (int*)malloc(n*r*sizeof(int));  
	int *c = (int*)malloc(k*r*sizeof(int));
    	
	int i,j;
    for(i = 0; i < k; i++)
    {
        for(j = 0; j < n; j++)
        {
        	*(a + (n * i) + j) = rand()%6;
        }
	}
	
	printf("A MATRIS :\n");
	  for(i = 0; i < k; i++) 
		{
	  	printf("[ ");
          for(j = 0; j < n; j++)
          {
        	printf("%-2d",*(a + (n * i) + j));
        	if(j+1 == n)
			{
        		printf("]");
        		printf("\n");
			}
    	  }
		}
	
	
		for(i = 0; i < n; i++){
        	for(j = 0; j < r; j++){
        	*(b + (r * i) + j) = rand()%6;
        }
	}
	
	printf("B MATRIS :\n");
	   for(i = 0; i < n; i++)
		{
		  printf("[ ");
           for(j = 0; j < r; j++)
		   {
        		printf("%-2d",*(b + (r * i) + j));
        	 	if(j+1 == r)
				{
        			printf("]");
        			printf("\n");
				}
          } 
        
		}
	
	    for(i = 0; i < k; i++){
        	for(j = 0; j < r; j++){
        	*(c + (r * i) + j) = 0; // C'nin elemanlar�na 0 de�erini atad�k.
        }
	}
	
	
	
  	  Matris* temp=(Matris*)malloc(sizeof(Matris));
	  temp->mata = a;
	  temp->matb = b;
	  temp->matc = c;
      temp->k = k;
      temp->n = n;
      temp->r = r;
      
    pthread_t threads[k]; // Burada kullan�lan k arguman�n�n sebebi, c matrisin sat�r say�s� kadar thread dizisinin boyutunun ayarlanmas�d�r.
    for(i = 0; i < k; i++)
    {
		pthread_create(&threads[i], NULL, multiplication,temp);
    }
    

    for(i = 0; i < k; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
	
		printf("EN SON HALI C MATRIS :\n");
	for(i = 0; i < k; i++){
			printf("[ ");
        	for(j = 0; j < r; j++){
        		printf("%-2d ",*(c + (r * i) + j));
        	 	if(j+1 == r){
        		printf("]");
        		printf("\n");
			}
        }  
	}
	
    free(temp);
    free(a);
    free(b);
    free(c);

    return 0;
}
