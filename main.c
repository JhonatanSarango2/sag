#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main(int argc, char *argv[])
{
    struct Producto productos[5];
    struct Venta ventas[5];
    int numVentas = 0;
    int opc;
    do
    {
        opc = menu();
        switch (opc)
        {
        case 1:
            inicializarProductos(productos);
            break;
        case 2:
            if (leerProductos(productos) == 0)
            {
                printf("No se pudieron leer los productos.\n");
            }
            else
            {
                imprimirProductos(productos);
            }
            break;
        case 3:
            realizarVenta(ventas, productos, &numVentas);
            break;
        case 4:
            Leerventas(ventas, &numVentas);
            if (numVentas == 0)
            {
                printf("No hay ventas registradas.\n");
            }
            else
            {
                listarVentas(ventas, numVentas);
            }
            break;
        default:
            break;
        }
    } while (opc != 6);

    return 0;
}