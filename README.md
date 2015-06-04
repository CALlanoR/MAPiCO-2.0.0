
MAPiCO C Version 2.0.0.1
************************

La Máquina Abstracta MAPiCO es la implementación de una máquina abstracta 
para el Cálculo PiCO, esta máquina sigue la especificación y las reglas de 
reducción de dicho Cálculo, que es la base del modelamiento matemático, 
sólido y formal del lenguaje de programación Cordial.
MAPiCO se reimplementó utilizando el lenguaje C, considerando las modificaciones 
del cálculo y la extensión del conjunto de instrucciones a través de módulos 
dinámicos que garantiza en un futuro no volver a rediseñar la Máquina.

La Máquina fue diseñada e implementada en la Pontificia Universidad Javeriana de Cali -COLOMBIA

La ultima version de MAPiCO se puede obtener de: 
 http://gforge.puj.edu.co/projects/mapico2

Para compilar mapico:

1. ./configure
2. make
3. cd plugins; make

Se generan 2 librerias:
- libCS.so (libCS.a) :         Sistema de restricciones 
- libmapico.so (libmapico.a) : Funciones propias de mapico, usado para compilar 
                               los plugins 
Las librerias estan dentro del directorio .libs en constsys y mapico respectivamente

El ejecutable de la maquina abstracta se llama mapico dentro del directorio mapico            

Autores:
   - Antal Buss.
   - Alba Liliana Sarasti.
   - Carlos Alberto Llano R.             