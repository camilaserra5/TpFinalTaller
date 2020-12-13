#ifndef _CUCHILLO_H
#define _CUCHILLO_H
#include "arma.h"

class Cuchillo: public Arma{
      public:
            Cuchillo();
            ~Cuchillo();
            int atacar() override;
      private:
            int danio;
};

#endif
