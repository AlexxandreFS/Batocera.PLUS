## Batocera.PLUS

### O que é o Batocera.PLUS?

O Batocera.PLUS é um sistema operacional minimalista (filmware) que transforma um PC 64 bits  em um console dedicado a retro emulação.

O Batocera.PLUS é uma versão modificada do batocera.linux que adiciona diversos recursos extras ao sistema, bem como correções de erros e personalizações.

O Batocera.PLUS não é uma imagem pronta com jogos, temas e customizações, trata-se de uma imagem limpa com recursos nunca antes vistos em um sistema de retro emulação.

O Batocera.PLUS não é um fork do projeto original e sim de um conjunto de scripts, patch, programas, etc… que adiciona diversas funcionalidades ao sistema original.


### O nascimento do Batocera.PLUS

O conceito do Batocera.PLUS surgiu como uma resposta para um problema.

No princípio, pelas comunidades na internet eu compartilhava alguns programas, scripts, emuladores, métodos de dualboot, entre outros para serem instalados pelo usuário no batocera.linux mas muitos usuários não conseguiam seguir os procedimentos para fazer as instalações, então surgiu a ideia de criar uma imagem com todas estas modificações já implementadas e assim surgiu o Batocera.PLUS.


### Como baixar o código fonte

O Batocera.PLUS já vem com o git instalado. Clone o repositório.

    git clone https://github.com/AlexxandreFS/Batocera.PLUS.git

Para atualizar um repositório anteriormente clonado, acesse o repositório local.

    cd Batocera.PLUS

Atualize o repositório.

    git reset --hard
    git clean -f
    git pull https://github.com/AlexxandreFS/Batocera.PLUS.git


### Como compilar

<b>A Imagem do Batocera.PLUS é compilada usando a versão anterior do próprio Batocera.PLUS.</b>

A pasta temporária usada na compilação precisa ficar em uma partição do tipo Linux (ext4, btrfs, etc)

Acesse a pasta onde estão os arquivos pelo terminal (win + f4) ou (f1 e depois f4) e execute o script de criação da imagem.

    ./build-batocera.plus

Durante a compilação vários pacotes extras serão baixados, seja paciente.


### Compilando no debian e derivados.

Instale os seguintes pacotes: (apt-get install)

    p7zip
    unzip
    gzip
    zstd
    squashfs-tools
    coreutils
    wget
    curl

Execute o script de criação da imagem como usuário root, (su "sua senha de root") e siga com a compilação normal conforme explicado no passo anterior.

Não prestamos suporte para problemas de compilação em outros sistemas operacionais.


### Compilar a imagem Nvidia Legancy Driver 390

Edite e altere o valor da variável NVIDIA_LEGACY para 1 no início do script de compilação "build-batocera.plus" e siga com a compilação normalmente.


### Download de imagens de teste e suporte pela comunidade

DISCORD
https://discord.gg/ktyGckZ

