#include "../headers/main.h" 
extern FILE* file_htm;

int main()
{
    HashTable_t table1 = {};
    HashTableCtor(&table1, 10); 

    char* string = strdup("hello!!!\n");

    HashTableAppendElem(&table1, string, hash_func_1);  
    
    for (int i = 0; i < 10; i++)
    {
        ListDumpImage(&table1.arrate_list[i]);
        ListDump(&table1.arrate_list[i], "hello hash!");
    }


    free(string);
    fclose(file_htm);
    HashTableDtor(&table1);

    return 0;
}
