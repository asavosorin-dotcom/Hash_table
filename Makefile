FLAGS =  -I./headers -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

OBJECTS_LIST = main.o list.o hash_table.o work_with_text.o
OBJECTS_DIR  = objects/
SOURCE_DIR   = source/
OBJECTS_LIST_CLEAN = make_clean_text.o work_with_text.o
BJECTS_LIST_TEST = test.o list.o hash_table.o work_with_text.o

hash_table: $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST))
	@echo ----------------------------------------------------
	g++ $(FLAGS) $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST)) -g -o hash_table
	@echo ----------------------------------------------------

$(OBJECTS_DIR)%.o: $(SOURCE_DIR)%.cpp
	g++ -c $< -o $@

clean_text: $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST_CLEAN))
	@echo ----------------------------------------------------
	g++ $(FLAGS) $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST_CLEAN)) -g -o clean_text 
	@echo ----------------------------------------------------

test: $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST_TEST))
	@echo ----------------------------------------------------
	g++ $(FLAGS) $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST_TEST)) -g -o test 
	@echo ----------------------------------------------------

hash_table_hist: $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST))
	@echo ----------------------------------------------------
	g++ $(FLAGS) $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST)) -g -o hash_table
	./hash_table
	python3 ./scripts/hist.py
	@echo ----------------------------------------------------

hash_table_perf: $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST))
	@echo ----------------------------------------------------
	nasm -f elf64 source/crc32.s -o $(addprefix $(OBJECTS_DIR), crc32.o)
	g++ $(addprefix $(OBJECTS_DIR), crc32.o) $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST)) -g -o hash_table
	@echo ----------------------------------------------------

clean:
	rm -f $(addprefix $(OBJECTS_DIR), *.o)
