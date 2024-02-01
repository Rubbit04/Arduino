# Proyecto Seta de Emergencia

En este proyecto se elaborará una seta de Emergencia que se montará en un vehículo, parando todos los controles del mismo.

## Ecosistema de Desarrollo

Se ha utilizado un ecosistema de desarrollo llamado *[PlatformIO](https://platformio.org/install/ide?install=vscode)* para la programación del código del sistema. Este ecosistema ofrece mejoras respecto al IDE de Arduino, como un entorno de trabajo unificado independiente del hardware y software utilizado, instalación de toolchains adecuados, identificación de bibliotecas más sencilla, compilación y linkeo de código fuente, detección automática de puertos, etc.

## Pasos para la Instalacion

1. Descargar o clonar este repositorio en su equipo.
2. Lanzar el Arduino IDE o el Visual Studio Code con la extensión [PlatformIO](https://platformio.org/install/ide?install=vscode) instalada.
3. Establecer la conexión entre el Arduino (en este caso nano) con la 'placa de desarrollo'y la placa [CAN mcp2515](https://ww1.microchip.com/downloads/en/DeviceDoc/MCP2515-Stand-Alone-CAN-Controller-with-SPI-20001801J.pdf).
4. Cargar el archivo [main.cpp](https://github.com/Rubbit04/Trabajo_INSIA/blob/Version-3/SetaArduino/src/main.cpp) en el Arduino.
5. Verificar si la configuración del sketch se compila y se carga con el dispositivo que se va a usar.
6. Iniciar el proceso haciendo clic en el botón `compilar` y `cargar`.
7. Verificar los mensajes que se mostrarán en el monitor.

## Explicación del código

Para que el código sea utilizado correctamente y la posibilidad de la depuración y cambio del mismo, se va a proceder a explicar las variables utilizadas y los métodos programados.

Se ha creado un enumeration llamado `EstadoSistema` el cual tiene 4 posibles estados, `Desarmado`, `Desarmado2`, `Pulsado`, `Armado`. Por los cuales va a pasar el sistema según los botones pulsados.

Tras la inicialización del MCP2515 y la asignación de los botones y el LED integrado en uno de ellos, se procede a programar el loop del programa.

Se asigna valores al mensaje a enviar `stmp` y por defecto, al iniciar el sistema, se va al estado **Desarmado** del enum y se procede a enviar un mensaje CAN (en esta versión aleatorio). Si se pulsa la seta de emergencia entonces se irá al estado `Pulsado` no sin antes ejecutar el código restante ya que se ha programado una función `switch()`, la cual muestra por pantalla que se va a ir a un modo Pulsado y que se encienda el LED integrado.

Una vez ya se esté en el caso de `Pulsado` si se despulsa la seta entonces se va ir al caso de `Desarmado2`, en este caso se va a cambiar el mensaje CAN, por tanto, se asignan diferentes valores al vector `stmp` y se procede a enviarlo, después se muestra por pantalla que se va a ir al modo Desarmado.

En el caso de `Desarmado` se enviará el mensaje `stmp` con los valores antiguos y se muestra por pantalla que se va a ir al modo `Desarmado`.

Una vez en el estado `Armado` se apaga el LED integrado y si se pulsa otra vez la seta de emergencia se procede a ir de nuevo al estado `Desarmado`.

## Imágenes del sistema

![msg696414714-5617](https://github.com/Rubbit04/Trabajo_INSIA/assets/73599929/d384956a-6cfb-46a1-89cc-833efa840cc5)

![photo_2024-01-31_11-39-58](https://github.com/Rubbit04/Trabajo_INSIA/assets/73599929/ea36fa0c-98b8-4433-b28a-16ae29e58663)

## Hardware Utilizado

- Botón seta de Emergencia
- Botón LED
- Arduino Nano
- Placa MCP2515
- Base de Aluminio
- Batería Externa

## Funcionalidades

La funcionalidad principal de este sistema es la de parar de enviar datos a la centralita del vehículo cuando se detecta un error o simplemente se quiere detener la ejecución. 
Para eso, se ha programado una serie de pasos que el usuario debe de ejecutar para la correcta puesta en marcha del sistema, identificando tres estados que representan la situación actual del sistema: 

1. Sistema **DESARMADO**
2. Sistema **PULSADO**
3. Sistema **ARMADO**

Para que el sistema se arme y se arme y se puedan transmitir los datos es necesario pulsar el botón LED de color rojo tras el encendido del sistema llevándolo al modo **ARMADO**. Una vez realizado esta acción el sistema es capaz de enviar la información a la ECU del vehículo. Cuando se quiera parar el sistema, simplemente se tiene que pulsar la seta de emergencia llevándolo al modo **PULSADO**, en este momento se ha detenido el envío de datos.

Para volver a enviar datos es necesario **ARMAR** el sistema, esto se hace despulsando el botón seta llevando al sistema al modo **DESARMADO** teniendo que pulsar el botón LED rojo para volver al modo ARMADO y volver a enviar datos.

Cabe destacar que el botón LED rojo se encenderá cuando el sistema esté en modo **DESARMADO** y **PULSADO** y se apagará cuando el sistema esté en modo **ARMADO**.

El sistema también es capaz de enviar mensajes CAN según en el estado en el que se encuentre. Se han creado 4 mensajes distintos:
1. 00-00-00-00-00-00-00-01    -> PULSADO
2. 00-00-00-00-00-00-00-02    -> DESARMADO
3. 00-00-00-00-00-00-00-03    -> ARMADO
                
El sistema capaz de contestar peticiones CAN, es decir, si llega un mensaje CAN con identificador `0x602` con el campo "Specifier" = 0x20, es decir, el mensaje que llega es `20-00-00-00-00-00-00-00` se responderá con una respuesta con el siguiente formato: `40-00-00-00-00-00-00-0X` siendo `x` los 3 estados del sistema (1,2,3).

