#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "validar.h"
#include "pantalla.h"
#include "contratacion.h"
#include "informes.h"
#include "scliente.h"


/** \brief idAutoincrementable
 *
 * \param array listaCliente recibe puntero al inicio del array
 * \param len es la cantidad de elementos del array
 * \return retorna el ultimo valor para utilizar en Id
 *
 */

int cliente_generar_Proximo_Id(sCliente listaClientes[], int len)
{
    static int ultimoValorIdAutoincrementable = -1;
    ultimoValorIdAutoincrementable ++;
    return ultimoValorIdAutoincrementable;

}



/** \brief Inicializa la lista
 *
 * \param array listaClientes recibe puntero al inicio del array
 * \param limite es la cantidad de elementos del array
 * \return retorno : -1 (error) ; 0 (funciona correctamente)
 *
 */

int cliente_InitLista(sCliente listaClientes[], int limite)
{
    int retorno = -1;
    int i;

    if( listaClientes != NULL && limite > 0)
    {
        for(i=0; i<limite ; i++)
        {
            listaClientes[i].flag_ocupado = INDICE_LIBRE;
            retorno=0;
        }

    }

    return retorno;
}


/**
 * Obtiene el primer indice libre del array.
 * @param lista el array se pasa como parametro.
 * @return el primer indice disponible
 */
int cliente_obtenerEspacioLibre(sCliente  listaClientes[],int limite)
{

    int retorno = -1;
    int i;
    if(listaClientes != NULL && limite > 0)
    {
        for(i=0; i<limite ; i++)
        {
            if(listaClientes[i].flag_ocupado == INDICE_LIBRE)
            {
                retorno =  i;
                break;
            }
        }

    }
    return retorno;

}


/** \brief carga listaClientes
 *
 * \param
 * \param
 * \return
 *
 */

 int cliente_Cargar_Clientes_ByCuit(sContratacion* listaContrataciones,int lenContrataciones,sCliente* listaClientes,int lenClientes)
 {
    int retorno = -1;
    int i;
    int j;
    int k;
    int flag_repetido=0;
    char buffCuit[50];
    int index;
    int indexContratacion=-1;


    if(listaContrataciones != NULL && lenContrataciones > 0 )
    {


        for (i=0, j=0; i<lenContrataciones; i++,j++)
        {
            if (listaContrataciones[i].flag_ocupado==INDICE_OCUPADO)
            {
                strncpy(buffCuit,listaContrataciones[i].cuitCliente,50);
                for (k=0; k<lenClientes; k++)
                {
                    if(strcmp(buffCuit,listaClientes[k].cuit) == 0)
                    {
                        flag_repetido++;
                        indexContratacion++;
                        listaClientes[k].idContrataciones[indexContratacion][20]= listaContrataciones[i].idContratacion;

                    }
                }
                /**si es un CUIT que no se encuentra ingresado entonces se copia en la posicion*/
                if(flag_repetido != 0)
                {
                    j--;
                }
                else
                {
                    index = cliente_obtenerEspacioLibre(listaClientes,lenClientes);
                    listaClientes[index].flag_ocupado = INDICE_OCUPADO;
                    listaClientes[index].idCliente= cliente_generar_Proximo_Id(listaClientes,lenClientes);
                    indexContratacion=0;
                    listaClientes[index].idContrataciones[indexContratacion][20]= listaContrataciones[i].idContratacion;
                    strncpy(listaClientes[index].cuit,buffCuit,50);
                }

            }
        }

        retorno=0;
    }
    return retorno;
}

/** for (l=0; l<lenClientes; l++)
        {
            if (listaContrataciones[l].flag_ocupado==INDICE_OCUPADO)
            {
                strncpy(buffCuit,listaClientes[l].cuit,50);
                for (k=0; k<lenContrataciones; k++)
                {
                    if (listaContrataciones[k].flag_ocupado==INDICE_OCUPADO)
                    {
                        if (strcmp(buffCuit, listaContrataciones[k].cuitCliente) == 0)
                        {
                            idPantalla = listaContrataciones[k].idPantallaRelacion;
                            monto = listaContrataciones[k].dias * listaPantallas[idPantalla].precio;
                            listaClientes[l].saldoTotal =listaClientes[l].saldoTotal + monto;
                        }
                    }
                }
            }
        }*/
