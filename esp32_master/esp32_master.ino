#include <SPI.h> // transceivers NRF usam o protocolo de comunicação Serial Peripheral Interface. Essa biblioteca gerencia os pinos MOSI, MISO e SCK (IRQ é opcional). A biblioteca RF24 requere o uso dela.
#include <RF24.h>

#define CE_PIN 4
#define CSN_PIN 5

// Cria objeto rádio, utilizando os pinos Chip Enable e Chip Select Not. Ambos são os únicos pinos controlados via software. O restante é gerenciado em baixo nível pelas bibliotecas definidas anteriormente.
RF24 radio(CE_PIN, CSN_PIN);

// Endereço do pipe (canal de comunicação), pode ter até 5 bytes.
// obs: um mestre pode mandar informação para até 6 escravos simultaneamente
const byte address[6] = "00001";

void setup() {
  
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);

    //Checa se o rádio conseguiu inicializar
    if (!radio.begin()) {
        Serial.println("Erro ao inicializar");
        while (1);  
    }

    // Configura o canal de escrita com base no endereço anterior de 5 bytes
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_LOW); // Power level: low -> intensidade da transmissão, baixo alcance, serve para poupar consumo energético, mas pode causar packet loss em outros cenários
    radio.stopListening();         // Configura o rádio para modo de envio
}

void loop() {
  
    // Mensagem a ser enviada
    // obs: os rádios NRF suportam até 32 bytes de informação
    // texto é uma maneira ineficiente de transmitir dados, aí que notações estruturadas entram (protobuf, JSON...)
    const char text[] = "Olá escravo";
    
    // Envia a mensagem
    bool success = radio.write(&text, sizeof(text));

    // Checa se a mensagem foi enviada com sucesso
    if (success) {
        Serial.println("Mensagem enviada!");
        digitalWrite(LED_BUILTIN, LOW);
    } else {
        Serial.println("Mensagem falhou");
        digitalWrite(LED_BUILTIN, HIGH);
    }

    delay(1000);
}
