#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIG_LENGTH 320

extern double Input_Signal_f32_1kHz_15kHz[SIG_LENGTH];
double calc_signal_mean(double *sig_src_arr, int sig_length);
double calc_signal_variance(double *sig_src_arr, double sig_mean, int sig_length);
double calc_signal_std(double sig_variance);

double MEAN;
double VARIANCE;
double STD;

/** @brief: Signal statistical algorithms in C. Calculate the mean, variance, and standard deviation of the ECG signals.
*
*/
int main(){

    MEAN = calc_signal_mean(&Input_Signal_f32_1kHz_15kHz[0], SIG_LENGTH);
    VARIANCE = calc_signal_variance(&Input_Signal_f32_1kHz_15kHz[0], MEAN, SIG_LENGTH);
    STD = calc_signal_std(VARIANCE);
    printf("\n\nMean = %f\n\n\n", MEAN);
    printf("\n\nVariance = %f\n\n\n", VARIANCE);
    printf("\n\nStandard = %f\n\n\n", STD);

    return 0;
}

/** @brief: Calculate the mean of the signal. Algorithm: μ = 1/N * ^(N-1)Σ_(i=0)x_i
* @param sig_src_arr double pointer to signal array
* @param sig_lenth integer representing length of the signal
*/
double calc_signal_mean(double *sig_src_arr, int sig_length){
    double _mean = 0.0;
    for (int i = 0; i < sig_length; i++){
        _mean = _mean + *sig_src_arr;
    }

    _mean = _mean/(double)sig_length;
    return _mean;
}

/** @brief: Calculate the mean of the signal (how far 'i' deviates from the mean). Algorithm: 1/(N-1) * σ = ^1/(N-1)Σ_(i=0)(x_i-μ)^2
* @param sig_src_arr double pointer to signal array
* @param sig_mean double representing the signal mean
* @param sig_length integer representing length of the signal
*/
double calc_signal_variance(double *sig_src_arr, double sig_mean, int sig_length){
    double _variance = 0.0;
    for (int i = 0; i < sig_length; i++){
        _variance = _variance + pow((sig_src_arr[i]-sig_mean),2);
    }

    _variance = _variance/(sig_length-1);
    return _variance;
}

/** @brief: Calculate the mean of the signal. Algorithm: σ^2 = (^1/(N-1)Σ_(i=0)((x_i-μ)^2))^2
* @param sig_variance double representing the variance of the signal
*/
double calc_signal_std(double sig_variance){
    double _std = sqrt(sig_variance);
    return _std;
}
