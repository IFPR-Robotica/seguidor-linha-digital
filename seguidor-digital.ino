//Componentes: Ponte H L298D e sensor InfraRed

const int BRANCO = 0;
const int PRETO = 1;

//Veriáveis para sensores de linha e velocidade
int     sensorEsq, sensorLinha, sensorDir;
int     velMin = 120, velMed = 180, velMax = 240; //Velocidades dos motores
int     limiar = 400; //limiar do sensor de luz

//Variáveis para sensores de início e fim de pista
int     sensorFim;
int     contFim = 4; //Conta marcas de início, fim e cruzamentos
boolean flagFim = false; 
long    tempoTotal; //Tempo total da volta
long    tempoExtra = 2000; //Tempo extra para seguir linha


//Definicoes pinos Arduino ligados a entrada da Ponte H
int IN1 = 2;
int IN2 = 4;
int IN3 = 7;
int IN4 = 8;
int  MA = 5; //Motor direito
int  MB = 6; //Motor esquerdo

void setup(){
  
  //Define os pinos como saida  
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);  
  pinMode(IN3, OUTPUT);  
  pinMode(IN4, OUTPUT);
  pinMode(MA,  OUTPUT);  
  pinMode(MB,  OUTPUT);  
  
}

void para_frente(int vel) {
  //Configura velocidade dos motores
  analogWrite(MA, vel);   
  analogWrite(MB, vel);   
  //Aciona o motores 
  digitalWrite(IN1, LOW);  //A 
  digitalWrite(IN2, HIGH); //A
  digitalWrite(IN3, LOW);  //B
  digitalWrite(IN4, HIGH); //B   
}

void vira_esquerda(int vel) {
  //MotorA_frente
  analogWrite(MA, vel);
  digitalWrite(IN1, LOW);  //A 
  digitalWrite(IN2, HIGH); //A  
  
  //MotorB_tras 
  analogWrite(MB, vel);   
  digitalWrite(IN3, HIGH); //B
  digitalWrite(IN4, HIGH);  //B   
}

void vira_direita(int vel) {
  //MotorA_tras
  analogWrite(MA, vel);
  digitalWrite(IN1, HIGH);  //A 
  digitalWrite(IN2, HIGH); //A  
  
  //MotorB_frente 
  analogWrite(MB, vel);   
  digitalWrite(IN3, LOW); //B
  digitalWrite(IN4, HIGH);  //B   
}

void para_motores() {
  //MotorA_para
  digitalWrite(IN1, HIGH);  //A 
  digitalWrite(IN2, HIGH);  //A  
  //MotorB_para 
  digitalWrite(IN3, HIGH);  //B
  digitalWrite(IN4, HIGH);  //B   
}

void segueLinha(){      

  //le os sensores
  sensorDir   = digitalRead(11); 
  sensorLinha = digitalRead(12);
  sensorEsq   = digitalRead(13);

  //Se estiver na linha segue em frente 
  if (sensorLinha == BRANCO){
    para_frente(velMax);    
  }
 
  //Se sensorDir acha linha vire para a direita
  if (sensorDir == BRANCO && sensorLinha == PRETO){
    vira_direita(velMed);
  }
 
  //Se sensorEsq acha linha vire para a esquerda
  if (sensorEsq == BRANCO && sensorLinha == PRETO){
    vira_esquerda(velMed);
  }

}
 
void loop(){
    segueLinha();
    delay(50);
 }
