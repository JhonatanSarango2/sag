struct Cliente
{
    char nombre[30];
    int cedula;
};
struct Producto
{
    char nombre[30];
    float precio;
};
struct Venta
{
    struct Cliente cliente;
    int numProductos;
    struct Producto productos[5];
    float totalVenta;
};
void leerCadena(char *cadena, int num);
int menu();
void inicializarProductos(struct Producto productos[5]);
void imprimirProductos(struct Producto productos[5]);
void guardarproductos(struct Producto *productos);
int leerProductos(struct Producto productos[5]);
void realizarVenta(struct Venta venta[5], struct Producto productos[5], int *numVentas);
void listarVentas(struct Venta ventas[5], int numVentas);
void guardarVentas(struct Venta *ventas, int numVentas);
int Leerventas(struct Venta ventas[5], int *numVentas);
void buscarVentas();