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

class Lecteur : public QThread
{
    Q_OBJECT

private:
    Pattern * pattern;
    std::vector<sf::SoundBuffer*> vecSoundBuffers;
    std::map<Son*, sf::Sound*> mapSonSound;
    bool mIsPlaying;

    void lireTemps(Temps* temps);
    void lireSubTemps(SubTemps* subTemps);
    void lireSon(Son* son);

public:
    Lecteur();
    virtual ~Lecteur();
    void lire();
    void arreter();
    Pattern * getPattern() const;
    void setPattern(Pattern *);

    // QThread interface
    bool isPlaying() const;
    void isPlaying(bool value);

signals:
    void currentTempsChanged(int value);

protected:
    void run();
};

#endif // LECTEUR_H
