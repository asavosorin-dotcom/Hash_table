#include "../headers/main.h" 
extern FILE* file_htm;

int main()
{
    HashTable_t table1 = {};
    HashTableCtor(&table1, HASH_TABLE_SIZE); 


    Buffer buffer = CreateBuffer("uniqe_clean_text.txt");
    String_t* arrate_words = CreateArrPoint(buffer.buff + 1);
    char* word = arrate_words[0].str;

    for (int i = 0; word != NULL; i++)
    {
        //printf("%d\n", counter++);
        HashTableAppendElem(&table1, word, HASH_FUNC);
        word = arrate_words[i].str;
    }

//    ListDump(&table1.arrate_list[1], "debug");
    HashTablePrint(&table1); 

    int counter = 1000;

    while (counter--)
    {
        for (int i = 0; i < 35000; i++)
        {
            char* elem = HashTableSearchElem(&table1, arrate_words[i].str, HASH_FUNC);
        }
    }

    free(arrate_words);
    free(buffer.buff);
    fclose(file_htm);
    HashTableDtor(&table1);

    return 0;
}
