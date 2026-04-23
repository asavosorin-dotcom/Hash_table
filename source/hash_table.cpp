#include "../headers/hash_table.h"
#include <smmintrin.h>

uint32_t (*hash_func_array[HASH_FUNC_CAPASITY]) (HashTable_t* , const char*) = {
    hash_func_0, 
    hash_func_sum, 
    hash_func_first_letter, 
    hash_func_strlen, 
    hash_func_roll, 
    hash_func_crc32, 
    hash_func_adler32,    
    hash_func_sum_differ,
    hash_func_last_letter,
    hash_func_mul
    };

void HashTableCtor(HashTable_t* table, int capacity)
{
    table->array_list = (List_t* ) calloc(capacity, sizeof(List_t));

    for (int i = 0; i < capacity; i++)
    {
        LISTCTOR(table->array_list[i], SIZE_LIST);
    }

    table->capacity = capacity;
}

void HashTableDtor(HashTable_t* table)
{
    for (int i = 0; i < table->capacity; i++)
        ListDtor(&table->array_list[i]);

    free(table->array_list);    
}

void HashTableAppendElem(HashTable_t* table, char* elem, uint32_t hash_func(HashTable_t*, const char*))
{
    uint32_t index = hash_func(table, elem);
    //printf("index = %d\n", index);
    List_t list = table->array_list[index];
    char* list_elem = list.data[1];

    for (int index_elem = 1; list_elem != NULL; index_elem++)
    {
        if (strcmp(list_elem, elem) == 0) return ;
        list_elem = list.data[index_elem];
    }

    LISTAppendAfter(table->array_list[index], 0, elem);
}

uint32_t hash_func_0 (HashTable_t* table, const char* elem)
{
    return 0;
}

uint32_t hash_func_sum (HashTable_t* table, const char* elem)
{
    uint32_t hash = 0;
//    FILE* log = fopen("log.txt", "w");
//    printf("[%s] \"\n", elem);
    while(*elem != '\0')
    {
//        fprintf(log, "%d [%c] %d\n", hash, *elem, *elem);
        hash += *elem;
        elem++;
    }
   
    // printf("hash0 = %d\n", hash);
    hash = hash % table->capacity; 
    // printf("hash = %d\n", hash);

//    fclose(log);
    return hash;
}

uint32_t hash_func_first_letter(HashTable_t* table, const char* elem)
{
    uint32_t hash = *elem %  table->capacity;
    return hash;
}

uint32_t hash_func_strlen(HashTable_t* table, const char* elem)
{
    uint32_t hash = strlen(elem) % table->capacity;
    return hash;
}

uint32_t hash_func_roll(HashTable_t* table, const char* elem)
{
    uint32_t hash = 0;
    uint32_t mask = 0;

    while (*elem != '\0')
    {
        mask = hash & (1 << 31);
        hash = (hash << 1) + mask;
        hash ^= *elem++;
    }

    hash = hash % table->capacity;
    return hash;
}

uint32_t hash_func_crc32(HashTable_t* table, const char* elem)
{
    #include "../headers/crc_table.h"
    uint32_t hash = 0;

//    for (int i = 0; i < 256; i++)
//    {
//        hash = i;
//        for (int j = 0; j < 8; j++)
//            hash = hash & 1 ? (hash >> 1) ^ 0xEDB88320UL : hash >> 1;
//
//        hash_table[i] = hash;
//    };

    hash = 0xFFFFFFFFUL;

    while (*elem != '\0')
        hash = hash_table[(hash ^ *elem++) & 0xFF] ^ (hash >> 8);
    
    hash ^= 0xFFFFFFFFUL;
    return hash % table->capacity;
}

uint32_t hash_func_adler32(HashTable_t* table, const char* elem)
{
    uint32_t hash = 0;

    uint16_t sum_a = 1;
    uint16_t sum_b = 0;

    int len = strlen(elem);

    while (*elem != '\0')
    {
        sum_a += *elem;
        sum_b += len * *elem;
        len--;
        elem++;
    }

    hash = sum_a * (2 << 15) + sum_b;

    return hash % table->capacity;
}

uint32_t hash_func_sum_differ(HashTable_t* table, const char* elem)
{
    uint32_t hash = 0;
    char flag = 1; 

    while (*elem != '\0')
    {
        hash += *elem++ * flag;
        flag *= -1;
    }

    return hash % table->capacity;
}

uint32_t hash_func_last_letter(HashTable_t* table, const char* elem)
{
    uint32_t hash = 0;
    while (*elem != '\0') elem++;

    elem--;
    hash = *elem % table->capacity;

    return hash;
}

uint32_t hash_func_mul(HashTable_t* table, const char* elem)
{
    uint32_t hash = 1;
    while (*elem != '\0') hash *= *elem; 

    return hash % table->capacity;
}

char* HashTableSearchElem(HashTable_t* table, const char* elem, uint32_t hash_func(HashTable_t*, const char*))
{
    int index = hash_func(table, elem);
    
    List_t* list = &table->array_list[index];
    int index_in_list = list->next[0];
    char* data_elem = list->data[index_in_list];

    while (data_elem != NULL)
    {
        __m128i elem_vec = _mm_loadu_si128((__m128i*) elem);
        __m128i data_elem_vec = _mm_loadu_si128((__m128i*) elem);

        if (_mm_cmpistrz(elem_vec, data_elem_vec, _SIDD_UBYTE_OPS) == 0)
        //if (strcmp(elem, data_elem) == 0)
        {
            return data_elem;
        }
        
        __asm__ (".intel_syntax noprefix;"
                "mov rdi, [rdi + 8];"
                "mov rax, [rdi + rsi * 4];"
                 ".att_syntax prefix;"
                : "=a" (index_in_list)
                : "D" (list), "S" (index_in_list)
                );

        __asm__  (".intel_syntax noprefix;"
                "mov rdi, [rdi];"
                "mov rax, [rdi + rsi * 4];"
                 ".att_syntax prefix;"
                : "=a" (data_elem)
                : "D" (list), "S" (index_in_list)
                );
//        index_in_list = list->next[index_in_list];
        // data_elem = list->data[index_in_list];
    }

    return NULL;
}

void HashTablePrint(HashTable_t* table)
{
    FILE* exel_table = fopen("./debug/table.csv", "w");
    List_t* list = &table->array_list[0];
    char* elem = list->data[1];

    for (int i = 0; i < table->capacity; i++)
    {
        list = &table->array_list[i];
        elem = list->data[1];

        int index_in_list = list->next[0];

        fprintf(exel_table, "%d\t", index_in_list );
    }

    fclose(exel_table);
}
