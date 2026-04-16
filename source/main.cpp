#include "../headers/main.h" 
extern FILE* file_htm;
// подключить онегига для чтения слов из файла сделать там функцию для разделения по словам, а не по строкам 
// дописать все хеш-функции
// написать функцию для подсчета количества слов в строке
int main()
{
    HashTable_t table1 = {};
    HashTableCtor(&table1, 10); 

    int counter = 0;

    Buffer buffer = CreateBuffer("clean_txt.txt");
    size_t count_words = CountWords(buffer.buff + 1);
    printf("%lu\n", count_words);
    String_t* arrate_words = CreateArrPoint(buffer.buff + 1);
    char* string = strdup("hello!!!\n");

    for (int i = 0; i < count_words - 1;i++)
    {
        printf("%d\n", counter++);
        HashTableAppendElem(&table1, arrate_words[i].str, hash_func_1);
    }
    printf("\n after append\n\n");
//    HashTableAppendElem(&table1, string, hash_func_1);  
    counter = 0;
    //for (int i = 0; i < 10; i++)
    //{
      //  printf("\n in dump [%d]\n\n", counter);

        //ListDumpImage(&table1.arrate_list[i]);
        //ListDump(&table1.arrate_list[i], "hello hash!"); 
    //}

    free(string);
    fclose(file_htm);
    HashTableDtor(&table1);

    return 0;
}
