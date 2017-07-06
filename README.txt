
BRIEF DESCRIPTION

Modulation format - BPSK. Noise - AWGN. There is only simplest receiver so far - it has no
difference in receiving between M-sequence and random sequence. BER is computed and compared
with theoretical value.


SIMPLEST DESCRIPTION FOR EVERYBODY. WITH MINIMUMIZED LEVEL OF MATH.
— Classes Transmitter and Noise. Generated binary sequence {a_n}, n-th symbol defined by recurrence equation:
		a_n = c_1 * a_(n-1) ^ c_2 * a_(n-2) ^ … ^ c_M * a_(n-M),   (1)
where c_1, c_2, c_n - some constant boolean coefficients (named COEFFS[] or taps[] in program),
M - some constant value - in a lot of papers it’s named lowercase «m», but in the very simulation it is «M» for
emphasizing that this is a constant value. Then transmission of signal is simulated: 1) «true» 
redefined as 1, and  «false» redefined as -1 2) Random real number is added to every element in transmitted array 
(class Noise)
— Class SimplestReceiver. The receiver is simplest: if signal > 0 then value «true» was received, else - «false»
— Class Stat.

Краткое описание

Моделируется передача и приём M-последовательности. Вид модуляции - BPSK. Помехи - аддитивный
белый гауссов шум. Пока реализован только простейший случай приёмника - как будто принимается
случайная последовательность битов, а не M-последовательность. Вычисляется вероятность ошибки,
она сверяется с теоретическим значением.