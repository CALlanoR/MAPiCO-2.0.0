
MAPiCO C Version 2.0.0.1
************************

La M�quina Abstracta MAPiCO es la implementaci�n de una m�quina abstracta 
para el C�lculo PiCO, esta m�quina sigue la especificaci�n y las reglas de 
reducci�n de dicho C�lculo, que es la base del modelamiento matem�tico, 
s�lido y formal del lenguaje de programaci�n Cordial.
MAPiCO se reimplement� utilizando el lenguaje C, considerando las modificaciones 
del c�lculo y la extensi�n del conjunto de instrucciones a trav�s de m�dulos 
din�micos que garantiza en un futuro no volver a redise�ar la M�quina.

La M�quina fue dise�ada e implementada en la Pontificia Universidad Javeriana de Cali -COLOMBIA

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