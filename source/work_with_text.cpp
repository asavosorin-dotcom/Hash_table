#include "../headers/work_with_text.h"
#include <cctype>

Buffer CreateBuffer(const char* filename) {
    
    // Buffer* point_struct = (Buffer* ) calloc(1, sizeof(Buffer));
    Buffer point_struct = {0};
    // assert(struct_buf);

    FILE* file = fopen(filename, "r");

    assert(file);

    size_t numOfElem = SizeOfFile(filename) / sizeof(char);
    char* buffer = (char* ) calloc(numOfElem + 2, sizeof(char));
    size_t numOfElemNew = fread(buffer + 1, sizeof(char), numOfElem + 1, file);

    // point_struct->buff = buffer;
    // point_struct->buff_size = numOfElemNew;

    point_struct.buff = buffer;
    point_struct.buff_size = numOfElemNew;

    fclose(file);

    return point_struct;
}

BufferBin CreateBufferBinary(const char* filename) {
    
    // Buffer* point_struct = (Buffer* ) calloc(1, sizeof(Buffer));
    BufferBin point_struct = {0};
    // assert(struct_buf);

    FILE* file = fopen(filename, "rb");

    assert(file);

    size_t numOfElem = SizeOfFile(filename) / sizeof(int);
    int*   buffer    = (int* ) calloc(numOfElem + 1, sizeof(int));

    fread(buffer, sizeof(int), numOfElem + 1, file);

    // point_struct->buff = buffer;
    // point_struct->buff_size = numOfElemNew;

    point_struct.buff = buffer;
    point_struct.buff_size = numOfElem;  

    fclose(file);

    return point_struct;
}

size_t SizeOfFile(const char* filename) {
    
    assert(filename);

    struct stat my_stat = {};
    int description = open(filename,  O_RDONLY);
    
    assert(description != -1);

    fstat(description, &my_stat);

    // printf("Size = %ld\n", my_stat.st_size);

    return (size_t) my_stat.st_size;
}

size_t CountStr(const char* buffer) {
    
    size_t count = 0;
    
    while (*buffer != '\0') {
        
        if (*buffer == '\n') {
            count++;
            buffer++;

            while (*buffer == '\n') {
                buffer++;
            }
        } else {
            buffer++;
        }
           
    }

    // printf("Count = %d\n\n", count + 1);

    return ++count;
}

void OutPutBuf(char* buffer, FILE* fileout, size_t numOfElemNew) {
    for (size_t i = 0; i < numOfElemNew; i++) 
        fputc(buffer[i]? buffer[i] : '\n', fileout);

}

size_t Maxlen(char* buffer) {
    
    int maxlen = 0;
    int count = 0;

    while (*buffer != '\0') {
        if (*buffer == '\n') {
            
            if (count > maxlen)
                maxlen = count;

            count = 0;
        }

        buffer++;
        count++;
    }

    printf("MaxLen = %d\n", maxlen);

    return (size_t) maxlen;
}

String_t* CreateArrPoint(char* buffer) {
    assert(buffer);
    char* buffer_start = buffer;

    // PRINT_DEBUG(BOLD_BLUE, "buffer[0] = %c\n", buffer[0])a
    size_t count_words = CountWords(buffer);
    String_t* arr_pointer = (String_t* ) calloc(count_words, sizeof(String_t));
    char* str_char = buffer;

    while (!isspace(*str_char)) str_char++;

    int i = 0;

    for (; *str_char != '\0'; i++)
    {
        *str_char = '\0';
        
        (arr_pointer + i) -> str = buffer;
        (arr_pointer + i) -> str_end = str_char - 1;
        
        str_char += 1;
       
        str_char = skip_space(str_char);

        buffer = str_char;
        while (!isspace(*str_char) && (*str_char != '\0')) str_char++;
    }
    
//    arr_pointer[i].str = buffer;
//    arr_pointer[i].str_end = str_char - 1;
    buffer = buffer_start;
    return arr_pointer;
}

char* skip_space(char* buffer)
{
    while (isspace(*buffer)) {
            buffer++;
        }

    return buffer;
}

char* skip_space_end(char* buffer_left, char* buffer_right)
{
    while (isspace(*buffer_right)) {
            buffer_right--;
        }

    buffer_right[1] = '\0';
    return buffer_left;
}

size_t CountWords(const char* buffer)
{
    size_t count_word = 0;
   //printf("buffer in start:%s\n", buffer);

    while (*buffer != '\0')
    {
        while (!isspace(*buffer) && (*buffer != '\0')) buffer++;
        count_word++;
        while (isspace(*buffer)) buffer++;

//        printf("%lu %s\n", count_word, buffer);
    }
    
//    printf("count_word in the end = %lu", count_word);
    return count_word;
}

void MakeCleanText(const char* filename)
{
    FILE* clean_txt_file = fopen("clean_txt.txt", "a");

    Buffer buffer = CreateBuffer(filename);
    char* elem = buffer.buff;
    char* buffer_print = ++elem;

    while (*elem != '\0')
    {
        while (!isalnum(*elem) && !isspace(*elem)) elem++;
        //fprintf(clean_txt_file, "%c", *elem);
        buffer_print = elem;

        while ((isalnum(*elem) || isspace(*elem)) && (*elem != '\0')) elem++; 
        if (*elem == '\0')
        {
            fprintf(clean_txt_file, "%s", buffer_print);
            break;
        }

        *elem = '\0';
        fprintf(clean_txt_file, "%s", buffer_print);
        elem++;
    }
    
    free(buffer.buff);
    fclose(clean_txt_file);
}
