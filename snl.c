#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define e 2.71828182846
#define N 3
#define PI 3.1415
#define h 1e-06
#define tot 15  //prof pediu

//###################################### Funçoes com as equacoes #################################

double f1(double x[N]) 
{	
     return (pow(x[0],2) - 81*pow(x[1] + 0.1, 2) + sin(x[2]) + 1.06);
	
}
	
double f2(double x[N]) 
{	
     return (exp(x[0]*x[1]) + 20*(x[2]) + (10*PI -3) / 3.0 );	
}

double f3(double x[N]) 
{	
     return (3*x[0] - cos(x[1]*x[2]) - 0.5);
}




//##################################### Jacobiano #########################################

double df(double f(), double x[N], int k)
{
	int i;
	double aux[N], v;
	
	
	for(i = 0; i < N; i++)
		aux[i] = x[i];
	
	aux[k] = x[k] + h/2.0;
	
	v = f(aux);
	
	aux[k] = x[k] - h/2.0;	
	
	v = (v - f(aux))/h;
	
	return(v);
}



//############################################### Função principal ##########################################
	
int main()
{	
     FILE *saida;
     int cont, i,j,k;
     double x[N], x0[N],y[N],norm,norma,nova_norma,nova,normay,normy,c,tol=1e-07;          
     double (*equacao[N])()={f1, f2, f3};         
     double **jac,**m;
	
     cont=0;
     
   
     saida=fopen("norma3.dat","w");

     jac=malloc(N*sizeof(double *));
     m=malloc(N*sizeof(double *));

     for (i=0;i<N;i++)
     {                                          //alocar o vetor
          jac[i]=malloc(N*sizeof(double));
          m[i]=malloc((N+1)*sizeof(double));
     }

    


     printf("\n\tdigite os valores vetor tentativa:\n");

     for(i=0; i<N; i++)
     {
        printf("%d° valor:",i+1);     //inserir 0.1,0.1,-0.1 
        scanf("%lf",&x0[i]);
     }

     
                               
     	 
     do
     {


         norm=0;

         for(i=0;i<N;i++)
         {   
               x[i]=equacao[i](x0);
               

               norm += pow(fabs(x[i]),2);                            
         }

         norma = sqrt(norm);

         cont++;     //contar numeros de iteraçoes
        
        for(i=0;i<N;i++)
	{
	      x[i] = -equacao[i](x0);
			
	      for(j = 0; j < N; j++)
	      {
		      jac[i][j] = df(equacao[i], x0, j);
	      }		
	}
	  


        for(i=0;i<N;i++)
        {
	       for(j=0;j<N;j++)
			
	             m[i][j] = jac[i][j];  //copia o jacobiano
	}

        for(i=0;i<N;i++)
		
		m[i][N] = x[i];  //estende a matriz

        
        //diagonalizando
	for(j=0;j<N;j++)
        {
              for(i=0;i<N;i++)
              {
                    if(i!=j) // Pegando elementos Diferentes
                    {
                           c=m[i][j]/m[j][j];   // operador para diagonalizar
                                                  
                           for(k=0; k<N+1; k++)
                           {
                                m[i][k]=m[i][k]-c*m[j][k]; // fazendo para todas as linhase colunas
                           }
                    }
              }
        }
		

        
	for(i=0;i<N;i++)
        {
       	 	
       	 	y[i]=m[i][N]/m[i][i];
        	

                x0[i]=x0[i]+y[i];
   	 }

         nova=0;

	 for(i=0;i<N;i++)
	 {	
		x[i] = equacao[i](x0);
 											
	        nova += pow(fabs(x[i]),2);
	 }
	
         nova_norma = sqrt(nova);

         
         normy=0;
         for(i=0;i<N;i++)
	 {	
		
               normy += pow(fabs(y[i]),2);
	 }
	
         normay = sqrt(normy);

         fprintf(saida,"\n%d\t%.2lf",cont,normay);
   
         if(cont>tot)
             break;


    }while(fabs(nova_norma-norma)>tol);



     if(cont>tot)
            printf("\n\tProcesso parou, número de iterações limite atingido\n");

     else
          printf("\n\tconvergiu em :%d passos\n\n", cont);

     
    
	
	// Imprimindo a solução
	printf("\n O vetor solução\n"); 
	for(i=0; i<N; i++)
   	 {
       	 	
        	printf("x%d:%0.2lf\n",i+1,x0[i]);
   	 }    
         

    
}




