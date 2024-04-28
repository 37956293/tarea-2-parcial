#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Estudiante {
    int id;
    string nombre;
    string apellido;
    float notas[4];
    float promedio;
    string resultado;
};

void crearEstudiante(fstream& archivo) {
    Estudiante estudiante;

    cout << "Ingrese ID del estudiante: ";
    cin >> estudiante.id;
    cin.ignore(); // Limpiar el buffer
    cout << "Ingrese nombres del estudiante: ";
    getline(cin, estudiante.nombre);
    cout << "Ingrese apellidos del estudiante: ";
    getline(cin, estudiante.apellido);
    cout << "Ingrese nota 1: ";
    cin >> estudiante.notas[0];
    cout << "Ingrese nota 2: ";
    cin >> estudiante.notas[1];
    cout << "Ingrese nota 3: ";
    cin >> estudiante.notas[2];
    cout << "Ingrese nota 4: ";
    cin >> estudiante.notas[3];

    // Calcular promedio
    estudiante.promedio = (estudiante.notas[0] + estudiante.notas[1] + estudiante.notas[2] + estudiante.notas[3]) / 4.0;

    // Determinar resultado
    estudiante.resultado = (estudiante.promedio > 60) ? "Aprobado" : "Reprobado";

    // Escribir en el archivo binario
    archivo.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));
}

void leerEstudiantes(fstream& archivo) {
    Estudiante estudiante;
    archivo.seekg(0, ios::beg); // Posicionarse al principio del archivo

    cout << "ID\tNombres\t\t\tApellidos\t\tPromedio\tResultado" << endl;
    cout << "------------------------------------------------------------------" << endl;

    while (archivo.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
        cout << estudiante.id << "\t" << setw(20) << left << estudiante.nombre << "\t" << setw(20) << left << estudiante.apellido << "\t" << fixed << setprecision(2) << estudiante.promedio << "\t" << estudiante.resultado << endl;
    }
}

void actualizarEstudiante(fstream& archivo, int id) {
    Estudiante estudiante;
    bool encontrado = false;

    archivo.seekg(0, ios::beg); // Posicionarse al principio del archivo

    while (!encontrado && archivo.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
        if (estudiante.id == id) {
            encontrado = true;

            cout << "Ingrese nuevos datos para el estudiante con ID " << id << ":" << endl;
            cout << "Nombres: ";
            getline(cin, estudiante.nombre);
            cout << "Apellidos: ";
            getline(cin, estudiante.apellido);
            cout << "Nota 1: ";
            cin >> estudiante.notas[0];
            cout << "Nota 2: ";
            cin >> estudiante.notas[1];
            cout << "Nota 3: ";
            cin >> estudiante.notas[2];
            cout << "Nota 4: ";
            cin >> estudiante.notas[3];

            // Calcular promedio
            estudiante.promedio = (estudiante.notas[0] + estudiante.notas[1] + estudiante.notas[2] + estudiante.notas[3]) / 4.0;

            // Determinar resultado
            estudiante.resultado = (estudiante.promedio > 60) ? "Aprobado" : "Reprobado";

            // Posicionarse en la posición donde se encontró el estudiante y actualizarlo
            archivo.seekp(-static_cast<int>(sizeof(Estudiante)), ios::cur);
            archivo.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));
        }
    }

    if (!encontrado) {
        cout << "Estudiante no encontrado." << endl;
    }
}

void borrarEstudiante(fstream& archivo, int id) {
    Estudiante estudiante;
    bool encontrado = false;

    fstream archivoTemp("temp.dat", ios::out | ios::binary); // Archivo temporal para escribir los estudiantes no borrados

    archivo.seekg(0, ios::beg); // Posicionarse al principio del archivo

    while (archivo.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
        if (estudiante.id == id) {
            encontrado = true;
            cout << "Estudiante con ID " << id << " borrado correctamente." << endl;
        } else {
            archivoTemp.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante)); // Escribir estudiantes no borrados en el archivo temporal
        }
    }

    archivo.close();
    archivoTemp.close();

    remove("notas.dat"); // Eliminar el archivo original
    rename("temp.dat", "notas.dat"); // Renombrar el archivo temporal
}

int main() {
    fstream archivo("notas.dat", ios::in | ios::out | ios::binary);

    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    int opcion;
    int id;

    do {
        cout << "\n1. Crear estudiante\n2. Leer estudiantes\n3. Actualizar estudiante\n4. Borrar estudiante\n5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                crearEstudiante(archivo);
                break;
            case 2:
                leerEstudiantes(archivo);
                break;
            case 3:
                cout << "Ingrese el ID del estudiante que desea actualizar: ";
                cin >> id;
                actualizarEstudiante(archivo, id);
                break;
            case 4:
                cout << "Ingrese el ID del estudiante que desea borrar: ";
                cin >> id;
                borrarEstudiante(archivo, id);
                break;
            case 5:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 5);

    archivo.close();

    return 0;
}
