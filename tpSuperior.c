/*
 * tpSuperior.c
 *
 *  Created on: 31/10/2013
 *      Author: Naza
 */


#include <stdio.h>
#include <stdlib.h>


#define SI 1
#define NO 0


float **ingresarPares(int *cantidadDePares);

float **burbuja(int cantidadDePares, float **matrizDePares);

float **completarMatriz(float **matrizDePares, int cantidadDePares);

float *coeficientesPro(int cantidadDePares, float **matrizDePares);

float *coeficientesReg(int cantidadDePares, float **matrizDePares);

void mostrarPolinomios(int cantidadDePares, float *vectorDeCoeficientesPro, float *vectorDeCoeficientesReg, float **matrizDePares);

void menuPrincipal(float **matrizDePares, int cantidadDePares, float* vectorDeCoeficientesPro, float* vectorDeCoeficientesReg, int *volverAEmpezar);

void calcularPolinomio(int cantidadDePares, float* vectorDeCoeficientesPro, float* vectorDeCoeficientesReg, float** matrizDePares);

float **borrarPar(float **matrizDePares, int* cantidadDePares, int i);

float **buscarYBorrarPar(float** matrizDePares, int *cantidadDePares);


//TODO Ver los casos de la division por 0
//TODO Ver el caso de los coeficientes iguales a 0



int main(void)
{
    int volverAEmpezar = NO;

    do{

    int cantidadDePares = 0;


    float **matrizDePares = ingresarPares(&cantidadDePares);



    //Ordenando el vectorDePares
     matrizDePares = burbuja(cantidadDePares, matrizDePares);




    //completando la matriz con las diferencias
    matrizDePares = completarMatriz(matrizDePares, cantidadDePares);

    /*
     //printf de los datos ingresados de forma ordenada
    printf("Ordenando los pares...\n");
    i = 0;
    while(i < cantidadDePares)
    {
            printf("La componente X es: %.2f y la de Y es: %.2f\n", matrizDePares[i][0], matrizDePares[i][1]);
            i++;

    }

    for(j = 2; j <= cantidadDePares + 1; j++)
    {
          for(i=0; i <= cantidadDePares - j; i++)
          printf("Diferencia nro: %d es: %.2f\n", j-1, matrizDePares[i][j]);
    }
    */

    //Coeficientes del progresivo
    float *vectorDeCoeficientesPro = coeficientesPro(cantidadDePares, matrizDePares);


    //Coeficientes del regresivo
    float *vectorDeCoeficientesReg = coeficientesReg(cantidadDePares, matrizDePares);

    //Mostrando los Polinomios
    mostrarPolinomios(cantidadDePares, vectorDeCoeficientesPro, vectorDeCoeficientesReg, matrizDePares);


    //Menu principal
    menuPrincipal(matrizDePares, cantidadDePares, vectorDeCoeficientesPro, vectorDeCoeficientesReg, &volverAEmpezar);


    }while(volverAEmpezar == SI);

    return 0;

}



float **ingresarPares(int *cantidadDePares){

      //temp serÃ¡ la cantidadDePares
      int temp;

      printf("Ingrese la cantidad de Pares: ");
      scanf("%d", &temp);

      float **matrizDePares = (float **) calloc(temp,  sizeof(float *));

      int i = 0;
      for(i = 0; i < temp; i++)
      {
            matrizDePares[i] = (float *) calloc( temp + 1, sizeof(float));
      }


     /*
        float matrizDePares[cantidadDePares][cantidadDePares + 1];

       */

       float x;
       float y;

       //Ingresando los datos
       i = 0;
       while( i < temp)
       {
           printf("Ingrese la componente X: ");
           scanf("%f",&x);
           printf("Ingrese la componente Y: ");
           scanf("%f", &y);

           matrizDePares[i][0] = x;
           matrizDePares[i][1] = y;

           i++;
       }

       *cantidadDePares = temp;
       return matrizDePares;
}



float** burbuja(int cantidadDePares, float **matrizDePares){

    float auxX, auxY;
    int i;
    int j;
    for(i = 1; i < cantidadDePares ; i++)
    {
          for(j=0; j < cantidadDePares - i; j++)
          {
                   if(matrizDePares[j][0] > matrizDePares[j+1][0])
                   {
                              auxX = matrizDePares[j][0];
                              auxY = matrizDePares[j][1];
                              matrizDePares[j][0] = matrizDePares[j+1][0];
                              matrizDePares[j][1] = matrizDePares[j+1][1];
                              matrizDePares[j+1][0] = auxX;
                              matrizDePares[j+1][1] = auxY;
                   }
          }
    }

    return matrizDePares;
}


float **completarMatriz(float **matrizDePares, int cantidadDePares){

    int j;
    int i;
    for(j=1 ; j < cantidadDePares + 1; j++)
    {
             for(i=0; i < cantidadDePares - j; i++)
             {
              matrizDePares[i][j + 1] = (matrizDePares[i+1][j] - matrizDePares[i][j])/(matrizDePares[i+j][0] - matrizDePares[i][0]);
             }
    }

    return matrizDePares;
}


float *coeficientesPro(int cantidadDePares, float **matrizDePares)
    {

    float *vectorDeCoeficientesPro = (float *) malloc(cantidadDePares * sizeof(float));
    int i;
    i = 0;

    while(i < cantidadDePares )
    {
            vectorDeCoeficientesPro[i] = matrizDePares[0][i+1];
            //printf("a%d = %.2f\n",i, vectorDeCoeficientesPro[i]);
            i++;
    }

    return vectorDeCoeficientesPro;
}


float *coeficientesReg(int cantidadDePares, float **matrizDePares)
{
    float *vectorDeCoeficientesReg = (float *) malloc(cantidadDePares * sizeof(float));
    int i;
    i = cantidadDePares;
    int j;
    j = 0;

    while(i != 0)
    {
            vectorDeCoeficientesReg[j] = matrizDePares[i - 1][j + 1];
            //printf("a%d = %.2f\n",j, vectorDeCoeficientesReg[j]);
            i--;
            j++;
    }

    return vectorDeCoeficientesReg;
}


void mostrarPolinomios(int cantidadDePares, float *vectorDeCoeficientesPro, float *vectorDeCoeficientesReg, float **matrizDePares){

    //TODO system("cls");
    system("clear");
    printf("Polinomio Progresivo\n");
    printf("P(X) = ");

    int i;
    i = 0;

    int primeraVez = SI;
    while( i < cantidadDePares )
    {
           if(primeraVez == SI)
           {
                         printf("%.2f", vectorDeCoeficientesPro[i]);
                         primeraVez = NO;
           }else
           {

                printf(" + ");
                printf("%.2f", vectorDeCoeficientesPro[i]);

                int n = 0;
                while( n < i )
                {
                printf(" x ");
                printf("(X - %1.f)", matrizDePares[n][0]);
                n++;
                }
           }

           i++;
    }


    i = 0;
    printf("\n\n\n");
    printf("Polinomio Regresivo\n");
    printf("P(X) = ");
    primeraVez = SI;
    while( i < cantidadDePares )
    {
           if(primeraVez == SI)
           {
                         printf("%.2f", vectorDeCoeficientesReg[i]);
                         primeraVez = NO;
           }else
           {

                printf(" + ");
                printf("%.2f", vectorDeCoeficientesReg[i]);

                int n = 0;
                int aux = cantidadDePares - 1;
                while( n < i )
                {
                printf(" x ");
                printf("(X - %1.f)", matrizDePares[aux][0]);
                n++;
                aux--;
                }
           }

           i++;
    }

    printf("\n\n");
}

void menuPrincipal(float **matrizDePares, int cantidadDePares, float* vectorDeCoeficientesPro, float* vectorDeCoeficientesReg,int *volverAEmpezar)
{
    int salirPrograma = NO;
    int opcion = 0;
    *volverAEmpezar = NO;

    while(salirPrograma == NO && *volverAEmpezar == NO)
    {
    printf("\n\n\n\nMenu Principal\n\n");
    printf("1. Analizar el polinomio en algun punto del intervalo de interpolacion\n");
    printf("2. Agregar o quitar un par ordenado\n");
    printf("3. Volver a empezar\n");
    printf("4. Salir\n\n");
    printf("Opcion: ");
    scanf("%d", &opcion);
    //TODO system("cls");
    system("clear");


    switch(opcion)
    {
                            case 1:
                           {


                           //Calculo del valor del polinomio en un punto
                           calcularPolinomio(cantidadDePares, vectorDeCoeficientesPro, vectorDeCoeficientesReg, matrizDePares);



                                break;
                            }
                            case 2:
                            {
                                  //printf de los datos ingresados de forma ordenada
                                  int volverAlMenu = NO;
                                  while(volverAlMenu == NO)
                                  {
                                  printf("Pares Ordenados:\n");
                                  int i;
                                  i = 0;
                                  while(i < cantidadDePares)
                                  {
                                  printf("X= %.2f Y= %.2f\n", matrizDePares[i][0], matrizDePares[i][1]);
                                  i++;
                                  }

                                  int opcion2 = 0;
                                  printf("\nElija la opcion deseada:\n");
                                  printf("1. Agregar par ordenado\n");
                                  printf("2. Quitar par ordenado\n");
                                  printf("3. Mostrar polinomio actual\n");
                                  printf("4. Volver al Menu Principal\n\n");
                                  printf("Opcion: ");
                                  scanf("%d", &opcion2);
                                  //TODO system("cls");
                                  system("clear");


                                  switch(opcion2)
                                  {
                                                case 1:
                                                     {
                                                              float x, y;


                                                              printf("Ingrese el nuevo par...\n");
                                                              printf("Componente X: ");
                                                              scanf("%f", &x);
                                                              printf("Componente Y: ");
                                                              scanf("%f", &y);

                                                              cantidadDePares++;

                                                              matrizDePares = (float **) realloc(matrizDePares, cantidadDePares * sizeof(float *));


                                                              for(i=0; i < cantidadDePares; i++){
                                                              matrizDePares[i] = (float *) realloc( matrizDePares[i], (cantidadDePares + 1) * sizeof(float));
                                                              }

                                                              matrizDePares[cantidadDePares - 1][0] = x;
                                                              matrizDePares[cantidadDePares - 1][1] = y;

                                                              matrizDePares = burbuja(cantidadDePares, matrizDePares);


                                                              matrizDePares = completarMatriz(matrizDePares, cantidadDePares);

                                                              vectorDeCoeficientesPro = coeficientesPro(cantidadDePares, matrizDePares);


                                                              vectorDeCoeficientesReg = coeficientesReg(cantidadDePares, matrizDePares);



                                                              break;
                                                     }
                                                case 2:
                                                     {

                                                        printf("Pares Ordenados:\n");
                                                    	int i;
														i = 0;
														while(i < cantidadDePares)
														{
														printf("X= %.2f Y= %.2f\n", matrizDePares[i][0], matrizDePares[i][1]);
														i++;
                                                    	}

														matrizDePares = buscarYBorrarPar(matrizDePares, &cantidadDePares);

														matrizDePares = burbuja(cantidadDePares, matrizDePares);


														 matrizDePares = completarMatriz(matrizDePares, cantidadDePares);

														 vectorDeCoeficientesPro = coeficientesPro(cantidadDePares, matrizDePares);


														 vectorDeCoeficientesReg = coeficientesReg(cantidadDePares, matrizDePares);


                                                              break;

                                                     }
                                                case 3:
                                                {

                                                	  //Mostrando los Polinomios
                                                	   mostrarPolinomios(cantidadDePares, vectorDeCoeficientesPro, vectorDeCoeficientesReg, matrizDePares);

                                                	   break;

                                                }
                                                case 4:
                                                     {
                                                                      //mostrar el polinomio
                                                                      volverAlMenu = SI;
                                                                      break;
                                                     }
                                                default:
                                                {
                                                	printf("Error, opcion invalida\n");

                                                	break;
                                                }

                                  }
                                  }
                                  break;
                            }
                            case 3:
                                 {
                                        *volverAEmpezar = SI;
                                        //TODO system("cls");
                                        system("clear");
                                        break;
                                 }
                            case 4:
                           {
                                    salirPrograma = SI;
                                  //  sleep(1000);
                                    break;
                           }


                           }



   }



}

void calcularPolinomio(int cantidadDePares, float* vectorDeCoeficientesPro, float* vectorDeCoeficientesReg, float** matrizDePares)
{
                        float punto;
                        printf("\n");
                        printf("Ingrese el punto a evaluar: ");
                        scanf("%f", &punto);

                        float resultadoPro = 0;
                        float resultadoReg = 0;



                        //Progresivo
                        int i;
                        i = 0;
                        int primeraVez = SI;
                        while( i < cantidadDePares )
                        {
                               if(primeraVez == SI)
                               {
                                             resultadoPro += vectorDeCoeficientesPro[i];
                                             primeraVez = NO;
                               }else
                               {

                                    float resultadoProAux = vectorDeCoeficientesPro[i];

                                    int n = 0;
                                    while( n < i )
                                    {
                                           resultadoProAux *= (punto - matrizDePares[n][0]);
                                           n++;
                                    }

                                    resultadoPro += resultadoProAux;

                               }

                                    i++;
                        }



                                     //Regresivo
                                     i = 0;
                                     primeraVez = SI;
                                     while( i < cantidadDePares )
                                     {
                                     if(primeraVez == SI)
                                     {
                                      resultadoReg += vectorDeCoeficientesReg[i];
                                      //printf("\n ResultadoReg: %2.f\n", resultadoReg);
                                      primeraVez = NO;
                                     }else
                                     {


                                          float resultadoRegAux = vectorDeCoeficientesReg[i];

                                          int n = 0;
                                          int aux = cantidadDePares - 1;
                                          while( n < i )
                                                 {

                                                 resultadoRegAux *= (punto - matrizDePares[aux][0]);

                                                 n++;
                                                 aux--;
                                                 }


                                          resultadoReg += resultadoRegAux;
                                        //  printf("\n ResultadoReg: %2.f\n", resultadoReg);
                                       }

                                          i++;
                                       }

                                          //printf de ambos resultados

                                          printf("Resultado en el polinomio Progresivo: P(%.2f) = %.2f\n", punto, resultadoPro);
                                          printf("Resultado en el polinomio Regresivo: P(%.2f) = %.2f\n", punto, resultadoReg);
}


float **buscarYBorrarPar(float** matrizDePares, int *cantidadDePares){

	float x, y;
	int temp = *cantidadDePares;
	printf("Ingrese el valor de X: ");
	scanf("%f", &x);
	printf("Ingrese el valor de Y: ");
	scanf("%f", &y);

	int i = 0;
	int encontrado = NO;

	while(encontrado == NO && i < temp){
		if(matrizDePares[i][0] == x && matrizDePares[i][1] == y){
			encontrado = SI;
		}
		else
			i++;
	}

	if(encontrado)
		matrizDePares = borrarPar(matrizDePares, &temp, i);


	*cantidadDePares = temp;


	return matrizDePares;



}


float **borrarPar(float **matrizDePares, int* cantidadDePares, int i){

	float auxX, auxY;


	while((i+1) < *cantidadDePares ) {

	auxX = matrizDePares[i][0];
	auxY = matrizDePares[i][1];

	matrizDePares[i][0] = matrizDePares[i+1][0];
	matrizDePares[i][1] = matrizDePares[i+1][1];

	matrizDePares[i+1][0] = auxX;
	matrizDePares[i+1][1] = auxY;

	i++;
	}

	*cantidadDePares -= 1;

	matrizDePares = (float **) realloc(matrizDePares, *cantidadDePares * sizeof(float *));

	int n;

	for(n = 0; n < *cantidadDePares; n++){
		matrizDePares[n] = (float *) realloc(matrizDePares[n], (*cantidadDePares + 1) * sizeof(float));
	}

	return matrizDePares;

}
