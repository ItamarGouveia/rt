# Definir o compilador e as flags
CXX = g++
CXXFLAGS = -Wall -g

# Nome do executável
TARGET = rt

# Arquivos fonte
SRC = ./src/rt.cpp

# Arquivos objeto (gerados a partir dos fontes)
OBJ = $(SRC:.cpp=.o)

# Regra para compilar o programa
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Regra para compilar o arquivo fonte em objeto
$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)

# Regra para instalar o binário
install: $(TARGET)
	# Verificar se DESTDIR está definido, senão usar o valor padrão
	if [ ! -d "$(DESTDIR)/usr/bin" ]; then \
		mkdir -p $(DESTDIR)/usr/bin; \
	fi
	# Instalar o binário no diretório destino
	install -m 755 $(TARGET) $(DESTDIR)/usr/bin/

	# Caso você tenha man page ou outros arquivos a instalar, adicione aqui
	# install -m 644 debian/man/rt.1 $(DESTDIR)/usr/share/man/man1/

# Regra para limpar arquivos temporários
clean:
	rm -f $(OBJ) $(TARGET)

# Regra para limpeza completa (remover o tarball, por exemplo)
distclean: clean
	rm -f $(TARGET).tar.gz
