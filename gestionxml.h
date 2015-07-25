#ifndef GESTIONXML_H
#define GESTIONXML_H

class Pattern;

class GestionXML
{
public:
    GestionXML();
    bool loadFileIntoPattern(const char * file, Pattern * pattern);
};

#endif // GESTIONXML_H
