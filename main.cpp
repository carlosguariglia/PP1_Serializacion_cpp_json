/*  Consigna: Usar una IA para crear una clase y serializarla en JSON.
    y el proceso inverso.

    La ia usada fue chatgpt.
    el prompt fue el siguiente:
        "necesito que crees una clase simple a modo de ejemplo en c++ de un auto, 
        con propiedades tipicas y funciones"
    luego continue con el siguiente prompt:
        "ahora necesito que hagas tambien en c++ serializar para resistir a un archivo .json
         y tambien el proceso inverso de deserealizarlo"

    A modo de practica de compilacion multiarchivo y para una mejor visualizacion se 
    utiliza la libreria consoleUtils.hpp que contiene funciones para limpiar la consola
    y pausar el programa en cualquier sistema operativo.
*/


#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

#include "consoleUtils.hpp"

using json = nlohmann::json;
using namespace std;

class Auto {
private:
    string marca;
    string modelo;
    int velocidad;

public:
    // Constructor
    Auto(string m = "", string mod = "", int v = 0) : marca(m), modelo(mod), velocidad(v) {}

    // Funciones para obtener propiedades
    string getMarca() const { return marca; }
    string getModelo() const { return modelo; }
    int getVelocidad() const { return velocidad; }

    // Función para establecer propiedades
    void setMarca(string m) { marca = m; }
    void setModelo(string mod) { modelo = mod; }
    void setVelocidad(int v) { velocidad = v; }

    // Función para acelerar
    void acelerar(int incremento) {
        velocidad += incremento;
        cout << "El auto ha acelerado. Velocidad actual: " << velocidad << " km/h" << endl;
    }

    // Función para frenar
    void frenar() {
        velocidad = 0;
        if (velocidad < 0) velocidad = 0;
        cout << "El auto ha frenado. Velocidad actual: " << velocidad << " km/h" << endl;
    }

    // Función para mostrar información del auto
    void mostrarInfo() const {
        cout << "Marca: " << marca << ", Modelo: " << modelo << ", Velocidad: " << velocidad << " km/h" << endl;
    }

    // Serializar a JSON
    json serializar() const {
        return json{{"marca", marca}, {"modelo", modelo}, {"velocidad", velocidad}};
    }

    // Deserializar desde JSON
    static Auto deserializar(const json& j) {
        Auto a;
        a.setMarca(j.at("marca").get<string>());
        a.setModelo(j.at("modelo").get<string>());
        a.setVelocidad(j.at("velocidad").get<int>());
        return a;
    }
};

// Función para guardar el JSON en un archivo
void guardarEnArchivo(const string& nombreArchivo, const json& j);
// Función para leer el JSON desde un archivo
json leerDeArchivo(const string& nombreArchivo);


int main() {
    int opcion;

    clearConsole();
    do {
        cout << endl;
        cout << " MENU DE OPCIONES" << endl;
        cout << " 1. Crear un nuevo auto (y guardar a Json)" << endl;
        cout << " 2. Leer el objeto Auto desde el archivo" << endl;
        cout << " 3. Salir" << endl;
        cout << " Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                // Crear un nuevo auto
                string marca, modelo;
                int velocidad;
                cout << " Ingrese la marca: ";
                cin >> marca;
                cout << " Ingrese el modelo: ";
                cin >> modelo;
                cout << " Ingrese la velocidad: ";
                cin >> velocidad;

                Auto nuevoAuto(marca, modelo, velocidad);

                clearConsole();
                nuevoAuto.mostrarInfo();
                // Serializar el objeto a JSON
                json autoJSON = nuevoAuto.serializar();
                // Guardar el JSON en un archivo
                guardarEnArchivo("auto.json", autoJSON);
                int opcion2;
                do {
                    cout << endl;
                    cout << " OPCIONES del objeto" << endl;
                    cout << " 1. Acelerar" << endl;
                    cout << " 2. Frenar" << endl;
                    cout << " 3. Mostrar informacion" << endl;
                    cout << " 4. Salir" << endl;
                    cout << " Ingrese una opcion: ";
                    cin >> opcion2;
                    switch (opcion2) {
                        case 1: {
                            int incremento;
                            cout << " Ingrese el incremento de velocidad: ";
                            cin >> incremento;
                            clearConsole();
                            nuevoAuto.acelerar(incremento);
                            break;
                        }
                        case 2: {
                            clearConsole();
                            nuevoAuto.frenar();
                            break;
                        }
                        case 3: {
                            clearConsole();
                            nuevoAuto.mostrarInfo();
                            break;
                        }
                        case 4: {
                            clearConsole();
                            break;
                        }
                        default: {
                            clearConsole();
                            cout << " Opcion no valida" << endl;
                            break;
                        }
                    }
                } while (opcion2 != 4);
                break;
            }
            case 2: {
                // Leer el objeto Auto desde el archivo
                auto autoLeido = leerDeArchivo("auto.json");
                Auto nuevoAuto = Auto::deserializar(autoLeido);
                clearConsole();
                nuevoAuto.mostrarInfo();
                break;
            }
            case 3: {
                // Salir
                cout << " Saliendo..." << endl;
                break;
            }
            default: {
                clearConsole();
                cout << " Opcion no valida" << endl;
                break;
            }
        }
    } while (opcion != 3);

    
    /* // Crear un objeto de la clase Auto
       Auto miAuto("Toyota", "Corolla", 50);
       // Serializar el objeto a JSON
       json autoJSON = miAuto.serializar();
       // Guardar el JSON en un archivo
       guardarEnArchivo("auto.json", autoJSON);
       // Leer el JSON del archivo
       json autoLeido = leerDeArchivo("auto.json");
       // Deserializar el objeto Auto desde JSON
       Auto nuevoAuto = Auto::deserializar(autoLeido);

       Mostrar la información del nuevo auto deserializado
       nuevoAuto.mostrarInfo();
    */
    return 0;
}

// Función para guardar el JSON en un archivo
void guardarEnArchivo(const string& nombreArchivo, const json& j) {
    ofstream archivo(nombreArchivo);
    archivo << j.dump(4); // Escribe el JSON con una indentación de 4 espacios
    archivo.close();
}

// Función para leer el JSON desde un archivo
json leerDeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    json j;
    archivo >> j;
    archivo.close();
    return j;
}