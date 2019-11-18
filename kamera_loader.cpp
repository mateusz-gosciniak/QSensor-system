#include "kamera_loader.h"

kamera_loader::kamera_loader(
        glm::vec3    pozycja,
        glm::vec3    do_przodu,
        glm::vec3    w_gore,
        glm::float32 roll,
        glm::float32 pitch,
        glm::float32 yaw,
        glm::float32 przyblizenie,
        glm::float32 czulosc
        ) : _pozycja(pozycja),
            _do_przodu(do_przodu),
            _w_gore(w_gore),
            _roll(roll),
            _pitch(pitch),
            _yaw(yaw),
            _przyblizenie(przyblizenie),
            _czulosc(czulosc)
    {
    this->aktualizacja_parametrow();
}

glm::mat4 kamera_loader::macierz_lookAt(){
    return glm::lookAt(this->_pozycja, this->_celownik, this->_w_gore);
}

void kamera_loader::przemiesc(STEROWANIE argument){
    switch (argument){
        case KAMERA_PRZOD: { _pozycja += _do_przodu; }break;
        case KAMERA_TYL:   { _pozycja -= _do_przodu; }break;
        case KAMERA_GORA:  { _pozycja += _w_gore;    }break;
        case KAMERA_DOL:   { _pozycja -= _w_gore;    }break;
        case KAMERA_PRAWO: { _pozycja += _w_prawo;   }break;
        case KAMERA_LEWO:  { _pozycja -= _w_prawo;   }break;

        case KAMERA_ROLL_MINUS:  { _roll--;  }break;
        case KAMERA_ROLL_PLUS:   { _roll++;  }break;
        case KAMERA_PITCH_MINUS: { _pitch--; }break;
        case KAMERA_PITCH_PLUS:  { _pitch++; }break;
        case KAMERA_YAW_MINUS:   { _yaw--;   }break;
        case KAMERA_YAW_PLUS:    { _yaw++;   }break;

        default: {} break;
    }
    this->aktualizacja_parametrow();
}

void kamera_loader::aktualizacja_parametrow(){
    glm::mat4 macierz_rotacji = glm::yawPitchRoll(glm::radians(_yaw),glm::radians(_pitch),glm::radians(_roll));
    _do_przodu = _czulosc * glm::normalize(glm::vec3(macierz_rotacji * glm::vec4(0,0,1,0)));
    _w_gore    = _czulosc * glm::normalize(glm::vec3(macierz_rotacji * glm::vec4(0,1,0,0)));
    _w_prawo   = _czulosc * glm::normalize(glm::cross(_do_przodu, _w_gore));
    _celownik  = _pozycja + _do_przodu;
}
