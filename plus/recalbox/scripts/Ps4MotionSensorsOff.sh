#!/bin/sh
## 
 # Resolve o bug de indentificar 2 controles de PS4 com apenas 1 controle conectado.
 # Funciona apenas com controle de PlayStation 4.
 # Funciona em controle conectado por cabo ou pelo adaptador de controle oficial da Sony.
 # Não funciona com controle conectado por adaptador bluetooth.
 # 
 # Batocera.PLUS
 # Autor:  Alexandre Freire dos Santos
 # E-Mail: alexxandre.freire@gmail.com
 #
 #######################################################################################
 # CONFIGURAÇÃO DO USUÁRIO INÍCIO
 #######################################################################################

##
 # Ativa ou desativa o controle extra indesejado.
 # 0 = Desativa o controle extra.
 # 1 = Deixa ativado o controle extra.
 ##
CONTROLE=0

##
 # Nome dos dispositivos para serem removidos.
 # Os dispositivos de controle são encontrados em /dev/input/by-id
 # Dependendo da versão do Linux os nomes podem ser diferentes.
 # Controles ligados na porta USB
 ##
USB=usb-Sony_Interactive_Entertainment_Wireless_Controller-event-if03

##
 # Nome dos dispositivos para serem removidos.
 # Os dispositivos de controle são encontrados em /dev/input/by-id
 # Dependendo da versão do Linux os nomes podem ser diferentes.
 # Controles ligados pelo Adaptador Wireless Oficial Sony.
 ##
WIRELESS=usb-Sony_Interactive_Entertainment_DUALSHOCK®4_USB_Wireless_Adaptor-event-if03

########################################################################################
# CONFIGURAÇÃO DO USUÁRIO FIM
########################################################################################

##
 # Diretório onde o log é gravado.
 ##
#LOG_FILE=/userdata/system/logs/$(basename $0 .sh).log
LOG_FILE=/dev/null

echo '' >> $LOG_FILE
echo "Data: $(date -Iseconds -u)" >> $LOG_FILE

##
 # Desativa o controle extra indesejado.
 ##
if (( $CONTROLE == 0 )); then

    echo 'Procurando por controle...' >> $LOG_FILE

    if [ -e /dev/input/by-id/$USB ]; then
        echo 'Controle encontrado em: Cabo USB' >> $LOG_FILE
        rm /dev/input/$(ls -l /dev/input/by-id/$USB | cut -d "/" -f 6) || exit 1
        rm /dev/input/by-id/$USB || exit 1
        echo 'O controle extra foi desativado.' >> $LOG_FILE
    elif [ -e /dev/input/by-id/$WIRELESS ]; then
        echo 'Controle encontrado em: Adaptador Wireless Oficial Sony' >> $LOG_FILE
        rm /dev/input/$(ls -l /dev/input/by-id/$WIRELESS | cut -d "/" -f 6) || exit 1
        rm /dev/input/by-id/$WIRELESS || exit 1
        echo 'O controle extra foi desativado.' >> $LOG_FILE
    else
        echo 'Controle não encontrado.' >> $LOG_FILE
        exit 1
    fi
fi

exit 0
