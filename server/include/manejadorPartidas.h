#ifndef MANEJADOR_PARTIDAS_H
#define MANEJADOR_PARTIDAS_H

#include "thread.h"
#include "servidor.h"
#include "old_cliente.h"
#include <atomic>
#include <string>
#include <map>
#include <vector>
#include "map.h"

class ManejadorPartidas : public Thread, public ISerializable {
public:
    ManejadorPartidas();

    ~ManejadorPartidas();

    bool crearPartida(std::string &nombreJugador,
                      int &cant_jugadores, std::string &nombre_partida,
                      std::string &archivoMapa);

    bool agregarClienteAPartida(std::string &nombreJugador,
                                std::string &nombre_partida);

    std::vector<char> serializar();/* {
        std::vector<char> informacion;
        std::vector<char> sizePartidas = numberToCharArray(this->partidas.size());
        informacion.insert(informacion.end(), sizePartidas.begin(), sizePartidas.end());
        std::map<std::string, Servidor *>::iterator it;
        for (it = this->partidas.begin(); it != this->partidas.end(); ++it) {
            std::pair<std::string, Servidor *> pair = *it;
            std::vector<char> sizeNombre = numberToCharArray(pair.first.size());
            informacion.insert(informacion.end(), sizeNombre.begin(), sizeNombre.end());
            informacion.insert(informacion.end(), pair.first.begin(), pair.first.end());
            std::vector<char> partidaSerializada = pair.second->serializar();
            informacion.insert(informacion.end(), partidaSerializada.begin(), partidaSerializada.end());
        }
        return informacion;
    }
*/
    void deserializar(std::vector<char> &serializado) {}

    void run();

    void eliminarPartidasTerminadas();

    Map buscarMapa(std::string& archivoMapa);

    void agregarMapa(std::string archivoMapa);

private:
    std::map<std::string, Servidor *> partidas;
    std::atomic<bool> esta_corriendo;
    std::vector<std::string> mapas;

};

#endif
