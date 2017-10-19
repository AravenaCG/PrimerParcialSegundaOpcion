#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pantalla.h"
#include "contratacion.h"
#include "validar.h"
#include "informes.h"

/** \brief imprime la estructura
 *
 * \param listaPantallas es el array
 * \param limite la cantidad de elementos para el array
 * \return retorno : -1 (error) ; 0 (funciona correctamente)
 *
 */

int info_PrintPantallas(sPantalla listaPantallas[], int limite)
{
    int retorno = -1;
    int i;

    if(listaPantallas != NULL && limite > 0)
    {
        printf("*************************************************************\n");
        printf("*~~~~~~~~~~~~~~~~PANTALLAS PARA IMPRIMIR~~~~~~~~~~~~~~~~~~~~*\n");
        printf("*************************************************************\n");
        for(i=0; i<limite ; i++)
        {
            if(listaPantallas[i].flag_ocupado == INDICE_OCUPADO)
            {
                printf("*************************************************************\n");
                printf("\n* ID PANTALLA:%d\n* DIRECCION:%s\n* PRECIO:%.2f\n",
                       listaPantallas[i].idPantalla,
                       listaPantallas[i].direccion,
                       listaPantallas[i].precio);
                if(listaPantallas[i].tipoPantalla == 1)
                {
                    printf( "\n* TIPO DE PANTALLA: LED\n");
                }
                else
                {
                    printf( "\n* TIPO DE PANTALLA: LCD\n");
                }
                printf("*************************************************************\n");
            }
        }

    }
    return retorno;
}

/** \brief busca la posicion segun el Cuit recibido
 *
 * \param listaContrataciones es el array de la estructura sContratacion donde se va a buscar el CUIT recibido
 * \param len es el largo del array
 * \param texto es el puntero al cuit recibido para buscar
 * \return retorna la posicion donde se encontro el CUIT
 *
 */

int info_BuscarPosicionCUIT(sContratacion listaContrataciones[],int len, char texto[])
{
    int i;
    int retorno =-1;
    for (i=0; i<len; i++)
    {
        if (listaContrataciones[i].flag_ocupado == INDICE_OCUPADO )
        {
            if (strcmp(listaContrataciones[i].cuitCliente, texto) == 0)
            {
                retorno = i;
                break;

            }
        }
    }
    return retorno;
}

/** \brief lista (imprime) las contrataciones
 *
 * \param listaContrataciones es el array cuyo elementos se van a imprimir
 * \param limite es el largo del array recibido
 * \return retorno 0 si funciona, -1 si no.
 *
 */


int info_PrintContrataciones(sContratacion listaContrataciones[], int limite)
{
    int retorno = -1;
    int i;
    if(listaContrataciones != NULL && limite > 0)
    {
        printf("*************************************************************\n");
        printf("*~~~~~~~~~~~~~~~~~LISTA DE CONTRATACIONES~~~~~~~~~~~~~~~~~~~*\n");
        printf("*************************************************************\n");
        for(i=0; i<limite ; i++)
        {
            if(listaContrataciones[i].flag_ocupado == INDICE_OCUPADO)
            {
                retorno=0;
                printf("*************************************************************\n");
                printf("* CUIT CLIENTE:%s \n* ID CONTRATACION:%d\n* DIAS:%d\n* NOMBRE DE ARCHIVO:%s\n* ID PANTALLA RELACIONADA:%d\n",listaContrataciones[i].cuitCliente,
                       listaContrataciones[i].idContratacion,
                       listaContrataciones[i].dias,
                       listaContrataciones[i].archivo,
                       listaContrataciones[i].idPantallaRelacion);
                printf("*************************************************************\n");
            }
        }

    }
    return retorno;
}


/** \brief calcula el monto a pagar por un cliente, la consulta se realiza por el Cuit recibido
 *
 * \param listaContrataciones array de contrataciones
 * \param listaPantallas array de pantallas
 * \param lenContrataciones es el largo del array listaContrataciones
 * \param lenPantallas es el largo del array listaPantallas
 * \param bCUIT es el Cuit recibido que se consulta para calcular el monto.
 * \return retorno -1 si funciona mal. 0 si funciona correctamente
 *
 */


int info_CalcularMontoSegunCuit(sContratacion listaContrataciones[],sPantalla listaPantallas[], int lenContrataciones,int lenPantallas, char bCUIT[])
{
    int retorno=-1;
    int indexPantalla;
    int i;
    float monto;

    if(listaContrataciones != NULL && lenContrataciones > 0)
    {
        if(listaPantallas != NULL && lenPantallas > 0)
        {

            printf("*************************************************************\n");
            printf("*                      CLIENTE:%s              *",bCUIT);
            for (i=0; i<lenContrataciones; i++)
            {
                if(strcmp(listaContrataciones[i].cuitCliente,bCUIT)== 0)
                {
                    indexPantalla = listaContrataciones[i].idPantallaRelacion;
                    monto = listaContrataciones[i].dias * listaPantallas[indexPantalla].precio;
                    printf("* LA CONTRATACION: %d \n* TIENE POR MONTO:%.2f\n ", listaContrataciones[i].idContratacion,monto);
                    retorno=0;
                    printf("*************************************************************\n");
                }
            }

        }
    }


    return retorno;
}




/** \brief cuenta la cantidad de clientes ingresados segun las contrataciones dadas de alta
 *
 * \param
 * \param
 * \return
 *
 */

int info_Contar_Cantidad_Clientes_byCuit(sContratacion* listaContrataciones,int lenghtContrataciones, int* lenClientes)
{
    int retorno = -1;
    int i;
    int j;
    int totalContrataciones = 0;
    int cuitRepetidos = 0;

    if(listaContrataciones != NULL && lenghtContrataciones > 0 )
    {
        for (i=0; i<lenghtContrataciones; i++)
        {
            if (listaContrataciones[i].flag_ocupado==INDICE_OCUPADO)
            {
                totalContrataciones++;
                for (j=i+1; j<lenghtContrataciones; j++)
                {
                    if (listaContrataciones[j].flag_ocupado== INDICE_OCUPADO)
                    {
                        if (strcmp(listaContrataciones[i].cuitCliente, listaContrataciones[j].cuitCliente)== 0)
                        {
                            cuitRepetidos++;

                        }
                        retorno=0;
                    }


                }

            }
        }
        *lenClientes = totalContrataciones - cuitRepetidos;
    }
    return retorno;
}


/** \brief lista (imprime) las contrataciones
 *
 * \param listaContrataciones es el array cuyo elementos se van a imprimir
 * \param limite es el largo del array recibido
 * \return retorno 0 si funciona, -1 si no.
 *
 */


/**int info_PrintClientes(sCliente listaClientes[], int limite)
{
    int retorno = -1;
    int i;
    if(listaClientes != NULL && limite > 0)
    {
        printf("*~~~~~~~~~~~~~~~~~LISTA DE CLIENTES~~~~~~~~~~~~~~~~~~~*\n");
        for(i=0; i<limite ; i++)
        {
            if(listaClientes[i].flag_ocupado == INDICE_OCUPADO)
            {
                retorno=0;
                printf("*************************************************************\n");
                printf("* ID CONTRA: \n* ID CONTRATACIONes:%s\n* IDCLIENTE:%d\n* saldo total :%f\n",

                       listaClientes[i].cuit,
                       listaClientes[i].idCliente,
                       listaClientes[i].saldoTotal);
                printf("*************************************************************\n");
            }
        }

    }
    return retorno;
}*/
