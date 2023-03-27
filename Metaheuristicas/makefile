###############################################################################
#                               Práctica 1                                    #
# Adriano García -Giralda Milena                                                      #
# Metaheurísticas                                                             #
# Grado en Ingeniería Informática                                             #
# E.T.S.I. Informática y de Telecomunicación. Universidad de Granada          #
###############################################################################
SRCDIR = src
OBJDIR = obj
INCDIR = include
BINDIR = bin

# Archivos y flags de compilación
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
INC = -I $(INCDIR)
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 $(INC)

# Nombre del ejecutable
EXECUTABLE = $(BINDIR)/programa_exe

# Reglas
$(EXECUTABLE): $(OBJ)
	g++ $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	g++ $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)
