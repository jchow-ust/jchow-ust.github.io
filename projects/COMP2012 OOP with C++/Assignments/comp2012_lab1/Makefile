
PIZZA = pizza.o dough.o chicken.o cheese.o
PASTA = pasta.o spaghetti.o herb.o chicken.o cheese.o
SOUP = soup.o
#You might want to use the variable $(LUNCHSET) some points later in this lab.
#The variable will take the union of the set PIZZA, PASTA, and SOUP.
LUNCHSET = $(sort $(PIZZA) $(PASTA) $(SOUP))

#@TODO Edit all target (added new stuff here)
all: soup.exe pizza.exe pasta.exe Lunchset.exe

#@TODO Add new targets
# creates an object file (-o) from a source file using every file in $SOUP
soup.exe: $(SOUP) mainSoup.cpp
	g++ -o $@ -std=c++11 $(SOUP) mainSoup.cpp

# creates an object file (-o) from a source file using every file in #PIZZA
pizza.exe: $(PIZZA) mainPizza.cpp
	g++ -o $@ -std=c++11 $(PIZZA) mainPizza.cpp

# newly added, as Task 2
# creates an executable (because -o) that we link from every object file defined in $PASTA as well as mainPasta.cpp
pasta.exe: $(PASTA) mainPasta.cpp
	g++ -o $@ -std=c++11 $(PASTA) mainPasta.cpp
	
# newly added, Task 3
# creates an executable (because -o) that we link from every object file defined in $LUNCHSET as well as mainLunchset.cpp
Lunchset.exe: $(LUNCHSET) mainLunchset.cpp
	g++ -o $@ -std=c++11 $(LUNCHSET) mainLunchset.cpp


# used to generate any_name.o file from its corresponding cpp file
%.o: %.cpp
	g++ -std=c++11 -c $< -o $@ 
	


# deletes all .o and .exe files
clean:
	rm -f *.o *.exe
	
# log:
# cheese, chicken, dough, herb, soup, spaghetti

# pasta depends on spaghetti, herb, chicken, cheese classes so:
# pasta.h should have dependencies for all those .h files

# pizza depends on dough, chicken, cheese classes
# pizza.h should have dependencies for all those .h files