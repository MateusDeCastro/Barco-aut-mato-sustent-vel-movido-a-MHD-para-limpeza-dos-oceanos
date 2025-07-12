#include <WiFi.h>
#include <ESP32Servo.h>

const char* ssid = "Aranha";
const char* password = "adrianoeelida2018";

Servo myServo;  
int servoPin = 18;

WiFiServer server(80);

// Declarações de funções
void serveLoginHTML(WiFiClient client);
void serveHomeHTML(WiFiClient client);
void serveMenuHTML(WiFiClient client);

void setup() {
    myServo.attach(servoPin);
    Serial.begin(115200);
    pinMode(5, OUTPUT);

    WiFi.begin(ssid, password);
    Serial.print("Conectando a ");
    Serial.println(ssid);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi conectado.");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());

    server.begin();
}

void loop() {
    WiFiClient client = server.available();  

    if (client) {
        Serial.println("Novo cliente.");
        String request = "";  
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);  
                request += c;     

                if (c == '\n') {  // Se o byte for uma nova linha, processa a requisição
                    // Verifica o tipo de requisição
                    if (request.indexOf("GET /left") != -1) {
                        myServo.write(135);  // Gira o servo para 135 graus (esquerda)
                    }
                    if (request.indexOf("GET /straight") != -1) {
                        myServo.write(90);  // Gira o servo para 90 graus (linha reta)
                    }
                    if (request.indexOf("GET /right") != -1) {
                        myServo.write(45);  // Gira o servo para 45 graus (direita)
                    }
                    if (request.indexOf("GET /") != -1) {
                        serveHomeHTML(client);  
                    }
                    break; // Corrigido para sair do loop corretamente após processar a requisição
                }
            }
        }
        client.stop();
        Serial.println("Cliente desconectado.");
    }
}

void serveHomeHTML(WiFiClient client) {
    client.println("<!DOCTYPE html>");
    client.println("<html lang=\"pt-br\">");
    client.println("<head>");
    client.println("<meta charset=\"UTF-8\">");
    client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
    client.println("<title>Home</title>");
    client.println("<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css\" rel=\"stylesheet\">");
    client.println("<link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/bootstrap-icons@1.11.3/font/bootstrap-icons.min.css\">");
    client.println("<style>");
    client.println("body {");
    client.println("    background-color: #e6f3ff; /* Cor de fundo azul claro */");
    client.println("}");
    client.println(".navbar {");
    client.println("    box-shadow: 0 2px 4px rgba(0,0,0,.1);");
    client.println("    background-color: #191970 !important; /* Azul meia-noite */");
    client.println("}");
    client.println(".card {");
    client.println("    transition: transform 0.3s;");
    client.println("    background-color: rgba(255, 255, 255, 0.9); /* Fundo branco semi-transparente para os cards */");
    client.println("}");
    client.println(".card:hover {");
    client.println("    transform: translateY(-5px);");
    client.println("}");
    client.println(".navbar-brand, .nav-link {");
    client.println("    font-size: 20px;");
    client.println("    color: white !important; /* Forçando a cor branca */");
    client.println("}");
    client.println(".navbar-brand:hover, .nav-link:hover {");
    client.println("    color: rgba(255,255,255,0.8) !important; /* Efeito hover suave */");
    client.println("}");
    client.println(".text-justify {");
    client.println("    text-align: justify;");
    client.println("}");
    client.println("</style>");
    client.println("</head>");

    client.println("<body>");
    
    // Navbar
    client.println("<nav class=\"navbar navbar-expand-lg navbar-dark style=\"background-color: #191970;\">");
    client.println("<div class=\"container\"><a class=\"navbar-brand\" href=\"#\"><i class=\"bi bi-water me-2\"></i>Home</a>");
    client.println("<div class=\"collapse navbar-collapse\" id=\"navbarNav\">");
    client.println("<ul class=\"navbar-nav ms-auto\">");
    client.println("<li class=\"nav-item\"><a class=\"nav-link\" href=\"#section1\">Controle</a></li>");
    client.println("<li class=\"nav-item\"><a class=\"nav-link\" href=\"#section2\">Trajetos</a></li></ul></div></div></nav>");

    // Section Controle do Barco
    client.println("<section id=\"section1\" class=\"container my-5\"><div class=\"card shadow\"><div class=\"card-body\">");
    client.println("<h2 class=\"card-title text-center mb-4\">Controle do Barco</h2>");
    client.println("<form><div class=\"mb-3\"><label for=\"barco-id\" class=\"form-label\">ID do barco</label>");
    client.println("<input type=\"text\" class=\"form-control\" id=\"barco-id\" placeholder=\"Digite o ID\"></div>");
    client.println("<div class=\"mb-4\"><h3 class=\"mb-3\">Localização Atual</h3>");
    client.println("<div class=\"ratio ratio-16x9\"><iframe src=\"https://www.google.com/maps/embed?...\" allowfullscreen=\"\" loading=\"lazy\"></iframe></div></div>");
    client.println("<div class=\"mb-3\"><label for=\"localizacao-final\" class=\"form-label\">Localização final</label>");
    client.println("<input type=\"text\" class=\"form-control\" id=\"localizacao-final\" placeholder=\"Digite a localização final\"></div>");
    client.println("<div class=\"text-center\"><button type=\"submit\" class=\"btn btn-primary\">Enviar</button></div></form>");

    // Controle Manual
    client.println("<div class=\"mt-5\"><h3 class=\"text-center mb-4\">Controle manual</h3>");
    client.println("<div class=\"d-flex justify-content-center\"><div class=\"btn-group\">");
    client.println("<a href=\"/left\" class=\"btn btn-outline-primary\"><i class=\"bi bi-arrow-left\"></i> Esquerda</a>");
    client.println("<a href=\"/straight\" class=\"btn btn-outline-primary\"><i class=\"bi bi-arrow-up\"></i> Linha reta</a>");
    client.println("<a href=\"/right\" class=\"btn btn-outline-primary\"><i class=\"bi bi-arrow-right\"></i> Direita</a>");
    client.println("</div></div></div>");
  
    // Section Trajetos Finalizados
    client.println("<section id=\"section2\" class=\"container my-5\"><div class=\"card shadow\"><div class=\"card-body\">");
    client.println("<h2 class=\"card-title text-center mb-4\">Trajetos Finalizados</h2>");
    client.println("<div class=\"table-responsive\"><table class=\"table table-hover\"><thead class=\"table-light\">");
    client.println("<tr><th>ID</th><th>Hora de saída</th><th>Hora de chegada</th><th>Data de saída</th><th>Data de chegada</th><th>Local de saída</th><th>Local de chegada</th><th>Status</th></tr></thead><tbody>");
    client.println("<tr><td>01</td><td>20:00</td><td>01:00</td><td>08/08/2024</td><td>10/08/2024</td><td>Santos</td><td>Paranaguá</td><td><span class=\"badge bg-secondary\">Inativo</span></td></tr>");
    client.println("<tr><td>02</td><td>10:00</td><td>11:00</td><td>15/08/2024</td><td>20/08/2024</td><td>Santos</td><td>Itapoá</td><td><span class=\"badge bg-secondary\">Inativo</span></td></tr>");
    client.println("</tbody></table></div></div></div></section>");

    client.println("</body></html>");
}


