#ifndef _ENEMIGO_H
#define _ENEMIGO_H

class Enemigo{
public:
      Enemigo(SDL_Render* render, int id);
      ~Enemigo();
      void actualizar(int posx, int posy);
      void renderizar();
private:
      int id;
      int posx;
      int posy;
};

#endif
