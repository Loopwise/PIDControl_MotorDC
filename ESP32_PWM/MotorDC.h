// Puente H -> L298N
// Pin Alimentación1 -> MA
// Pin Alimentación2 -> MB
// Pin PWM -> Velocidad
// EncA , EncB -> Velocidad (Realimentada)
// Reduccion
// Máxima RPM
// PPR -> Pulses Per Revolution: 12 en Pololu (Después cambia con el ratio)
class MotorDC{
    private: // Atributos
        long t = 0;
        int EN1, EN2;
        int ENM;
        int encA, encB;
        float velocityA = 0, velocityB = 0;
        float ratio;
        int ppr = 12;
        volatile long contA = 0;
        volatile long contB = 0;
        int max_RPM;
        
    public: // Métodos
        MotorDC();
        MotorDC(int MA, int MB, int PWM, int encA, int encB);

        void begin(float ratio);
        void start(bool state);
        
        int get_encA();
        int get_encB();

        void set_PWM(int value);
        float get_VelocityA();
        float get_VelocityB();

        void LectA(){
          this -> contA++;
        }
        void LectB(){
          this -> contB++;
        }
};
