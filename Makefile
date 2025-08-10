############
# Makefile corrigido
# Prof. João Paulo A. Almeida
# Programação OO
############

# nome do compilador
CPP = g++
# opções de compilação
CFLAGS = -Wall -g
CPPFLAGS = -std=c++17

# lista de arquivos-fonte
FONTES = $(wildcard *.cpp)
# lista de arquivos-objeto
OBJETOS = $(FONTES:.cpp=.o)
# nome do executável
EXECUTAVEL = deputados

############ Alvos ############

# alvo principal
all: $(EXECUTAVEL)

# linkagem do executável
$(EXECUTAVEL): $(OBJETOS)
	@$(CPP) -o $@ $^

# compilação de cada .cpp para .o
%.o: %.cpp
	@$(CPP) $(CPPFLAGS) $(CFLAGS) -c $<

# executar o programa
run: $(EXECUTAVEL)
	@./$(EXECUTAVEL) $(CDMUN) candidatos.csv votacao.csv 06/10/2024

# limpeza de arquivos
clean:
	@rm -f *.o $(EXECUTAVEL)
