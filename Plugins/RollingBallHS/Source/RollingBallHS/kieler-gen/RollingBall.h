#ifndef ROLLINGBALL_H
#define ROLLINGBALL_H
/*
 * Automatically generated C code by
 * KIELER SCCharts - The Key to Efficient Modeling
 *
 * http://rtsys.informatik.uni-kiel.de/kieler
 */

typedef struct {
  double accel;
  double targetV;
  double currentV;
  double Kp;
  double Ki;
  double Kd;
  double deltaT;
  double prevError;
  double error;
  double P;
  double I;
  double D;
  double t;
  double sleepT;
  char _GO;
  char _TERM;
} RB_TickData;

void RB_Reset(RB_TickData* d);
void RB_Logic(RB_TickData* d);
void RB_Tick(RB_TickData* d);

#endif /* !ROLLINGBALL_H */
