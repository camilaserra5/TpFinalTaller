#ifndef MANEJADOR_PARTIDAS_H
#define MANEJADOR_PARTIDAS_H

#include "thread.h"
#include "servidor.h"
#include <atomic>
#include <string>
#include <map>
#include <vector>
#include "map.h"
#include "protocolo.h"
#include "../include/thclient.h"
#include "../include/partida.h"
#include "configuracionPartida.h"

class ManejadorPartidas : public ISerializable {
public:
    /*
      * creara la clase manejador de partidas dejandola valida para uso
      * los paremotrs deben estar inicializados y ser validos
    */
    ManejadorPartidas(std::string rutaMapas, std::map<std::string, std::string> &mapas,
                      ConfiguracionPartida& configuracion);
    /*
      * liberara a la clase con sus recursos
    */
    ~ManejadorPartidas();
    /*
      * agrega aun nuevo cliente
    */
    void nuevoCliente(ThClient *cliente);
    /*
      * cierra las partidas;
    */
    void cerrarPartidas();
    /*
      * crea la partida si es que esta ya no existe
      * los parametros deben ser validos
    */
    void crearPartida(std::string &nombreJugador, int &cant_jugadores,
                      std::string &nombre_partida, std::string &archivoMapa,
                      int &screenWidth);
    /*
      * agerga un clinete a la partida si es que esta no arranco
    */
    void agregarClienteAPartida(std::string &nombreJugador,
                                std::string &nombre_partida, ThClient *cliente);
    /*
      * serializa la clase y devuelve la informacion correspondiente
    */
    std::vector<char> serializar();
    /*
      * deserializa la clase y la deja en valores previos
    */
    void deserializar(std::vector<char> &serializado) {}
    /*
      * ejecuta el rpograma
    */
    void run();
    /*
      * elimina las partidas termiandas
    */
    void eliminarPartidasTerminadas();
    /*
      * busca en el mapa de archivos mapa y devuelve si esta, sino esta
      * devuelve una exception
    */
    Map buscarMapa(std::string archivoMapa, int &anchoPantalla);
    /*
      * agrega un mapa
    */
    void agregarMapa(std::string nombreMapa, std::string archivoMapa);
    /*
      * cierra las partidas 
    */
    void cerrar();

private:
    std::map<std::string, Partida *> partidas;
    std::atomic<bool> esta_corriendo;
    std::map<std::string, std::string> &mapas;
    std::string rutaMapas;
    ConfiguracionPartida configuracion;
};

#endif
