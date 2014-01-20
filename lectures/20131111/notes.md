# Variation of color components #
Blue - White - Red

v = Results value. Transformed from SEGY.
S = Splitter value. Enables focus of value range.

< 0:
* Red   = v/s
* Green = v/s
* Blue  = 1

>= 0:
* Red   = 1
* Green = (1-v)/(1-s)
* Blue  = (1-v)/(1-s)

# Fragment Shader #
Input:
* v: Transformert SEGY sample value [0.0, 1.0]
* s: Splitter verdi fra kontroll av fargekoding [0.0, 1.0]


# Eksamen #
* Forskjell mellom tegnemetoder (glBegin/glEnd og vertexarray).
* Teksturering er viktig
* Lighting
* Shader forståelse. Argumenttyper. Kodeforståelse. Diskusjon.
