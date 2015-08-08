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
    bool mIsPlaying; // True lorsque le pattern est en cours de lecture.
    char samplesDirectory[512]; // le dossier où sont stockés tous les samples utilisés par l'application.

    // Map qui stocke les sf::SoundBuffer nécessaires au pattern chargé. La key est le chemin relatif (string) du fichier sample utilisé.
    // On veut que chaque fihier ne soit chargé qu'une seule fois dans cette map.
    typedef std::map<const char *, sf::SoundBuffer*> MapFileSoundBuffer;
    MapFileSoundBuffer mapFileSoundBuffer;

    // Map qui stocke tous les sf::Sound utilisés par le pattern chargé.
    // Il y a un sf::Sound pour chaque Son du pattern.
    // La key de la map est le Son. La valeur est le sf::Sound.
    typedef std::map<Son*, sf::Sound*>  MapSonSound;
    MapSonSound mapSonSound;

    void lireTemps(Temps* temps);
    void lireSubTemps(SubTemps* subTemps);
    void lireSon(Son* son);

    void chargerSoundBuffersDuPattern(); // Alloue et charge les sf::SoundBuffer et les sf::Sound necessaires pour jouer le pattern.

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
