# Decodificador de Codigo Morse para Arduino

## Descrição

Projeto que consegue enviar ou receber uma mensagem em código morse de um Arduino para um computador. Para mostrar a mensagem usamos o padrão do código morse de unidades de tempo (u). O ponte tem 1u, o traçõ 3u, o espaço entre letras 5u e entre palavras 7u.

## Envio

O programa traduz uma mensagem escrita no terminal para código morse e manda para a placa. Ela então usa a luz e o microfone para mostrar a mensagem. A unidade de tempo usada é 200 milisegundos.

## Recepção

A placa tem um botão e duas luzes (uma amarela e uma azul) para o envio de mensagens. O programa leva em conta que pode haver um erro do operador durante o envio da mensagem. Ele recebe a mensagem dada pelo operador, traduz ela para código morse usando um "dicionario" e imprime ela no terminal.

## Grupo:
Luís Otávio Machado Ferreira
Luca Maciel Alexander
Maria Fernanda Lucio de Mello
Leonardo Fonseca Pinheiro
