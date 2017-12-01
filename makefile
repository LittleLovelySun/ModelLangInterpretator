#[название выходного файла - программы]  
NAME=ModelLang
#[название комилятора]
COMPILER=clang++
#[файлы для компиляции]
FILES=*.cpp analyzers/*.cpp entities/*.cpp
#[используемый стандарт языка]
STD=c++14
#OPTIMIZE_LEVEL=[уровень оптимизации, 0 - не оптимизировать]
#[флаги компиляции]
FLAGS=-Wall

all:
	$(COMPILER) $(FLAGS) -std=$(STD) $(FILES) -o $(NAME)
  
clean:
	rm -rf $(NAME)
