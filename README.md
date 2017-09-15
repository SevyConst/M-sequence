#### English

There is a simulation of transmission and receiving of binary [maximum length sequence](https://en.wikipedia.org/wiki/Maximum_length_sequence) also known as M-sequence. Modulation format - BPSK. Noise - AWGN. There is only the simplest receiver so far: it has no difference in receiving between M-sequence and a random sequence; optimized receiver with acquisition will be added later, in other words at this stage the program has the form of example of use some functions from file [mainFunctions.h](https://github.com/SevyConst/M-sequence/blob/master/mainFunctions.h).

There are initial parameters of simulation in [param.json](https://github.com/SevyConst/M-sequence/blob/master/param.json).

The function that generates M-sequence (from [mainFunctions.h](https://github.com/SevyConst/M-sequence/blob/master/mainFunctions.h)):

``` c++
std::vector<bool> genMseq(std::vector<bool> iniState,
                          unsigned int numSamples,
                          std::vector<unsigned int> taps)
```
Parameters: `<std::vector<bool> iniState>` - initial state of linear feedback shift register (LFSR),

`c++<unsigned int numSamples>` - number of samples (bits) in returned sequence,

`cpp<std::vector<unsigned int> taps>` - taps of LFSR. The 0-th bit is always a tap.

Returns: ```std::vector<bool>``` - generated sequence.

There is test for this function (in the directory [Tests/genMseqTest/](https://github.com/SevyConst/M-sequence/tree/master/Tests/genMseqTest)) which checks with analog from [SciPy](https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.max_len_seq.html) (Python 3).

Also there is a function overloading for generating by a random initial state of LFSR.

```c++
std::vector<bool> genMseq(unsigned int lengthLFSR,
                              unsigned int numSamples,
                              std::vector<unsigned int> taps);
```
where ```unsigned int lengthLFSR``` - number of bits in LFSR.

The bit error rate (BER) of receiving is computed  in the integration test ([Tests/ChannelIntegrTest.cpp](https://github.com/SevyConst/M-sequence/blob/master/Tests/ChannelIntegrTest.cpp)). The achieved value is compared with the theoretic value.

#### Русский

Моделируется передача и приём бинарной [последовательности максимальной длины](https://en.wikipedia.org/wiki/Maximum_length_sequence), так же известной как M-последовательность. Вид модуляции - BPSK. Помехи - аддитивный белый гауссов шум. Пока реализован только простейший случай приёмника: как будто принимаются просто биты, а не M-последовательность; оптимизированный приёмник c синхронизацией будет добавлен позже, то есть на данный момент программа представляет собой просто пример использования некоторых функций из файла [mainFunctions.h](https://github.com/SevyConst/M-sequence/blob/master/mainFunctions.h).

Начальные параметры моделирования находятся в param.json.

Функция, которая генерирует M-последовательность (файл mainFunctions.h):

```cpp
std::vector<bool> genMseq(std::vector<bool> iniState,
                          unsigned int numSamples,
                          std::vector<unsigned int> taps)
```
Параметры: ```std::vector<bool> iniState``` - начальное состояние регистра сдвига с линейной обратной связью,

```unsigned int numSamples``` - количество отсчётов (бит) в сгенерированной последовательности,

```std::vector<unsigned int> taps``` - отводы. Нулевой бит всегда является отводом.

Возвращаемое значение: ```std::vector<bool>``` - сгенерированная последовательность.

Для данной функции написан тест (директория [Tests/genMseqTest/](https://github.com/SevyConst/M-sequence/tree/master/Tests/genMseqTest)), который сверяет её работу с аналогом из [SciPy](https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.max_len_seq.html) (Python 3).

Также для этой функции добавлена перегрузка для генерации со случайным начальным состоянием регистра сдвига:

``` cpp
std::vector<bool> genMseq(unsigned int lengthLFSR,
                              unsigned int numSamples,
                              std::vector<unsigned int> taps);
```
где ```unsigned int lengthLFSR``` - длина регистра.

В интеграционном тесте ([Tests/ChannelIntegrTest.cpp](https://github.com/SevyConst/M-sequence/blob/master/Tests/ChannelIntegrTest.cpp)) вычисляется вероятность битовой ошибки. Полученное значение сверяется с теоретическим.