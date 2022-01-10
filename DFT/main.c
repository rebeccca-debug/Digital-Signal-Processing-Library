#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define     SIG_LENGTH      320

extern double InputSignal_f32_1kHz_15kHz[320];
double Output_REX[SIG_LENGTH/2];
double Output_IMX[SIG_LENGTH/2];
double Output_MAG[SIG_LENGTH/2];

void calc_sig_dft(double *sig_src_arr,double *sig_dest_rex_arr, double *sig_dest_imx_arr, int sig_length);
 void get_dft_output_mag(double *sig_dest_mag_arr);

int main()
{
     FILE *fptr,*fptr2,*fptr3,*fptr4;

    calc_sig_dft((double *)&InputSignal_f32_1kHz_15kHz[0],(double *)&Output_REX[0],(double *)&Output_IMX[0], (int )SIG_LENGTH);
    get_dft_output_mag((double *)&Output_MAG[0]);

    fptr = fopen("input_signal.dat","w");
    fptr2=fopen ("output_rex.dat","w");
    fptr3=fopen("output_imx.dat","w");
    fptr4=fopen("output_mag.dat","w");

    for(int i=0;i<SIG_LENGTH;i++){
    fprintf(fptr,"\n%f",InputSignal_f32_1kHz_15kHz[i]);
    }

    for(int i=0;i<(SIG_LENGTH/2);i++)
    {
        fprintf(fptr2,"\n%f",Output_REX[i]);
        fprintf(fptr3,"\n%f",Output_IMX[i]);
        fprintf(fptr4,"\n%f",Output_MAG[i]);

    }

    fclose(fptr);
    fclose(fptr2);
    fclose(fptr3);
    fclose(fptr4);

    return 0;
}

void calc_sig_dft(double *sig_src_arr,double *sig_dest_rex_arr, double *sig_dest_imx_arr, int sig_length)
{
  int i,j,k;
  double PI = 3.14159265359;

  for(j=0;j<sig_length/2;j++)
  {
      sig_dest_rex_arr[j] =0;
      sig_dest_imx_arr[j] =0;

  }

    for(k=0;k<(sig_length/2);k++)
    {
        for(i=0;i<sig_length;i++)
        {
            sig_dest_rex_arr[k] = sig_dest_rex_arr[k] + sig_src_arr[i]*cos(2*PI*k*i/sig_length);
            sig_dest_imx_arr[k] = sig_dest_imx_arr[k] - sig_src_arr[i]*sin(2*PI*k*i/sig_length);
        }
    }


}
 void get_dft_output_mag(double *sig_dest_mag_arr)
 {

     int k;
     for(k=0;k<SIG_LENGTH/2;k++)
     {
         sig_dest_mag_arr[k] = sqrt(pow(Output_REX[k],2)+pow(Output_IMX[k],2));
     }
 }
