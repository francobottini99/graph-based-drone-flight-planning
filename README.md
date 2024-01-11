# Planificación de Vuelo para Fumigación

Este proyecto tiene como objetivo planificar el vuelo de un dron que llegue hasta los puntos donde hay malezas y aplique un herbicida. Se logra utilizando un grafo para representar la disposición de los cultivos, malezas y barreras en el terreno.

### Autores:
- **Bottini, Franco Nicolas**
- **Robledo, Valentin**

## Desarrollo

### Clases Implementadas

1. **`Map`**: Genera mapas aleatorios que contienen cultivos, malezas y barreras. La generación respeta ciertas condiciones, como la creación de malezas cuadradas o rectangulares. Proporciona una representación gráfica del problema.

2. **`Drone`**: Dibuja el dron dentro del mapa y se encarga de todos los movimientos, incluyendo la etapa de fumigación.

3. **`Filter`**: Permite identificar grupos de malezas de tamaño mayor o igual a 3x3, generando una lista que contiene cada grupo. También proporciona una lista de barreras.

4. **`Graph`**: Crea un grafo donde cada nodo son grupos de malezas, y los vértices que unen esos nodos representan posibles conexiones entre grupos, siempre y cuando no haya barreras de por medio.

### Algoritmo de Ciclo Hamiltoniano

Implementamos un algoritmo heurístico para encontrar el Ciclo Hamiltoniano en el grafo. El proceso sigue estos pasos:

1. Partimos desde el inicio hacia el nodo cuya arista tiene el menor peso.
2. Marcamos la arista como visitada y repetimos el proceso hasta que todos los nodos hayan sido visitados, asegurándonos de que el nodo final del recorrido tenga conexión con el inicial.
3. Esta solución retorna un Ciclo Hamiltoniano, aunque no asegura ser el más óptimo.

## Representación Gráfica

En la representación gráfica del problema:

- El color verde representa a los cultivos.
- El color amarillo representa las malezas.
- El color rojo representa las barreras.
- El color verde en cuadros representa las malezas fumigadas.
- El punto en color gris es el dron.