# Projeto RT (Remove to Trash)

É uma alternativa para o rm deo linux que joga os arquivos para a lixeira 

## Índice

- [Sobre](#sobre)
- [Requisitos](#requisitos)
- [Instalação](#instalação)
- [Uso](#uso)
- [Contribuição](#contribuição)
- [Licença](#licença)

## Sobre

O **RT** é um projeto desenvolvido para excluir arquivos por linha de comando para a lixeira ao invés de excluir direto. Ele foi criado com a finalidade de evitar que por descuido a gente acabe excluindo definitivamente um arquivo que não deveria.

## Requisitos

Antes de rodar o projeto, é necessário ter os seguintes softwares instalados:

- **C++**: O código fonte é compilado com `g++`.
- **Make**: Para executar as etapas de compilação e instalação.


## Instalação

### Clonando o Repositório

Primeiro, clone o repositório para o seu ambiente local:

```bash
git clone https://github.com/ItamarGouveia/rt.git
cd rt
```

### Compilando o Projeto

O projeto usa o `Makefile` para compilar e instalar. Para compilar o projeto, execute:

```bash
make
```

Isso irá compilar o código-fonte e gerar o binário `rt`.

### Instalando o Binário

Para instalar o binário no seu sistema, execute o seguinte comando:

```bash
make install DESTDIR=/caminho/do/destino
```

Substitua `/caminho/do/destino` pelo diretório onde você deseja que o binário seja instalado. Por exemplo:

```bash
make install DESTDIR=/home/usuario/projeto/instalacao
```

Isso irá copiar o binário para o diretório correto dentro de `DESTDIR`.

### Limpando os Arquivos de Compilação

Para remover os arquivos de compilação gerados, use:

```bash
make clean
```

Se você deseja fazer uma limpeza completa, incluindo o arquivo tarball, execute:

```bash
make distclean
```

## Uso

Após instalar o binário, você pode executá-lo com o seguinte comando:

```bash
./rt
```

Se você precisar de mais detalhes sobre como usar o projeto, adicione exemplos aqui.

### Exemplo de uso

1. Execute o comando para compilar e rodar:
   ```bash
   ./rt
   ```

2. [Descrição do que acontece quando o programa é executado].

## Contribuição

Contribuições são bem-vindas! Para contribuir:

1. Faça um fork do projeto.
2. Crie uma branch (`git checkout -b minha-feature`).
3. Faça suas mudanças.
4. Envie suas alterações com um pull request.

Por favor, veja o arquivo [CONTRIBUTING.md](CONTRIBUTING.md) para mais detalhes sobre o processo de contribuição.

## Licença

Este projeto está licenciado sob a [MIT License](LICENSE).

---

### Dicas de Personalização:

- **Sobre o Projeto**: Substitua a descrição genérica do projeto por algo específico, explicando o que ele faz, o que o torna interessante e como ele pode ser útil.
- **Requisitos**: Se o projeto requer outras ferramentas ou bibliotecas, adicione essas informações.
- **Instalação**: Caso o processo de instalação precise de configurações específicas ou ferramentas adicionais, inclua detalhes sobre isso.
- **Uso**: Se o projeto tiver opções de configuração, parâmetros de linha de comando, ou exemplos de entrada e saída, adicione-os na seção de uso.
- **Contribuição**: Caso você tenha um processo específico para contribuições ou queira guiar as pessoas a seguir boas práticas de codificação, adicione essas informações.

Esse formato de `README.md` ajuda qualquer pessoa que veja o seu repositório a entender rapidamente como usar, instalar e contribuir com o projeto.
