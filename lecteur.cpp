#include "lecteur.h"
#include "pattern.h"
#include "temps.h"

#include <iostream>
#include <ctime>
#include <cstring>

// Pour getcwd :
#include <stdio.h>
#include <direct.h>


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
    if (subTemps) {
        std::cout<<'.';

        // Jouer tous les sons de ce SubTemps
        for(int iSon=0; iSon<subTemps->getNbSons(); iSon++) {
            Son * son = subTemps->getSonAt(iSon);
            if (son) {
                lireSon(son);
            }
        }
    }

}

void Lecteur::lireSon(Son *son)
{
    if (son && mapSonSound.count(son)>0){
        sound = mapSonSound.at(son);
        sound->play();
    }
}

void Lecteur::chargerSoundBuffersDuPattern()
{
    if (pattern) {

        // Decharger l'existant :
        MapFileSoundBuffer::const_iterator it;
        for(it = mapFileSoundBuffer.begin(); it != mapFileSoundBuffer.end(); ++it) {
            sf::SoundBuffer * sb = it->second;
            delete sb;
        }
        mapFileSoundBuffer.clear();
        std::cout<<"Map de SoundBuffer videe"<<std::endl;

        MapSonSound::const_iterator it2;
        for(it2 = mapSonSound.begin(); it2 != mapSonSound.end(); ++it2) {
            sf::Sound * s = it2->second;
            delete s;
        }
        mapSonSound.clear();
        std::cout<<"Map de Sound videe"<<std::endl;


        for(int iTemps=0; iTemps<pattern->getNbTemps(); iTemps++) {

            Temps * temps = pattern->getTemps(iTemps);

            for(int iSubTemps=0; iSubTemps<temps->getNbSubTemps(); iSubTemps++){

                SubTemps* subTemps = temps->getSubTempsAt(iSubTemps);

                for(int iSon=0; iSon<subTemps->getNbSons(); iSon++) {

                    Son * son = subTemps->getSonAt(iSon);
                    if (son) {
                        const char * file = son->getFileRelativePath();
                        sf::SoundBuffer * sb = 0;
                        // Regarder si ce chemin file est deja present dans la map
                        // MAis ATTENTION il ne faut pas comparer les char*,
                        // il faut comparer la valeur des chaines.
                        MapFileSoundBuffer::const_iterator it;
                        bool dejaDansMap = false;
                        for(it = mapFileSoundBuffer.begin(); it != mapFileSoundBuffer.end(); ++it) {
                            const char * valeur = it->first;
                            if (std::strcmp(valeur, file) == 0) {
                                sb = it->second;
                                dejaDansMap = true;
                                break;
                            }
                        }

                        if ( ! dejaDansMap) {
                            sb = new sf::SoundBuffer;
                            char fullFilePath[1024] = "";
                            std::strcat(fullFilePath, samplesDirectory);
                            std::strcat(fullFilePath, file);
                            bool b = sb->loadFromFile(fullFilePath);
                            if (!b) {
                                std::cout<<"Erreur chargement fichier sample "<<fullFilePath<<std::endl;
                            }
                            else {
                                mapFileSoundBuffer[file] = sb;
                            }
                        }

                        if (sb) {
                            sf::Sound * sound = new sf::Sound(*sb);
                            sound->setVolume(son->getVolume());
                            mapSonSound[son] = sound;
                        }
                    }
                }
            }
        }

    }
}

Lecteur::Lecteur()
    : pattern(0)
    , mIsPlaying(false)
{

    std::strcpy(samplesDirectory, "C:\\Users\\monnom\\Dropbox\\Documents\\Musique\\Samples\\");

    // Afficher le repertoire de travail (TEMPORAIRE) :
    char cwd[512];
    _getcwd(cwd, sizeof(cwd));
    std::cout<<"Current directory = "<<cwd<<std::endl;
    /*
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
    */
}

Lecteur::~Lecteur()
{

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

    chargerSoundBuffersDuPattern();
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
