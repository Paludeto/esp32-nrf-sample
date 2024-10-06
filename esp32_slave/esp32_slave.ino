#include <SPI.h> // transceivers NRF usam o protocolo de comunicação Serial Peripheral Interface. Essa biblioteca gerencia os pinos MOSI, MISO e SCK (IRQ é opcional). A biblioteca RF24 requere o uso dela.
#include <RF24.h>

#define CE_PIN 4
#define CSN_PIN 5


RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "00001"; // Mesmo endereço do master

void setup() {
    
    Serial.begin(115200);

    if (!radio.begin()) {
        Serial.println("Erro ao inicializar");
        while (1); 
    }

    radio.openReadingPipe(0, address); // Abre o pipe com o endereço anterior para ser lido
    radio.setPALevel(RF24_PA_LOW);
    radio.startListening();         // Configura o rádio para começar o recebimento
}

void loop() {
    
    if (radio.available()) {
        char text[32] = {0};  // Buffer de 32 bytes para armazenar os dados recebidos
        
        // Lê os dados recebidos
        radio.read(&text, sizeof(text));

        Serial.print("Mensagem recebida: ");
        Serial.println(text);
    }

    delay(1000);
}
