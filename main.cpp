////////////////////////////////////////////
//// Autor:     Khoroshilov Dmitrii     ////
//// Name:      Raiffeisen Assignment   ////
//// Version:   1.0.3                   ////
////////////////////////////////////////////


#include <functional>
#include <iostream>
#include <string> 

template<class TKey,class TValue>
class HashTable
{

public:


    bool    push(TKey key, TValue value);       // Hashes new key and value , returns true if success, false otherwise
    bool    remove(TKey key);                   // Deletes a node with key = key , returns true if success, false otherwise
    bool    search(TKey key) const;             // Looks for object with key = key, returns true if success, false otherwise
    
    HashTable(size_t Limits);                   // Creates new Hash Table with initial capacity size = Limits.
    ~HashTable();


private:

    size_t Capacity;                             // Maximum Capacity for Hash Table
    size_t Stored;                               // Current number of Stored objects
    //size_t supervisor;


    class HObject                                //  Class for Hash Tables nodes
    {

    public:

        TKey key;                                // Objects key
        TValue value;                            // Associated value
        HObject* Next;                           // Next node pointer

         HObject();
        ~HObject();
        void operator=(const HObject& A);

    };

    bool   push(HObject& A);                      


    HObject** Table;                            // Table itself
    HObject*  AllowedObjects;                   // Special Objects' range for usage

    size_t HashFunction(TKey obj, size_t SizeLimit) const;      // Hash Function to be used for hashing, takes a key, Capacity limits and returns hash
    void ReHash();                                              // Function for rehashing, gets used whenever extending of capacity is required. Sets new capacity equal to 3 times former capacity

    

    


};



int main()
{
    // just excample of usage

    
    HashTable<std::string, int> table(11);  

    table.push("RaiffeisenNumberOne", 101);
    int a; 

    std::cout << table.search("RaiffeisenNumberOne");
    std::cin >> a;


    std::cout << table.remove("RaiffeisenNumberOne");
    std::cin >> a;

    std::cout << table.search("RaiffeisenNumberOne");
    std::cin >> a;

    return 0;
}


template<class TKey, class TValue>
HashTable<TKey, TValue>::HashTable(size_t Limits)
{
    Capacity = Limits;
    Stored = 0;
    Table = new HObject*[Capacity];
    AllowedObjects = new HObject[Capacity - 3];
    for (size_t i = 0; i < Capacity; i++)
        Table[i] = NULL;

}


template<class TKey, class TValue>
HashTable<TKey, TValue>::~HashTable()
{

    delete[] AllowedObjects;
    delete[] Table;
    

}


template<class TKey, class TValue>
bool HashTable<TKey, TValue>::push(TKey key, TValue value)
{
    
    if (Stored + 4 >= Capacity)
        ReHash();


    AllowedObjects[Stored].key = key;
    AllowedObjects[Stored].value = value;
    AllowedObjects[Stored].Next = NULL;

    size_t expected_pos = HashFunction(key,Capacity);

    if (Table[expected_pos] != NULL)
    {
        AllowedObjects[Stored].Next = Table[expected_pos]->Next;
        Table[expected_pos] = (AllowedObjects + Stored);


    }

    else
    {
        Table[expected_pos] = (AllowedObjects + Stored);
    }

    Stored++;



    return true;
}


template<class TKey, class TValue>
bool HashTable<TKey, TValue>::push(HObject & A)
{

    push(A.key, A.value);

    return true;
}

template<class TKey, class TValue>
size_t HashTable<TKey, TValue>::HashFunction(TKey key, size_t SizeLimit) const
{
    size_t index = 0;


    index = std::hash<TKey>{}(key);

    index = index % SizeLimit;

    return index;
}

template<class TKey, class TValue>
bool HashTable<TKey, TValue>::remove(TKey key)
{

    size_t searching_pos = HashFunction(key, Capacity);
    HObject* conductor = NULL;


    if (Table[searching_pos] == NULL) return false;
    else
    {
        conductor = Table[searching_pos];

        if (conductor->key == key)
        {
            Table[searching_pos] = conductor->Next;
            return true;
        }

        while ((conductor->Next)->key != key)
        {
            conductor = conductor->Next;
        }

        conductor->Next = (conductor->Next)->Next;
        

    }


    return true;
}

template<class TKey, class TValue>
bool HashTable<TKey, TValue>::search(TKey key) const
{
    
    size_t searching_pos = HashFunction(key, Capacity);
    HObject* conductor = NULL;


    if (Table[searching_pos] == NULL) return false;
    else
    {
        conductor = Table[searching_pos];

        if (conductor->key == key)
        {
            
            return true;
        }

        while (((conductor->Next)->key != key )|| (conductor->Next != NULL))
        {
            conductor = conductor->Next;
        }

        if (conductor->key == key) return true;
    }


    

    return false;
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
    for (size_t i = 0; i < Capacity; i++)
        Table[i] = NULL;

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


