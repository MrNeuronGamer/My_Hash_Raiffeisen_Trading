#include <functional>
#include <iostream>
#include <string> 

template<class TKey,class TValue>
class HashTable
{

public:


    bool    push(TKey key, TValue value);
    bool    remove(TKey key);
    TValue  search(TKey key) const;
    




private:

    size_t Capacity;
    size_t Stored;
    //size_t supervisor;


    class HObject
    {

    public:

        TKey key;
        TValue value;     
        HObject* Next;

         HObject();
        ~HObject();
        void operator=(const HObject& A);

    };

    bool   push(HObject& A);


    HObject** Table;
    HObject*  AllowedObjects;

    size_t HashFunction(HObject& obj, size_t SizeLimit) const;
    void ReHash();



};



int main()
{



    return 0;
}


template<class TKey, class TValue>
size_t HashTable<TKey, TValue>::HashFunction(HObject& obj, size_t SizeLimit) const
{
    size_t index = 0;


    index = std::hash<TKey>{}(obj.key);

    index = index / SizeLimit;

    return index;
}


template<class TKey, class TValue>
void HashTable<TKey, TValue>::ReHash()
{
    HObject *buffer = new HObject[Stored];
    HObject** grabber = Table;
    HObject*  conductor;
    size_t StoredOLD = Stored;

    for (size_t i = 0; i < Stored; )
    {

        while (grabber[0] == NULL)
            grabber++;

        conductor = grabber[0];
        while (conductor != NULL)
        {
            buffer[i] = *conductor;
            conductor = conductor->Next;
            i++;
        }
        
    }



    delete[] AllowedObjects;
    delete[] Table;


    Capacity = 3 * Capacity;
    Stored = 0;

    Table = new HObject*[Capacity];
    AllowedObjects = new HObject[Capacity - 3];

    for (size_t i = 0; i < StoredOLD; i++)
    {        
        this->push(buffer[i]);
    }







    delete[] buffer;
}









template<class TKey, class TValue>
HashTable<TKey, TValue>::HObject::HObject()
{
   
    Next = NULL;

}

template<class TKey, class TValue>
HashTable<TKey, TValue>::HObject::~HObject()
{
    
}

template<class TKey, class TValue>
void HashTable<TKey, TValue>::HObject::operator=(const HObject & A)
{

    key = A.key;
    value = A.value;
    Next = NULL;
}


