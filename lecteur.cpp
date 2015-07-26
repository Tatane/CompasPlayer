#include "lecteur.h"
#include "pattern.h"
#include "temps.h"

#include <iostream>
#include <ctime>

// Pour getcwd :
#include <stdio.h>
#include <direct.h>

static const char * REPERTOIRE_SONS = "C:\\Users\\monnom\\Dropbox\\Documents\\Musique\\Samples\\";

void Lecteur::lireTemps(Temps *temps)
{
    clock_t tickDebut = clock();

    std::cout<<"|";

    int dureeTempsMs = 60000 / pattern->getTempo(); // en milisecondes, durée entre chaque temps.

    // Diviser le temps en subTemps
    if (temps->getNbSubTemps() > 0) {
        int dureeSubTempsMs = dureeTempsMs / temps->getNbSubTemps();
        for(int iSubTemps=0; iSubTemps<temps->getNbSubTemps(); iSubTemps++){
            clock_t tickDebutTemps = clock();

            SubTemps* subTemps = temps->getSubTempsAt(iSubTemps);

            lireSubTemps(subTemps);


            while (((clock() - tickDebutTemps)*1000 / CLOCKS_PER_SEC)<dureeSubTempsMs);
        }
    }

    while (((clock() - tickDebut)*1000 / CLOCKS_PER_SEC)<dureeTempsMs);
}

void Lecteur::lireSubTemps(SubTemps *subTemps)
{
    std::cout<<'.';

    // Jouer tous les sons de ce SubTemps
    for(int iSon=0; iSon<subTemps->getNbSons(); iSon++) {

        // Si ce Son a encore son sf::Sound vide, alors il faut l'initialier,
        // sinon, on utilise le pointeur deja existant.
        Son * son = subTemps->getSonAt(iSon);
        if (son) {

            lireSon(son);

        }
    }

}

void Lecteur::lireSon(Son *son)
{
    sf::Sound * sound = 0;
    if (mapSonSound.count(son) == 0) {

        //if (son->getSound() == 0) {
        int indexSoundBuffer = son->getIndexSoundBuffer();
        if (indexSoundBuffer < vecSoundBuffers.size()) {
            sf::SoundBuffer * soundBuffer = vecSoundBuffers.at(indexSoundBuffer);
            sound = new sf::Sound(*soundBuffer);
            sound->setVolume(son->getVolume());
            //son->setSound(sound);
            mapSonSound[son] = sound;
        }
    }
    else {
        sound = mapSonSound.at(son);
    }

    // Jouer le son :
    sound->play();
}

Lecteur::Lecteur()
    : pattern(0)
    , mIsPlaying(false)
{

    // Afficher le repertoire de travail (TEMPORAIRE) :
    char cwd[512];
    _getcwd(cwd, sizeof(cwd));
    std::cout<<"Current directory = "<<cwd<<std::endl;

    // Charger les sons dans les buffers :
    sf::SoundBuffer * buffer = new sf::SoundBuffer;
    char cheminFichier[512];

    sprintf(cheminFichier, "%s%s", REPERTOIRE_SONS, "Dry-Kick.wav");
    if ( ! buffer->loadFromFile(cheminFichier)) {
        std::cout<<"Erreur loadFromFile"<<std::endl;
    } else {
        vecSoundBuffers.push_back(buffer);
    }

    buffer = new sf::SoundBuffer;
    sprintf(cheminFichier, "%s%s", REPERTOIRE_SONS, "Clap-3.wav");
    if ( ! buffer->loadFromFile(cheminFichier)) {
        std::cout<<"Erreur loadFromFile"<<std::endl;
    } else {
        vecSoundBuffers.push_back(buffer);
    }
}

Lecteur::~Lecteur()
{
    std::vector<sf::SoundBuffer*>::const_iterator it;
    for(it = vecSoundBuffers.begin(); it != vecSoundBuffers.end(); it++){
        sf::SoundBuffer* buffer = *it;
        delete buffer;
        buffer = 0;
    }
}

void Lecteur::lire()
{
    std::cout<<"lire"<<std::endl;

    if ( ! isPlaying() ) {
        start();
    }
    else {
        std::cout<<"Deja en cours de lecture"<<std::endl;
    }
}

void Lecteur::arreter()
{
    std::cout<<"arreter"<<std::endl;
    isPlaying(false);
}

Pattern *Lecteur::getPattern() const
{
    return pattern;
}

void Lecteur::setPattern(Pattern * p)
{
    pattern = p;
}

bool Lecteur::isPlaying() const
{
    return mIsPlaying;
}

void Lecteur::isPlaying(bool value)
{
    mIsPlaying = value;
}

void Lecteur::run()
{
    isPlaying(true);

    while ( isPlaying() ) {
        for(int iTemps=0; iTemps<pattern->getNbTemps() && isPlaying(); iTemps++) {

            currentTempsChanged(iTemps);

            Temps * temps = pattern->getTemps(iTemps);

            lireTemps(temps);
        }
    }

    std::cout<<"Thread terminé"<<std::endl;
}
