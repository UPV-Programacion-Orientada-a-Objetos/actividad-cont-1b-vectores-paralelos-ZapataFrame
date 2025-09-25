#include <iostream>
#include <iomanip> // Libreria para manejar mejor la IO de la consola
#include <fstream> // Libreria para manipular el flujo de archivos
#include <sstream> // Libreria para manejar strings como flujo.

// Prototypes
int get_menu_option();
void consult_product();
void update_inventory();
void update_inventory_by_ubication();
void products_report();
void products_stock_report();
void highest_price_product();
void lowest_price_product();
void register_new_product();

// files methods
void load_data_from_file();
void save_data_to_file();

void print_index(int index);
int get_int_input(std::string prompt);
float get_float_input(std::string prompt);
int get_index_by_code(int code);
int get_highest_price_product_index();
int get_lowest_price_product_index();
void wait_enter();

int find_int_in_array(int element, int *array, int size);
int find_string_in_array(std::string element, std::string *array, int size);
int get_highest_in_array(float *array, int size);
int get_highest_in_array(int *array, int size);
int get_lowest_in_array(float *array, int size);

// Constantes
char FILE_DELIMITER = ',';
std::string FILE_PATH = "./data/inventario.txt";

// Variables Globales
int elementCount = 0;
int codes[100];
std::string names[100];
int stocks[100];
float prices[100];
std::string ubications[100];

int main()
{
    load_data_from_file();
    std::cout << "\n--- Ferreteria \"El Martillo\" ---" << std::endl;
    bool is_program_running = true; // variable centinela

    while (is_program_running)
    {
        int opt = get_menu_option();
        switch (opt)
        {
        case 1: //
            consult_product();
            break;
        case 2:
            update_inventory();
            break;
        case 3:
            products_report();
            break;
        case 4:
            highest_price_product();
            break;

        case 5:
            register_new_product();
            break;
        case 6:
            update_inventory_by_ubication();
            break;
        case 7:
            products_stock_report();
            break;
        case 8:
            lowest_price_product();
            break;
        case 0:
            std::cout << "Bye!" << std::endl;
            is_program_running = false;
            save_data_to_file(); // guarda los valores
            break;
        default:
            std::cout << "Esta opcion no existe. . ." << std::endl;
            break;
        }
        if (is_program_running)
            wait_enter();
    }
    return 0;
}

/**
 * Funcion para imprimir el menu y obtener una opción desde consola.
 * @return opción seleccionada
 */
int get_menu_option()
{
    // imprimir menu
    std::cout << "\n--- Menú principal ---" << std::endl;
    std::cout << "┌─────────────────────────────────────────┐" << std::endl;
    std::cout << "│ 1) Consultar un producto" << std::endl;
    std::cout << "│ 2) Actualizar inventario" << std::endl;
    std::cout << "│ 3) Generar reporte completo" << std::endl;
    std::cout << "│ 4) Encontrar el producto más caro" << std::endl;
    std::cout << "│ 0) Salir" << std::endl;
    std::cout << "│ ===== ¡¡¡ Nuevas implementaciones !!! ===== " << std::endl;
    std::cout << "│ 5) Registrar nuevo producto" << std::endl;
    std::cout << "│ 6) Actualizar inventario por ubicacion" << std::endl;
    std::cout << "│ 7) Generar reporte de bajo stock" << std::endl;
    std::cout << "│ 8) Encontrar el producto más barato" << std::endl;
    std::cout << "└─────────────────────────────────────────┘" << std::endl;

    // obtener opcion desde input
    bool valid_input = false;
    int opt;

    // Validar opcion
    do
    {
        opt = get_int_input("Seleccione una opción [1-9]:");

        if (opt >= 0 && opt <= 9)
        {
            valid_input = true; // Si es una opcion valida salir
        }
        else
        {
            std::cout << "[Error] Debe ingresa una opción valida" << std::endl;
        }

    } while (!valid_input);
    return opt;
}

/**
 * Funcion para consultar un producto.
 */
void consult_product()
{
    std::cout << "\n--- Consulta de producto ---" << std::endl;
    std::cout << "Ingresa el codigo del producto a consultar" << std::endl;
    int code = get_int_input("codigo:");
    int index = get_index_by_code(code);

    if (index == -1) // si no se encontro producto
    {
        std::cout << "Producto con codigo no encontrado" << std::endl;
        return;
    }
    std::cout << "Informacion del producto:" << std::endl;
    print_index(index);
}

/**
 * Funcion para actualizar el inventario de un producto
 */
void update_inventory()
{
    std::cout << "\n--- Actualizar inventario ---" << std::endl;
    std::cout << "Ingresa el codigo del producto a actualizar" << std::endl;
    int code = get_int_input("codigo:");
    int index = get_index_by_code(code);

    if (index == -1) // si no se encontro producto
    {
        std::cout << "Producto con codigo no encontrado" << std::endl;
        return;
    }
    std::cout << "Producto: " << names[index] << " Stock actual: " << stocks[index] << std::endl;
    std::cout << "Ingresa la cantidad a incrementar o decrementar (Numero positivo o negativo)" << std::endl;
    int quantity = get_int_input("cantidad:");

    if (stocks[index] + quantity < 0) // si la cantidad queda en negativo
    {
        std::cout << "[Error] El numero despues del decremento no puede ser negativo." << std::endl;
        return;
    }
    stocks[index] += quantity;

    std::cout << "Se actualizo el stock a " << stocks[index] << std::endl;
}

/**
 * Funcion para actualizar el inventario de un producto
 */
void update_inventory_by_ubication()
{
    std::cout << "\n--- Actualizar inventario (ubication version) ---" << std::endl;
    std::string ubication;
    std::cout << "Ingresa la ubicacion del producto a actualizar" << std::endl;
    std::cin >> ubication;
    int index = find_string_in_array(ubication, ubications, elementCount);
    if (index == -1) // si no se encontro producto
    {
        std::cout << "Producto con codigo no encontrado" << std::endl;
        return;
    }
    std::cout << "Producto: " << names[index] << " Stock actual: " << stocks[index] << std::endl;
    std::cout << "Ingresa la cantidad a incrementar o decrementar (Numero positivo o negativo)" << std::endl;
    int quantity = get_int_input("cantidad:");

    if (stocks[index] + quantity < 0) // si la cantidad queda en negativo
    {
        std::cout << "[Error] El numero despues del decremento no puede ser negativo." << std::endl;
        return;
    }
    stocks[index] += quantity;

    std::cout << "Se actualizo el stock a " << stocks[index] << std::endl;
}

/**
 * Funcion para imprimir en consolar todos los productos en un formato de tabla.
 */
void products_report()
{
    std::cout << "\n--- Reporte Completo ---" << std::endl;

    // Table Header
    std::cout << "┌───────────────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "|";
    std::cout << std::left << std::setw(10) << "Codigo" << "│";
    std::cout << std::left << std::setw(30) << "Nombre" << "│";
    std::cout << std::right << std::setw(10) << "Stock" << "│";
    std::cout << std::right << std::setw(10) << "Precio" << "│";
    std::cout << std::right << std::setw(10) << "Ubicacion" << "│" << std::endl;

    // Table Middle
    std::cout << "├───────────────────────────────────────────────────────────────────────────┤" << std::endl;

    for (int i = 0; i < elementCount; i++)
    {
        // Make Row
        std::cout << "|";
        std::cout << std::left << std::setw(10) << codes[i] << "|";
        std::cout << std::left << std::setw(30) << names[i] << "|";
        std::cout << std::right << std::setw(10) << stocks[i] << "|";
        std::cout << std::right << std::setw(1) << "$" << std::setw(9) << std::fixed << std::setprecision(2) << prices[i] << "|";
        std::cout << std::right << std::setw(9) << std::fixed << std::setprecision(2) << ubications[i] << "|" << std::endl;
    }
    // Table footer
    std::cout << "└───────────────────────────────────────────────────────────────────────────┘" << std::endl;

    std::cout << "--- Fin del Reporte ---" << std::endl;
}

/**
 * Funcion para imprimir en consolar todos los productos con bajo stock en un formato de tabla.
 */
void products_stock_report()
{
    std::cout << "\n--- Reporte de bajo stock ---" << std::endl;

    // Table Header
    std::cout << "┌───────────────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "|";
    std::cout << std::left << std::setw(10) << "Codigo" << "│";
    std::cout << std::left << std::setw(30) << "Nombre" << "│";
    std::cout << std::right << std::setw(10) << "Stock" << "│";
    std::cout << std::right << std::setw(10) << "Precio" << "│";
    std::cout << std::right << std::setw(10) << "Ubicacion" << "│" << std::endl;

    // Table Middle
    std::cout << "├───────────────────────────────────────────────────────────────────────────┤" << std::endl;

    for (int i = 0; i < elementCount; i++)
    {
        // solo mostrar los que sean menores a 10 en el stock
        if (stocks[i] < 10)
        {
            // Make Row
            std::cout << "|";
            std::cout << std::left << std::setw(10) << codes[i] << "|";
            std::cout << std::left << std::setw(40) << names[i] << "|";
            std::cout << std::right << std::setw(10) << stocks[i] << "|";
            std::cout << std::right << std::setw(1) << "$" << std::setw(9) << std::fixed << std::setprecision(2) << prices[i] << "|" << std::endl;
            std::cout << std::right << std::setw(9) << std::fixed << std::setprecision(2) << ubications[i] << "|" << std::endl;
        }
    }
    // Table footer
    std::cout << "└───────────────────────────────────────────────────────────────┘" << std::endl;

    std::cout << "--- Fin del Reporte stock ---" << std::endl;
}

/**
 * Funcion para imprimir en consola el producto mas caro.
 */
void highest_price_product()
{
    int index = get_highest_price_product_index();
    std::cout << "\n--- Producto mas caro ---" << std::endl;

    std::cout << "El producto más caro es: " << names[index] << " con un precio de " << prices[index] << std::endl;
}

/**
 * Funcion para imprimir en consola el producto mas barato
 */
void lowest_price_product()
{
    int index = get_lowest_price_product_index();
    std::cout << "\n--- Producto mas barato ---" << std::endl;

    std::cout << "El producto más barato es: " << names[index] << " con un precio de " << prices[index] << std::endl;
}

/**
 * Función con validaciones para obtener un valor tipo int desde la consola.
 * @param prompt Breve mensaje antes de insertar el input
 * @return int numero ingresado desde consola.
 */
int get_int_input(std::string prompt)
{
    bool valid_input = false;
    int input;
    do
    {
        std::string temp;
        std::cout << prompt;
        std::getline(std::cin, temp);
        try
        {
            try
            {
                input = std::stoi(temp);
            }
            catch (std::out_of_range e) // validar rango de numero (rango -2,147,483,648 / 2,147,483,647)
            {
                std::cout << "[Error] Debe ingresar un número de menor tamaño" << std::endl;
                continue;
            }
        }
        catch (std::invalid_argument e) // Validar numeros
        {
            std::cout << "[Error] Debe ingresar un número" << std::endl;
            continue;
        }

        valid_input = true;
    } while (!valid_input);
    return input;
}

/**
 * Función con validaciones para obtener un valor tipo float desde la consola.
 * @param prompt Breve mensaje antes de insertar el input
 * @return int numero ingresado desde consola.
 */
float get_float_input(std::string prompt)
{
    bool valid_input = false;
    float input;
    do
    {
        std::string temp;
        std::cout << prompt;
        std::getline(std::cin, temp);
        try
        {
            try
            {
                input = std::stof(temp);
            }
            catch (std::out_of_range e) // validar rango de numero (rango -2,147,483,648 / 2,147,483,647)
            {
                std::cout << "[Error] Debe ingresar un número de menor tamaño" << std::endl;
                continue;
            }
        }
        catch (std::invalid_argument e) // Validar numeros
        {
            std::cout << "[Error] Debe ingresar un número" << std::endl;
            continue;
        }

        valid_input = true;
    } while (!valid_input);
    return input;
}

/**
 * Obtiene el indice de un producto a partir del codigo.
 *
 * @param code El codigo del producto
 * @return int el indice del producto.
 */
int get_index_by_code(int code)
{
    return find_int_in_array(code, codes, elementCount);
}

/**
 * Regresa el indice del producto con el precio mas alto.
 * En caso de duplicidad se regresa el primer elemento.
 */
int get_highest_price_product_index()
{
    return get_highest_in_array(prices, elementCount);
}

/**
 * Regresa el indice del producto con el precio mas bajo
 * En caso de duplicidad se regresa el primer elemento.
 */
int get_lowest_price_product_index()
{
    return get_lowest_in_array(prices, elementCount);
}

/**
 * Imprime en consola un producto a partir de su indice
 *
 * @param index indice del producto
 */
void print_index(int index)
{

    std::cout << "┌─────────────────────────────────────────┐" << std::endl;
    std::cout << "│ Codigo:" << codes[index] << std::endl;
    std::cout << "│ Nombre:" << names[index] << std::endl;
    std::cout << "│ Stock:" << stocks[index] << std::endl;
    std::cout << "│ Precio:" << prices[index] << std::endl;
    std::cout << "└─────────────────────────────────────────┘" << std::endl;
}

/**
 * Espera la entrada de una linea en la consola por parte del usuario
 */
void wait_enter()
{
    std::cout << "[Enter to continue . . .]";
    std::getchar();
}

/**
 * Funciones generales
 */
// TODO: podria hacerse mejor con generico . . .
// template <typename T>
int find_int_in_array(int element, int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (element == array[i])
        {
            return i;
        }
    }
    return -1;
}

int find_string_in_array(std::string element, std::string *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (element == array[i])
        {
            return i;
        }
    }
    return -1;
}

int get_highest_in_array(int *array, int size)
{
    int highest_index = 0;
    for (int i = 1; i < size; i++)
    {
        if (array[i] > array[highest_index])
        {
            highest_index = i;
        }
    }
    return highest_index;
}

int get_highest_in_array(float *array, int size)
{
    int highest_index = 0;
    for (int i = 1; i < size; i++)
    {
        if (array[i] > array[highest_index])
        {
            highest_index = i;
        }
    }
    return highest_index;
}

int get_lowest_in_array(float *array, int size)
{
    int lowest_index = 0;
    for (int i = 1; i < size; i++)
    {
        if (array[i] < array[lowest_index])
        {
            lowest_index = i;
        }
    }
    return lowest_index;
}

int get_number_lines(std::ifstream &file)
{
    int counter = 0;
    std::string aux;

    file.clear();  // restart the file
    file.seekg(0); // return to line 0

    while (getline(file, aux))
    {
        counter++;
    }

    file.clear();  // restart file
    file.seekg(0); // return to line 0

    return counter;
}

void load_data_from_file()
{

    std::ifstream file(FILE_PATH);
    elementCount = get_number_lines(file) - 1;

    std::string temp;
    std::string line;
    std::getline(file, line); // leemos primera linea para quitar el header

    if (!file.is_open())
    {
        std::cout << "[warning] No se pudo cargar inventario, se creara un nuevo archivo. (Los archivos estan en el data, y debe llevar el nombre de invenario.txt)" << std::endl;
    }
    for (int i = 0; i < elementCount; i++)
    {
        std::getline(file, line);
        std::string temp; // string auxiliar para el parse de int
        std::stringstream ss_line(line);

        getline(ss_line, temp, FILE_DELIMITER); // get code
        codes[i] = std::stoi(temp);             // parse to int

        getline(ss_line, names[i], FILE_DELIMITER); // get name

        getline(ss_line, temp, FILE_DELIMITER); // get quantity
        stocks[i] = std::stoi(temp);            // parse to int

        getline(ss_line, temp, FILE_DELIMITER); // get price
        prices[i] = std::stof(temp);            // parse to float

        getline(ss_line, ubications[i], FILE_DELIMITER); // get ubications
    }
}

void save_data_to_file()
{

    // ingresamos el header
    std::string header = "Código,Nombre,Cantidad,Precio,Ubicación\n";
    std::ofstream outfile(FILE_PATH, std::ofstream::binary);

    // write to outfile
    outfile.write(header.c_str(), header.size());
    for (int i = 0; i < elementCount; i++)
    {
        std::string aux;
        std::stringstream StrStream;
        StrStream << codes[i] << "," << names[i] << "," << stocks[i] << "," << std::to_string(prices[i]) << "," << ubications[i] + "\n";
        aux = StrStream.str();
        outfile.write(aux.c_str(), aux.size());
        std::cout << "[info] Datos Guardados correctamente" << std::endl;
    }

    outfile.close();
}

void register_new_product()
{
    if (elementCount >= 100)
    {
        std::cout << "=== Maximo de elementos alcanzados === " << std::endl;
        return;
    }

    std::cout << "=== Registrar producto === " << std::endl;
    int code;
    do
    {
        std::cout << "Ingrese el codigo" << std::endl;
        code = get_int_input("codigo:");
        if (get_index_by_code(code) != -1)
        {
            std::cout << "=== ya hay un producto con ese codigo === " << std::endl;
        }
    } while (get_index_by_code(code) != -1);

    std::cout << "Ingrese el nombre" << std::endl;
    std::cout << "nombre:";
    std::string nombre;
    std::cin >> nombre;

    std::cout << "Ingrese el stock" << std::endl;
    int stock = get_int_input("Stock:");
    std::cout << "Ingrese el precio" << std::endl;
    float price = get_float_input("Price:");

    std::cout << "Ingrese la ubicacion" << std::endl;
    std::cout << "ubicacion:";
    std::string ubicacion;
    std::cin >> ubicacion;

    int new_index = elementCount;
    if (new_index < 0)
    {
        new_index = 0;
    }

    codes[new_index] = code;
    names[new_index] = nombre;
    stocks[new_index] = stock;
    prices[new_index] = price;
    ubications[new_index] = ubicacion;
    elementCount++; // se incrementa el contador de elementos

    std::cout << "Producto registrado satisfactoriamente" << std::endl;
    std::cout << "El index es: " << new_index << std::endl;
}