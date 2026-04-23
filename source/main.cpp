#include "../headers/main.h" 
extern FILE* file_htm;
extern uint32_t (*hash_func_array[HASH_FUNC_SIZE]) (HashTable_t* , const char*); 

int main()
{
    HashTable_t table1 = {};
    HashTableCtor(&table1, HASH_TABLE_SIZE); 
    
    Buffer buffer = CreateBuffer("uniqe_clean_text.txt");
    String_t* array_words = CreateArrPoint(buffer.buff + 1);
    char* word = array_words[0].str;

    for (int i = 0; word != NULL; i++)
    {
        //printf("%d\n", counter++);
        HashTableAppendElem(&table1, word, HASH_FUNC);
        word = array_words[i].str;
    }

    HashTablePrint(&table1); 

    int counter = 1000;

    while (counter--)
    {
        for (int i = 0; i < 35000; i++)
        {
            char* elem = HashTableSearchElem(&table1, array_words[i].str, HASH_FUNC);
        }
    }

    free(array_words);
    free(buffer.buff);
    fclose(file_htm);
    HashTableDtor(&table1);

    return 0;
}
