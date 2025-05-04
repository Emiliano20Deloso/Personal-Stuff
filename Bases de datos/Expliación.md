# Relaciones entre Entidades

## Clase Jugador
- El Jugador tiene una relación uno a muchos (1:N) con Mazo.
- Es decir, un jugador puede tener varios mazos.

## Clase Mazo
- El Mazo tiene una relación muchos a muchos (N:M) con Carta Pokémon.
- Un mazo puede contener varias cartas.
- Una carta puede estar en varios mazos.

## Clase Carta Pokémon
- Esta clase es simplemente una entidad que define las cartas que los jugadores pueden coleccionar y usar.

## Clase Partida
- Una Partida involucra a dos jugadores.
- Existe una relación de muchos a muchos (N:M) entre Jugador y Partida.

## Clase Torneo
- El Torneo tiene una relación de uno a muchos (1:N) con Partida.
- Un torneo puede involucrar múltiples partidas. 