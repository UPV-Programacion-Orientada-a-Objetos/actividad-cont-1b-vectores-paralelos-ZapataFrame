#include <iostream>
#include <iomanip>   // Libreria para manejar mejor la IO de la consola.
#include <fstream>   // Libreria para manipular el flujo de archivos
#include <sstream>   // Libreria para manejar strings como flujo.
#include <stdexcept> // Libreria para crear exceptiones.

// Prototypes
int get_menu_option();

// options
void consult_product();
void update_inventory();
void update_inventory_by_ubication();
void products_report();
void register_new_product();
void products_stock_report();
void highest_price_product();
void lowest_price_product();

// files methods
void create_file(std::string path);
void load_data_from_file(std::string file_path);
void save_data_to_file(std::string file_path);

// methods
void print_index(int index);
void wait_enter();

int get_int_input(std::string prompt);
int get_positive_int_input(std::string prompt);
float get_float_input(std::string prompt);
int get_float_int_input(std::string prompt);
std::string get_string_input(std::string prompt);

int get_index_by_code(int code);

int get_highest_price_product_index();
int get_lowest_price_product_index();

// Auxiliares
int find_int_in_array(int element, int *array, int size);
int find_string_in_array(std::string element, std::string *array, int size);

int get_highest_in_array(float *array, int size);
int get_highest_in_array(int *array, int size);

int get_lowest_in_array(float *array, int size);

int count_values_from_splitted_string(std::string string, char delimiter);

bool is_int(std::string string);
bool is_float(std::string string);

// Messages
void print_message(std::string type, std::string message);

// Constantes archivos
const char FILE_DELIMITER = ',';
const std::string FILE_PATH = "./data/inventario.txt";
const int MAX_ELEMENTS = 100;

// Variables Globales
int elementCount = 0;
int codes[MAX_ELEMENTS];
std::string names[MAX_ELEMENTS];
int stocks[MAX_ELEMENTS];
float prices[MAX_ELEMENTS];
std::string ubications[MAX_ELEMENTS];

int main()
{
    load_data_from_file(FILE_PATH);
    std::cout << "\n--- Bienvenido al Sistema de Inventario de \"El Martillo\" ---" << std::endl;
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
            is_program_running = false;
            save_data_to_file(FILE_PATH); // guarda los valores
            std::cout << "Bye!" << std::endl;
            exit(EXIT_SUCCESS);
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
    std::cout << "├─────────────────────────────────────────" << std::endl;
    std::cout << "│ 5) Registrar nuevo producto" << std::endl;
    std::cout << "│ 6) Actualizar inventario por ubicacion" << std::endl;
    std::cout << "│ 7) Generar reporte de bajo stock" << std::endl;
    std::cout << "│ 8) Encontrar el producto más barato" << std::endl;
    std::cout << "│ 0) Guardar y salir" << std::endl;
    std::cout << "└─────────────────────────────────────────┘" << std::endl;

    // obtener opcion desde input
    bool valid_input = false;
    int opt;

    // Validar opcion
    do
    {
        opt = get_int_input("Seleccione una opción [0-8]:");

        if (opt >= 0 && opt <= 8)
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
    std::cout << "Ingresa la ubicacion del producto a actualizar" << std::endl;
    std::string ubication = get_string_input("Ubicacion:");

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
    std::cout << "Ingresa el umbral, solo se mostraran productos con menor stock que el umbral" << std::endl;

    int umbral = get_positive_int_input("Umbral:");
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
        if (stocks[i] < umbral)
        {
            // Make Row
            std::cout << "|";
            std::cout << std::left << std::setw(10) << codes[i] << "|";
            std::cout << std::left << std::setw(30) << names[i] << "|";
            std::cout << std::right << std::setw(10) << stocks[i] << "|";
            std::cout << std::right << std::setw(1) << "$" << std::setw(9) << std::fixed << std::setprecision(2) << prices[i] << "|";
            std::cout << std::right << std::setw(9) << std::fixed << std::setprecision(2) << ubications[i] << "|" << std::endl;
        }
    }
    // Table footer
    std::cout << "└───────────────────────────────────────────────────────────────────────────┘" << std::endl;

    std::cout << "--- Fin del Reporte stock ---" << std::endl;
}

/**
 * Funcion para imprimir en consola el producto mas caro.
 */
void highest_price_product()
{
    int index = get_highest_price_product_index();
    std::cout << "\n--- Producto mas caro ---" << std::endl;

    if (elementCount > 0)
    {
        std::cout << "El producto más caro es: " << names[index] << " con un precio de " << prices[index] << std::endl;
    }
    else
    {
        print_message("Info", "No hay producctos.");
    }
}

/**
 * Funcion para imprimir en consola el producto mas barato
 */
void lowest_price_product()
{
    int index = get_lowest_price_product_index();
    std::cout << "\n--- Producto mas barato ---" << std::endl;

    if (elementCount > 0)
    {
        std::cout << "El producto más barato es: " << names[index] << " con un precio de " << prices[index] << std::endl;
    }
    else
    {
        print_message("Info", "No hay producctos.");
    }
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
                print_message("Error", "Debe ingresar un número de menor tamaño.");
                continue;
            }
        }
        catch (std::invalid_argument e) // Validar numeros
        {
            print_message("Error", "Debe ingresar un número");
            continue;
        }

        valid_input = true;
    } while (!valid_input);
    return input;
}

int get_positive_int_input(std::string prompt)
{
    int input;
    do
    {
        input = get_int_input(prompt);
        if (input < 0)
        {
            print_message("Error", "Debe ingresar un número positivo.");
        }

    } while (input < 0);
    return input;
}
std::string get_string_input(std::string prompt)
{
    std::string input;
    bool valid_input = true;
    do
    {
        valid_input = true;
        std::cout << prompt;
        std::getline(std::cin, input);

        if (input.find(",") != std::string::npos)
        {
            print_message("Error", "No se puede utilizar el caracter ('," + std::to_string(FILE_DELIMITER) + "').");
            valid_input = false;
        }
        if (input.empty())
        {
            print_message("Error", "Se debe ingresar texto");
            valid_input = false;
        }

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
            catch (std::out_of_range e) // validar rango de numero (rango ±3.4E +/- 38)
            {
                print_message("Error", "Debe ingresar un número de menor tamaño.");
                continue;
            }
        }
        catch (std::invalid_argument e) // Validar numeros
        {
            print_message("Error", "Debe ingresar un número");
            continue;
        }

        valid_input = true;
    } while (!valid_input);
    return input;
}
float get_positive_float_input(std::string prompt)
{
    float input;
    do
    {
        input = get_float_input(prompt);
        if (input < 0)
        {
            print_message("Error", "Debe ingresar un número positivo.");
        }

    } while (input < 0);
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
    std::cout << "│ Ubicacion:" << ubications[index] << std::endl;
    std::cout << "└─────────────────────────────────────────┘" << std::endl;
}

/**
 * Espera la entrada de una linea en la consola por parte del usuario
 */
void wait_enter()
{
    std::cout << "[Enter to continue . . .]";
    std::string temp;
    getline(std::cin, temp);
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

void load_data_from_file(std::string file_path)
{
    std::ifstream file(file_path);
    print_message("Info", "Intentando abrir el archivo: " + file_path);

    if (!file.is_open())
    {
        print_message("Warning", "No se pudo cargar inventario.");
        create_file(file_path);
        print_message("Info", "Archivo creado: " + file_path);
        file.open(file_path);
    }

    int number_lines = get_number_lines(file);
    if (number_lines > MAX_ELEMENTS)
    {
        print_message("Error", "No se pudo cargar inventario, se exedio el numero de elementos. Maximo de elementos:" + std::to_string(MAX_ELEMENTS));
        exit(EXIT_FAILURE);
        return;
    }

    int products_loaded = 0;
    int products_ommited = 0;

    std::string line;
    for (int i = 1; i <= number_lines; i++)
    {
        std::string error_message;
        int field;
        std::getline(file, line);

        // validar datos
        try
        {
            int values_count = count_values_from_splitted_string(line, FILE_DELIMITER);

            if (values_count != 5)
                throw std::invalid_argument("No contiene todos los valores necesarios.");

            std::string temp; // string auxiliar para el parse
            std::stringstream ss_line(line);

            getline(ss_line, temp, FILE_DELIMITER); // get code

            if (!is_int(temp))
                throw std::invalid_argument("Contiene un valor no int en el codigo.");

            if (find_int_in_array(std::stoi(temp), codes, products_loaded) != -1)
                throw std::invalid_argument("Contiene un codigo ya ingresado.");

            codes[products_loaded] = std::stoi(temp); // parse to int

            getline(ss_line, names[products_loaded], FILE_DELIMITER); // get name

            getline(ss_line, temp, FILE_DELIMITER); // get quantity

            if (!is_int(temp))
                throw std::invalid_argument("Contiene un valor no int en el stock.");

            if (std::stoi(temp) < 0)
                throw std::invalid_argument("Contiene un valor negativo en el stock.");

            stocks[products_loaded] = std::stoi(temp); // parse to int

            getline(ss_line, temp, FILE_DELIMITER); // get price
            if (!is_float(temp))
                throw std::invalid_argument("Contiene un valor no float en el precio.");

            if (std::stof(temp) < 0)
                throw std::invalid_argument("Contiene un valor negativo en el precio.");

            prices[products_loaded] = std::stof(temp); // parse to float

            getline(ss_line, ubications[products_loaded], FILE_DELIMITER); // get ubicationss
            products_loaded++;
        }
        catch (std::exception &e)
        {
            if (i != 1)
            {
                print_message("Warning", "Se omitio la linea numero " + std::to_string(i) + " debido a que " + e.what());
            }
            else
            {
                print_message("Warning", "Se omitio la linea numero " + std::to_string(i) + " debido a que " + e.what() + " Aunque podria ser el header");
            }
        }
    }
    file.close();
    products_ommited = number_lines - products_loaded;
    elementCount += products_loaded;
    print_message("Info", "Numero de productos cargados: " + std::to_string(products_loaded));
    print_message("Info", "Numero de productos omitidos: " + std::to_string(products_ommited));
}

int count_values_from_splitted_string(std::string string, char delimiter)
{
    std::stringstream ss_line(string);
    std::string aux;
    int count = 0;
    while (getline(ss_line, aux, delimiter))
    {
        count++;
    }
    return count;
}

void save_data_to_file(std::string file_path)
{

    // ingresamos el header
    std::string header = "Código,Nombre,Cantidad,Precio,Ubicación\n";
    std::ofstream outfile(file_path);

    if (!outfile)
    {
        print_message("Error", "Archivo de guardado inaccesible en la ruta: " + file_path + "\nSi desea guardar los datos correctamente actualice los permisos y después presione enter.");
        // print_message("Info", "Si desea guardar los datos correctamente actualice los permisos y después presione enter.");
        wait_enter();
        create_file(file_path);
    }

    // write to outfile
    outfile.write(header.c_str(), header.size());
    for (int i = 0; i < elementCount; i++)
    {
        // formatear linea
        std::string line = "";
        line.append(std::to_string(codes[i]) + FILE_DELIMITER);  // agregar codigo
        line.append(names[i] + FILE_DELIMITER);                  // agregar nombre
        line.append(std::to_string(stocks[i]) + FILE_DELIMITER); // agregar stock
        line.append(std::to_string(prices[i]) + FILE_DELIMITER); // agregar precio
        line.append(ubications[i]);                              // agregar ubicacion
        line.append("\n");                                       // new line

        // escribir linea
        outfile.write(line.c_str(), line.size());
    }
    outfile.close();
    print_message("Info", "Datos guardados correctamente.");
}

/**
 * Funcion para crear un archivo a partir de una ruta.
 * @param path String de ruta con nombre y extension. Ej './data/example.txt'.
 */
void create_file(std::string path)
{
    print_message("Info", "Intentando crear el archivo: " + path);
    std::ofstream new_file(path);
    if (!new_file)
    {
        print_message("Error", "No se pudo crear el archivo. Verifique los permisos.");
        exit(EXIT_FAILURE);
        return;
    }
    new_file.close();
}

void register_new_product()
{
    if (elementCount >= MAX_ELEMENTS)
    {
        print_message("Error", "Operacion no permitida; Maximo de elementos alcanzados. Maximo de elementos:" + std::to_string(MAX_ELEMENTS));
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
            print_message("Error", "Ya existe un producto con este codigo. Ingrese otro.");
        }

    } while (get_index_by_code(code) != -1);

    std::cout << "Ingrese el nombre" << std::endl;
    std::string name = get_string_input("Nombre:");

    std::cout << "Ingrese el stock" << std::endl;

    int stock;
    do
    {
        stock = get_positive_int_input("Stock:");
        if (stock < 0)
            print_message("Error", "Debe ingresar un número positivo");
    } while (stock < 0);

    std::cout << "Ingrese el precio" << std::endl;
    float price = get_positive_float_input("Price:");

    std::cout << "Ingrese la ubicacion" << std::endl;
    std::string ubication = get_string_input("Ubicacion:");

    int new_index = elementCount;
    if (new_index < 0)
    {
        new_index = 0;
    }

    codes[new_index] = code;
    names[new_index] = name;
    stocks[new_index] = stock;
    prices[new_index] = price;
    ubications[new_index] = ubication;
    elementCount++; // se incrementa el contador de elementos

    print_message("Info", "Producto nuevo registrado correctamente.");
}

/**
 * Funcion para mostrar un mensaje formateado.
 * @param type Tipo de mensaje Ej Warning, Error, Info.
 * @param message Mensaje a mostrar.
 */
void print_message(std::string type, std::string message)
{
    std::cout << "[" << type << "]\t" << message << std::endl;
}

bool is_int(std::string string)
{
    if (string.empty())
    {
        return false;
    }
    try
    {
        std::stoi(string);
        return true;
    }
    catch (const std::exception &e)
    {
        // catch any error
    }
    return false;
}

bool is_float(std::string string)
{
    if (string.empty())
    {
        return false;
    }
    try
    {
        std::stof(string);
        return true;
    }
    catch (const std::exception &e)
    {
        // catch any error
    }
    return false;
}