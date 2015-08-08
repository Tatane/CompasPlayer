#ifndef SON_H
#define SON_H

//#include <SFML/Audio.hpp>

static const int FILERELATIVEPATH_MAXLENGTH = 512;

class Son
{
    int volume;
    //int indexSoundBuffer;
    //sf::Sound *sound;
    char fileRelativePath[FILERELATIVEPATH_MAXLENGTH];

public:
    Son();

    int getVolume() const;
    void setVolume(int value);
    //sf::Sound *getSound() const;
    //void setSound(sf::Sound *value);
    //int getIndexSoundBuffer() const;
    //void setIndexSoundBuffer(int value);
    const char * getFileRelativePath() const;
    void setFileRelativePath(const char * filePath);

};

#endif // SON_H
