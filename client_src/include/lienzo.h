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
};

#endif //LIENZO_H
