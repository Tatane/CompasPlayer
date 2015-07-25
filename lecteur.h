#ifndef LECTEUR_H
#define LECTEUR_H

#include "SFML/Audio.hpp"

#include <vector>
#include <map>

#include <QThread>

class Temps;
class SubTemps;
class Son;

class Son;

class Pattern;

class Lecteur : QThread
{
private:
    Pattern * pattern;
    std::vector<sf::SoundBuffer*> vecSoundBuffers;
    std::map<Son*, sf::Sound*> mapSonSound;

    void lireTemps(Temps* temps);
    void lireSubTemps(SubTemps* subTemps);
    void lireSon(Son* son);

public:
    Lecteur();
    virtual ~Lecteur();
    void lirePattern();
    void arreter();
    void setPattern(Pattern *);

    // QThread interface
protected:
    void run();
};

#endif // LECTEUR_H
