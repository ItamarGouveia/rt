# RT (Remove to Trash)

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)

Uma alternativa segura ao comando `rm` do Linux: em vez de excluir arquivos permanentemente, o **RT** os move para a lixeira. Criado para prevenir exclusões acidentais via terminal.

## Índice

- [Sobre](#sobre)
- [Requisitos](#requisitos)
- [Instalação](#instalação)
- [Uso](#uso)
- [Contribuição](#contribuição)
- [Licença](#licença)

## Sobre

O **RT (Remove to Trash)** é uma ferramenta de linha de comando desenvolvida em C++ que move arquivos para a lixeira do sistema, funcionando como um substituto mais seguro para o `rm`. Ideal para usuários que utilizam terminal com frequência e querem evitar perdas acidentais de dados.

## Requisitos

- **C++ (g++)**
- **Make**

## Instalação

```bash
git clone https://github.com/ItamarGouveia/rt.git
cd rt
make
```

### Instalar o binário

```bash
make install DESTDIR=/caminho/do/destino
```

Por exemplo:

```bash
make install DESTDIR=/home/usuario/bin
```

### Limpeza

```bash
make clean         # Remove arquivos temporários
make distclean     # Limpa completamente, incluindo tarballs
```

## Uso

```bash
./rt nome_do_arquivo
```

**Exemplo:**
```bash
./rt documento.txt
```

➡️ Isso move `documento.txt` para a lixeira, sem excluir permanentemente o arquivo.

## Contribuição

Contribuições são bem-vindas!

1. Faça um fork do projeto
2. Crie uma branch (`git checkout -b minha-feature`)
3. Faça suas alterações
4. Envie um pull request

Veja o arquivo [CONTRIBUTING.md](CONTRIBUTING.md) para mais detalhes.

## Licença

Distribuído sob a [Licença MIT](LICENSE).
