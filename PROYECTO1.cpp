

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Cajero {
private:
    string nip;
    string contra;
    double saldo;
    vector<string> movimientos;

public:
    Cajero(string _nip, string _contra, double _saldo) : nip(_nip), contra(_contra), saldo(_saldo) {}

    bool iniciarSesion(const string& _nip, const string& _contra) const {
        return nip == _nip && contra == _contra;
    }

    void consultarSaldo() {
        cout << "Saldo actual: $" << saldo << endl;
        movimientos.push_back("Consulta de saldo: $" + to_string(saldo));
    }


    void retirar(double cantidad) {
        if (cantidad <= saldo) {
            saldo -= cantidad;
            cout << "Has retirado: $" << cantidad << endl;
            movimientos.push_back("Retiro: $" + to_string(cantidad));
        }
        else {
            cout << "Saldo insuficiente." << endl;
        }
    }

    void depositar(double cantidad) {
        saldo += cantidad;
        cout << "Has depositado: $" << cantidad << endl;
        movimientos.push_back("Depósito: $" + to_string(cantidad));
    }

    void transferir(double cantidad, const string& cuentaDestino) {
        if (cantidad > 9000) {
            cout << "No se puede transferir más de $9000 diarios." << endl;
            return;
        }
        if (cantidad <= saldo) {
            saldo -= cantidad;
            cout << "Has transferido: $" << cantidad << " a la cuenta: " << cuentaDestino << endl;
            movimientos.push_back("Transferencia a " + cuentaDestino + ": $" + to_string(cantidad));
        }
        else {
            cout << "Saldo insuficiente para la transferencia." << endl;
        }
    }

    void pagarServicio(const string& servicio, double cantidad) {
        if (cantidad <= saldo) {
            saldo -= cantidad;
            cout << "Has pagado " << servicio << " por: $" << cantidad << endl;
            movimientos.push_back("Pago de " + servicio + ": $" + to_string(cantidad));
        }
        else {
            cout << "Saldo insuficiente para pagar " << servicio << "." << endl;
        }
    }

    void cambiarNip(const string& nuevoNip) {
        nip = nuevoNip;
        cout << "NIP cambiado exitosamente." << endl;
        movimientos.push_back("Cambio de NIP.");
    }

    void consultarMovimientos() const {
        cout << "Últimos movimientos:" << endl;
        for (const auto& mov : movimientos) {
            cout << "- " << mov << endl;
        }
    }

    void admin() {
        double aux;
        cout << "Bienvenido Administrador " << endl;
        cout << "INDIQUE LA CANTIDAD DE DINERO QUE DESEA RECARGAR AL CAJERO: ";
        cin >> aux;
        depositar(aux);
    }
};

int main() {
    Cajero cajero("1234", "Contra1", 1000);  // NIP y contra y saldo inicial
    string nip, contra, cuentaDestino, servicio;
    double cantidad;
    int opcion;

    cout << "------------------------------------------------------------" << endl;
    cout << "Bienvenido al cajero automático." << endl;
    cout << "Introduce tu NIP: ";
    cin >> nip;
    cout << "Introduce tu contraseña: ";
    cin >> contra;
    cout << "------------------------------------------------------------" << endl;

    if (cajero.iniciarSesion(nip, contra)) {
        do {
            cout << "\n--- Menú de opciones ---\n";
            cout << "1. Consultar saldo\n";
            cout << "2. Retirar dinero\n";
            cout << "3. Depositar dinero\n";
            cout << "4. Transferir dinero\n";
            cout << "5. Pagar servicios\n";
            cout << "6. Cambiar NIP\n";
            cout << "7. Consultar últimos movimientos\n";
            cout << "8. Administrador (recargar efectivo)\n";
            cout << "9. Salir\n";
            cout << "Elige una opción: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
                cajero.consultarSaldo();
                break;
            case 2:
                cout << "Cantidad a retirar: ";
                cin >> cantidad;
                cajero.retirar(cantidad);
                break;
            case 3:
                cout << "Cantidad a depositar: ";
                cin >> cantidad;
                cajero.depositar(cantidad);
                break;
            case 4:
                cout << "Cantidad a transferir: ";
                cin >> cantidad;
                cout << "Cuenta destino: ";
                cin >> cuentaDestino;
                cajero.transferir(cantidad, cuentaDestino);
                break;
            case 5:
                cout << "Servicio a pagar (CFE, Luz, Agua, Internet): ";
                cin >> servicio;
                cout << "Cantidad a pagar: ";
                cin >> cantidad;
                cajero.pagarServicio(servicio, cantidad);
                break;
            case 6:
                cout << "Introduce tu nuevo NIP: ";
                cin >> nip;
                cajero.cambiarNip(nip);
                break;
            case 7:
                cajero.consultarMovimientos();
                break;
            case 8:
                cajero.admin();  // Opción para el administrador
                break;
            case 9:
                cout << "Saliendo del cajero. ¡Gracias por usar nuestros servicios!" << endl;
                break;
            default:
                cout << "Opción no válida." << endl;
            }
        } while (opcion != 9);
    }
    else {
        cout << "NIP o contraseña incorrectos." << endl;
        cout << "------------------------------------------------------------" << endl;
    }

    return 0;
}


