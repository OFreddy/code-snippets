#include <stdio.h>
#include <stdlib.h>

#include "pid.h"

// Erweiterte Regelstrecke (z. B. ein System 2. Ordnung)
double ProcessModel(double input, double *state, double dt) {
    // Zustandsvariablen
    double a = 0.8; // Dämpfungsfaktor
    double b = 0.2; // Verstärkungsfaktor

    // Zufallsfaktor hinzufügen
    double noise = ((double)rand() / RAND_MAX - 0.5) * 2.0; // Zufall im Bereich [-1, 1]

    // Diskretes Zustandsmodell
    double new_state = a * state[0] + b * input + noise;

    // Aktualisierung der Zustände
    state[0] = new_state;

    return new_state;
}

int main() 
{
    // Beispielhafte Anwendung des PID-Reglers
    T_PID pid;
    PID_Init(&pid, 1.0, 0.1, 0.05, 10); // kp, ki, kd, sample time in ms

    double setpoint = 100.0; // Sollwert
    double actual = 0.0; // Istwert
    double dt = 0.01; // Zeitschritt in Sekunden

	double state[1] = {0.0}; // Zustandsvariable für die Regelstrecke

	PID_SAMPLETIME_MS_TYPE millis = 0;

    // Simulation einer Regelungsschleife
    for (int i = 0; i < 100; i++) 
	{

        double output = PID_Compute(&pid, setpoint, actual, millis);

        // Regelstreckenmodell anwenden
        actual = ProcessModel(output, state, dt);

        printf("Schritt: %d, ms: %d, Sollwert: %.2f, Istwert: %.2f, Ausgabe: %.2f (p: %.2f i: %.2f d: %.2f)\n", 
			i, millis, setpoint, actual, output, pid.pterm, pid.iterm, pid.dterm);
		
		millis += 10;
    }

    return 0;
}