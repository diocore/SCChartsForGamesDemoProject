/*
 * Automatically generated C code by
 * KIELER SCCharts - The Key to Efficient Modeling
 *
 * http://rtsys.informatik.uni-kiel.de/kieler
 */

#include "RollingBall.h"

void RB_Logic(RB_TickData* d) {
  d->error = d->targetV - d->currentV;
  d->prevError = d->error;
  d->P = d->Kp * d->error;
  d->I += d->error * d->deltaT;
  d->D = (d->error - d->prevError) / d->deltaT;
  d->accel = d->P + d->Ki * d->I + d->Kd * d->D;
  if (!d->_GO) {
    d->t += d->deltaT;
  }
  d->sleepT = 1000.0;
}

void RB_Reset(RB_TickData* d) {
  d->_GO = 1;
  d->_TERM = 0;
  d->targetV = 10;
  d->currentV = 0;
  d->deltaT = 0;
  d->prevError = 0;
  d->error = 0;
  d->t = 0;
  d->sleepT = 0.0;
}

void RB_Tick(RB_TickData* d) {
  RB_Logic(d);

  d->_GO = 0;
}
