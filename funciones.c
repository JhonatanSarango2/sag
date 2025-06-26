#include <stdio.h>
#include <string.h>
#include "funciones.h"

// Lee una cadena desde teclado y elimina el salto de línea final
void leerCadena(char *cadena, int num)
{
    fflush(stdin); // Limpia el buffer de entrada
    fgets(cadena, num, stdin); // Lee la cadena
    int len = strlen(cadena) - 1;
    cadena[len] = '\0'; // Elimina el salto de línea
}
// Muestra el menú principal y retorna la opción elegida
int menu()
{
    int opcion;
    printf("\n\n----------Menu de opciones----------\n");
    printf("1. Inicializar productos.\n");
    printf("2. Imprimir productos.\n");
    printf("3. Realizar venta.\n");
    printf("4. Listar ventas.\n");
    printf("5. Buscar ventas.\n");
    printf("6. Salir.\n");
    printf(">>>>>: ");
    scanf("%d", &opcion);
    return opcion;
}
// Inicializa el arreglo de productos con valores predeterminados
void inicializarProductos(struct Producto productos[5])
{
    strcpy(productos[0].nombre, "Microoanda");
    productos[0].precio = 80;
    strcpy(productos[1].nombre, "Licuadora");
    productos[1].precio = 30;
    strcpy(productos[2].nombre, "Cocina");
    productos[2].precio = 200;
    strcpy(productos[3].nombre, "Refrigerador");
    productos[3].precio = 600;
    strcpy(productos[4].nombre, "Televisor");
    productos[4].precio = 700;
    guardarproductos(productos); // Guarda los productos en archivo binario
}
// Imprime la lista de productos disponibles
void imprimirProductos(struct Producto productos[5])
{
    printf("\n\nProductos disponibles.\n");
    printf("%s %-10s %-20.2s\n", "#","Nombre","Precio");
    printf("----------------------------------------\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d %-10s %-20.2f\n", i + 1,productos[i].nombre,productos[i].precio);
        printf("----------------------------------------\n");
    }
}
// Guarda el arreglo de productos en un archivo binario
void guardarproductos(struct Producto *productos)
{
    FILE *f;
    f = fopen("productos.dat", "wb+"); // Abre el archivo para escritura binaria
    fwrite(productos, sizeof(struct Producto), 5, f); // Escribe los 5 productos
    fclose(f);
}
// Lee los productos desde el archivo binario y los carga en el arreglo
int leerProductos(struct Producto productos[5])
{
    FILE *f;
    f = fopen("productos.dat", "rb+");
    if (f == NULL)
    {
        printf("No existe el archivo de productos.\n");
        return 0;
    }
    fread(productos, sizeof(struct Producto), 5, f); // Lee los 5 productos
    fclose(f);
    return 1;
}
// Realiza una venta y la guarda en el archivo de ventas
void realizarVenta(struct Venta venta[5], struct Producto productos[5], int *numVentas)
{
    struct Venta nuevaVenta;
    int numProductos, productoIndex;
    printf("\n\nIngrese el nombre del cliente: ");
    leerCadena(nuevaVenta.cliente.nombre, 30);
    printf("\nIngrese la cedula del cliente: ");
    scanf("%d", &nuevaVenta.cliente.cedula);
    printf("\nIngrese el numero de productos (max 5): ");
    scanf("%d", &numProductos);
    if (numProductos > 5 || numProductos < 1)
    {
        printf("Numero de productos no valido, se limitara a 5.\n");
        return;
    }
    nuevaVenta.numProductos = numProductos;
    nuevaVenta.totalVenta = 0.0;
    printf("Seleccione el producto (0-4).\n");
    imprimirProductos(productos);
    for (int i = 0; i < numProductos; i++)
    {
        printf(">>>");
        scanf("%d", &productoIndex);
        // Validación del índice del producto
        if (productoIndex < 1 || productoIndex >= 5)
        {
            printf("Producto no valido, intente de nuevo.\n");
            i--; // Repite la selección para este producto
            continue;
        }
        nuevaVenta.productos[i] = productos[productoIndex];
        nuevaVenta.totalVenta += productos[productoIndex].precio;
    }
    venta[*numVentas] = nuevaVenta; // Guarda la venta en el arreglo local
    (*numVentas)++;
    guardarVentas(&nuevaVenta, 1); // Guarda la venta en el archivo
    printf("Venta realizada con exito. Total: %.2f\n", nuevaVenta.totalVenta);
}
// Lista todas las ventas almacenadas en el arreglo
void listarVentas(struct Venta ventas[5], int numVentas)
{
    if (numVentas == 0)
    {
        printf("No hay ventas registradas.\n");
        return;
    }
    printf("----------Listado de ventas----------\n");
    for (int i = 0; i < numVentas; i++)
    {
        printf("\n-Venta #%d:\n", i + 1);
        printf("Cliente: %s\nCedula: %d\n", ventas[i].cliente.nombre, ventas[i].cliente.cedula);
        printf("Productos aquiridos:\n");
        for (int j = 0; j < ventas[i].numProductos; j++)
        {
            printf("%d. %s - %.2f\n", j + 1, ventas[i].productos[j].nombre, ventas[i].productos[j].precio);
        }
        printf("Total de la venta: %.2f\n", ventas[i].totalVenta);
    }
}
// Guarda una o varias ventas en el archivo binario
void guardarVentas(struct Venta *ventas, int numVentas)
{
    FILE *f;
    f = fopen("ventas.dat", "ab+"); // Abre el archivo para agregar ventas
    if (f == NULL)
    {
        printf("Error al abrir el archivo de ventas.\n");
        return;
    }
    fwrite(ventas, sizeof(struct Venta), numVentas, f); // Escribe las ventas
    fclose(f);
}
// Lee hasta 5 ventas del archivo binario y las carga en el arreglo
int Leerventas(struct Venta ventas[5], int *numVentas)
{
    FILE *f;
    f = fopen("ventas.dat", "rb+");
    if (f == NULL)
    {
        printf("No existe el archivo de ventas.\n");
        *numVentas = 0;
        return 0;
    }
    *numVentas = fread(ventas, sizeof(struct Venta), 5, f); // Lee hasta 5 ventas
    fclose(f);
    return 1;
}
// Busca ventas por cédula de cliente y las muestra
void buscarVentas()
{
    int cedulabuscar;
    struct Venta ventas[5];
    int numVentas = 0;
    Leerventas(ventas, &numVentas); // Carga ventas desde archivo
    printf("Ingrese la cedula del cliente a buscar: ");
    scanf("%d", &cedulabuscar);
    int encontrado = 0;
    for (int i = 0; i < numVentas; i++)
    {
        if (ventas[i].cliente.cedula == cedulabuscar)
        {
            printf("Venta encontrada:\n");
            printf("Cliente: %s, Cedula: %d\n", ventas[i].cliente.nombre, ventas[i].cliente.cedula);
            printf("Productos:\n");
            for (int j = 0; j < ventas[i].numProductos; j++)
            {
                printf("%d. %s - %.2f\n", j + 1, ventas[i].productos[j].nombre, ventas[i].productos[j].precio);
            }
            printf("Total de la venta: %.2f\n", ventas[i].totalVenta);
            encontrado = 1;
        }
    }
    if (!encontrado)
    {
        printf("No se encontraron ventas para la cedula %d.\n", cedulabuscar);
    }
}