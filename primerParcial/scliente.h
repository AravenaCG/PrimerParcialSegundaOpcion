#ifndef SCLIENTE_H_INCLUDED
#define SCLIENTE_H_INCLUDED
#define LIMITE_CONTRATACIONES 4036

typedef struct{
    int idCliente;
    int flag_ocupado;
    char cuit[50];
    char idContrataciones[LIMITE_CONTRATACIONES][20];
    float saldoTotal;
}sCliente;

#endif // SCLIENTE_H_INCLUDED
#define INDICE_OCUPADO 0
#define INDICE_LIBRE 1

int cliente_generar_Proximo_Id(sCliente listaClientes[], int len);
int cliente_InitLista(sCliente listaClientes[], int limite);
int cliente_obtenerEspacioLibre(sCliente  listaClientes[],int limite);
int cliente_Cargar_Clientes_ByCuit(sContratacion* listaContrataciones,int lenContrataciones,sCliente* listaClientes,int lenClientes);
