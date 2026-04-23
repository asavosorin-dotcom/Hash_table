#include "../headers/main.h" 

int main()
{
    HashTable_t table1 = {};
    HashTableCtor(&table1, 4001);
    hash_func_crc32(&table1, "aaa");
    return 0;
}
