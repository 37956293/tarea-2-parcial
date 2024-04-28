#include <iostream>
#include <string>

using namespace std;

struct Estudiante {
    int id;
    string nombre;
    string apellido;
    float notas[4];
    float promedio;
};

int main() {
    int N;
    cout << "Ingrese la cantidad de estudiantes: ";
    cin >> N;

    Estudiante *estudiantes = new Estudiante[N];

    // Pedir datos de los estudiantes
    for (int i = 0; i < N; i++) {
        cout << "\nIngrese datos del estudiante " << i + 1 << ":" << endl;
        cout << "ID: ";
        cin >> (estudiantes + i)->id;
        cin.ignore(); // Limpiar el buffer
        cout << "Nombres: ";
        getline(cin, (estudiantes + i)->nombre);
        cout << "Apellidos: ";
        getline(cin, (estudiantes + i)->apellido);
        cout << "Nota 1: ";
        cin >> (estudiantes + i)->notas[0];
        cout << "Nota 2: ";
        cin >> (estudiantes + i)->notas[1];
        cout << "Nota 3: ";
        cin >> (estudiantes + i)->notas[2];
        cout << "Nota 4: ";
        cin >> (estudiantes + i)->notas[3];

        // Calcular promedio
        (estudiantes + i)->promedio = ((estudiantes + i)->notas[0] + (estudiantes + i)->notas[1] + (estudiantes + i)->notas[2] + (estudiantes + i)->notas[3]) / 4.0;
    }

    // Mostrar resultados
    cout << "\nResultados:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "\nEstudiante " << i + 1 << ":" << endl;
        cout << "ID: " << (estudiantes + i)->id << endl;
        cout << "Nombre: " << (estudiantes + i)->nombre << " " << (estudiantes + i)->apellido << endl;
        cout << "Promedio: " << (estudiantes + i)->promedio << endl;
        if ((estudiantes + i)->promedio > 60) {
            cout << "Estado: Aprobado" << endl;
        } else {
            cout << "Estado: Reprobado" << endl;
        }
    }

    delete[] estudiantes; // Liberar memoria
    return 0;
}
