// Project MPI [duck managed]
// Class Bouton (src/classes/Bouton/Bouton.class.hpp)
#ifndef BOUTON_CLASS_HPP
	#define BOUTON_CLASS_HPP
    
    #include "../GraphicComponent/GraphicComponent.class.h"
    //Bouton class definition

    class Bouton : public GraphicComponent
    {
        public:
        Bouton(); //class constructor
        ~Bouton();
        void Onclick();
    };

    #endif
