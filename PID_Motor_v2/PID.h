class PID{
  private:
    double Kp, Ki, Kd, SetPoint;
    double last_error = 0, error = 0, accum_error = 0, rate_error = 0;
    double t0, t1;
    volatile float* Variable;
  public:
    PID();
    PID(double Kp, double Ki, double Kd);
    PID(double Kp, double Ki, double Kd, volatile float* Variable);

    void begin();
    void set_Point(double SetPoint);
    void Link(volatile float *variable);
    double compute();
};
