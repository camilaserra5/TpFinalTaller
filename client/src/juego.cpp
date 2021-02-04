#include "../include/juego.h"

#define EXITO 0
#define TAMANIO_FILA 20
#define TAMANIO_COLUMNA 20
#define LARGO_PROYECTOR ANCHO_CANVAS
#define ANCHO_PROYECTOR 20
#define WOODEN_WALL_ROOT "../../editor/resources/wall2.jpg"
#define BLUE_STONE_WALL_ROOT "../../editor/resources/wall1.jpg"
#define GRAY_STONE_WALL_ROOT "../../editor/resources/wall3.jpg"
#define PUERTA_ROOT "../../editor/resources/puerta.png"




#define LOWER_TEXTURE_ROOT "../../client/resources/images/ParteInferior.png"


Juego::Juego(Ventana& ventana, Modelo& modelo): ventana(ventana), modelo(modelo) {

        this->modelo.inicializar();
        this->texturaInferior = new Textura(LOWER_TEXTURE_ROOT,
                                            this->ventana.obtener_render());
        this->corriendo = true;
}

void Juego::eventos(){
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                this->corriendo = false;
                break;

            default:
                break;

          }
    }
}
void Juego::run() {
  Map mapa (20,20);
    while(this->corriendo){
        try {
              this->clean();
              this->eventos();
              this->raycasting(mapa,this->modelo.getPlayer());
              this->renderizar();
              this->actualizar(/*1*/);
              std::chrono::milliseconds duration(100);
              std::this_thread::sleep_for(duration);
        } catch (...) {
            this->corriendo = false;
        }
    }
    this->cerrar();

}

void Juego::actualizar(/*temporal int idArma*/) {
    this->ventana.actualizar();
    this->modelo.actualizar();
}

void Juego::renderizar() {
  this->modelo.renderizar();
  this->ventana.renderizar(this->texturaInferior);
}

Juego::~Juego() {
    delete this->texturaInferior;
}

void Juego::cerrar(){
    this->corriendo = false;
    this->ventana.cerrar();
};
void Juego::clean() {
    this->ventana.limpiar();
  //  this->corriendo = false;
}

void Juego::raycasting(Map &mapaa, Player &jugador) {

// x = fila / y = columna

  int mapa[TAMANIO_FILA][TAMANIO_COLUMNA] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                       /*1*/  {1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1},
                                      /*2*/   {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
                                     /*3*/    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    /*4*/     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                   /*5*/      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*6*/       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*7*/       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*8*/       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*9*/       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*10*/      {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                                  /*11*/      {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                                /*12*/        {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                            /*13*/            {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                            /*14*/            {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                                    /*15*/    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    /*16*/    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                      /*17*/  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                      /*18*/  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                      /*19*/  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                            /* 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 */
                                            };
            SDL_Renderer *render = this->ventana.obtener_render();
            Textura* wall = new Textura(GRAY_STONE_WALL_ROOT,render);
            Posicion& posJugador = jugador.getPosicion();

            /*******PARAMETROS DE RAYCASTING********/
            double rangoDeVista = 2 * acos(0.0) / 3;//60 grados
            int ladoCelda = ANCHO_CANVAS/TAMANIO_FILA;
            double anguloPorStripe = rangoDeVista / ANCHO_CANVAS;
            double anguloJugador = jugador.getAnguloDeVista();
            double anguloRayo = anguloJugador - (rangoDeVista / 2);
            SDL_Rect wallDimension,wallDest;

            std::vector<double>& zbuffer = this->modelo.getZBuffer();
            for (int i = ANCHO_CANVAS - 1; i >= 0; i--) {
                unsigned int alturaParedProyectada = 0;
                double distancia = 0;
                int drawStart,drawEnd;
                Rayo rayo(rangoDeVista, ladoCelda, LARGO_PROYECTOR, anguloRayo,posJugador);
                rayo.verificarInterseccion(mapa,distancia,jugador);
                alturaParedProyectada = (ladoCelda / distancia) * rayo.getDistanciaProyector();
                zbuffer.push_back(distancia);
                drawStart = floor((ANCHO_CANVAS / 2) - (alturaParedProyectada / 2)) - 20;//cheuear ese ancho canvas
                drawEnd = drawStart + alturaParedProyectada;
                if (drawStart > ALTURA_CANVAS){
                    drawStart = 600 - 1;
                    drawEnd = 0;
                }
                wallDimension.x = rayo.getOffset() % 64;
                wallDimension.y = 0;
                wallDimension.w = 1;
                wallDimension.h = alturaParedProyectada;

                wallDest.x = i;
                wallDest.y = drawStart;
                wallDest.w = 1;
                wallDest.h = drawEnd - drawStart;

                wall->renderizar(&wallDimension,wallDest, 0,NULL);
              //  this->ventana->actualizar();

              //  std::chrono::milliseconds duration(20);
              //  std::this_thread::sleep_for(duration);
                anguloRayo += anguloPorStripe;
            }
            delete wall;
}
