#include "son.h"
#include <cstring>
#include <iostream>
#include <exception>

int Son::getVolume() const
{
    return volume;
}

void Son::setVolume(int value)
{
    volume = value;
}

const char *Son::getFileRelativePath() const
{
    return fileRelativePath;
}

void Son::setFileRelativePath(const char *filePath)
{
    if (std::strlen(filePath) >  FILERELATIVEPATH_MAXLENGTH) {
        std::cout<<"Le chemin du fchier est trop long"<<std::endl;
        // TODO : gerer le schemisn trop longs
    }
    std::strcpy(fileRelativePath, filePath);
}
/*
sf::Sound *Son::getSound() const
{
    return sound;
}

void Son::setSound(sf::Sound *value)
{
    sound = value;
}
*/
/*
int Son::getIndexSoundBuffer() const
{
    return indexSoundBuffer;
}

void Son::setIndexSoundBuffer(int value)
{
    indexSoundBuffer = value;
}
*/
Son::Son()
    : volume(100) // 0 to 100. 100 is maximum.
    //, indexSoundBuffer(-1)
    //, sound(0)
{
}
