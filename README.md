## Batocera.PLUS

### O que é o Batocera.PLUS?

O Batocera.PLUS é um sistema operacional minimalista (firmware) que transforma um PC 64 bits  em um console dedicado a retro emulação.

O Batocera.PLUS é uma versão modificada do batocera.linux que adiciona diversos recursos extras ao sistema, bem como correções de erros e personalizações.

O Batocera.PLUS não é uma imagem pronta com jogos, temas e customizações, trata-se de uma imagem limpa com recursos nunca antes vistos em um sistema de retro emulação.

O Batocera.PLUS não é um fork do projeto original e sim de um conjunto de scripts, patch, programas, etc… que adiciona diversas funcionalidades ao sistema original.

### Como compilar

A imagem do Batocera.PLUS é compilada usando a versão anterior do próprio Batocera.PLUS.

As imagens mais recentes do Batocera.PLUS podem ser baixadas diretamente na comunidade do Batocera.PLUS no discord do progeto.

Para compilar a imagem é necessário ter pelo menos 30GB de espaço livre em disco, este espaço será usado apenas durante o processo de compilação.
A partição precisa ter sido formatada em algum tipo de sistema de arquivos Linux (ext4, btrfs, etc), não são suportadas partições do tipo Windows (fat, ntfs, extat)

Recomenda-se que o computador tenha 6GB ou mais de memória Ram.

Durante a compilação serão baixados diversos arquivos da internet. Estima-se que serão baixados cerca de 5GB a 8GB de arquivos. Ao final da compilação os arquivos baixados não serão removido, portanto quando uma nova compilação for necessária somente os arquivos que foram atualizados serão baixados dinuindo o tempo de download.

Levando em consideração que todos os arquivos já foram baixados o processo de compilação propriamente dito leva em torno de 10 a 60 minutos a depender do processador usado e principalmente da velocidade de leitura/gravação do HD/SSD/NVME.

<b>Compilação modo fácil</b>

O Batocera.PLUS possui um simples script que automatiza todo o processo de compilação gerando a imagem com as últimas atualizações disponíveis. O script se encarrega de baixar todos os arquivos e gerar a imagem pronta para uso, sendo indicado para quem deseja apenas ter uma imagem atualizada.

Para compilar apenas crie uma pasta com qualquer nome e acesse a pasta, em seguida abra um terminal pressionando a tecla F4 e no terminal execute este comando.

    batocera-build

<b>Compilação modo difícil</b>

O Batocera.PLUS já vem com o git instalado, então clone o repositório.

    git clone https://github.com/AlexxandreFS/Batocera.PLUS.git

Para atualizar um repositório anteriormente clonado, acesse o repositório local.

    cd Batocera.PLUS

Atualize o repositório.

    git reset --hard
    git clean -f
    git pull https://github.com/AlexxandreFS/Batocera.PLUS.git

Acesse a pasta onde estão os arquivos pelo terminal (win + f4) ou (f1 e depois f4) e execute o script de criação da imagem.

    ./build-batocera.plus

### Compilando no debian e derivados

Não prestamos suporte para problemas de compilação em outros sistemas operacionais.

Instale os seguintes pacotes:

    apt-get install coreutils p7zip unzip gzip zstd xz-utils bzip2 tar patch squashfs-tools kmod jq wget curl axel

Siga com a compilação normal conforme explicado no passo anterior executando o script de compilação como root.

### Download de imagens de teste e suporte pela comunidade

DISCORD
https://discord.gg/ktyGckZ
