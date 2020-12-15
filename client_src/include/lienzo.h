#ifndef LIENZO_H
#define LIENZO_H

class Lienzo {
private:
    int x, y;
    int ancho, alto;

public:
    Lienzo(int x, int y, int ancho, int alto);

    int getX() const;

    int getY() const;

    int getAncho() const;

    int getAlto() const;

    void actualizar(int una_x, int una_y, int un_alto, int un_ancho){
};

#endif //LIENZO_H
