/*
 * Interface for AVLTree and HashTable
 *
 *
 *
 *
*/


#ifndef INDEXERFACE_H
#define INDEXERFACE_H

template <typename fontenot>
class IndexerFace {
private:

public:
    virtual void insert(fontenot val) = 0;
    virtual fontenot remove() = 0;
    virtual bool search() = 0;
};

#endif // INDEXERFACE_H
