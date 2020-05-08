# Projeto_TC_2017

Projeto desenvolvido para o Trabalho de Curso no ano de 2017 para a graudação em Engenharia Elétrica com ênfase em automação e controle na Universidade de Santa Cruz do Sul.

A ideia inicial antes de começar a desenvolver o software era contruir um projeto unindo a automação e visão computacional em um processo produtivo, como por exemplo na inspeção de peças em uma esteira industrial, onde o sistema poderia identifcar quais peças possuiam defeito e quais estavam ok, com isso descartar ou coletar as peças defeituosas com um robô Scara, Cartesiano ou Delta através das coordenadas das peças onde o sistema de visão computacional iria continuar rastreando em tempo real e fornecer os dados para o CLP efetuar a automação do descarte. Porém como este tipo de projeto involveria muito investimento de capital e também tempo para desenvolvimento, não se encaixando no semestre, foi optado por desenvolver apenas a parte principal do software, que efetua a inspeção de qualidade e rastreamento para fornecimento das coordenadas das peças em um "processo indutrial simulado".

Utilizando a biblioteca OpenCV foi possível processar as imagens obtidas de duas câmeras, uma com função de inspecionar e outra com função de ratrear a peças na sequência. O código foi desenvolvido em C++ sem uso de programação paralela em GPU na época e a interface foi criada com a ferramenta Qt Creator, sem fins comerciais.

Estam disponíveis no repositório os arquivos de apresentação do trabalho, um exemplo de funcionamento em um vídeo, a pasta com o *executável* do software e os códigos desenvolvidos em C/C++ e na plataforma de desenvolvimento Qt Creator.

*O executável não está funcionando diretamente apenas com as dlls dispostas, acredito que instalando o Qt Creator funcione ou então necessita alguma configuração no código ou algum detalhe para corrigir isso.*
