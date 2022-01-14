#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define SIG_LENGTH 501

extern double _501pts_20Hz_sig_imx[SIG_LENGTH];
extern double _501pts_20Hz_sig_rex[SIG_LENGTH];

double Output_rex[SIG_LENGTH];
double Output_imx[SIG_LENGTH];



void complex_dft(double *sig_src_time_domain_rex,
                 double *sig_src_time_domain_imx,
                 double *sig_dest_freq_domain_rex,
                 double *sig_dest_freq_domain_imx,
                 int sig_length
                 );



int main()
{
   FILE *input_rex_fptr,*input_imx_fptr,*output_rex_fptr,*output_imx_fptr;




      complex_dft((double *)&_501pts_20Hz_sig_rex[0],
                 (double *)&_501pts_20Hz_sig_imx[0],
                 (double *)&Output_rex[0],
                 (double *)&Output_imx[0],
                 (int) SIG_LENGTH
                 );

    input_rex_fptr = fopen("input_rex.dat","w");
    input_imx_fptr = fopen("input_imx.dat","w");
    output_rex_fptr = fopen("output_rex.dat","w");
    output_imx_fptr  = fopen("output_imx.dat","w");

    for(int i =0;i<SIG_LENGTH;i++)
    {
        fprintf(input_rex_fptr,"\n%f",_501pts_20Hz_sig_rex[i]);
        fprintf(input_imx_fptr,"\n%f",_501pts_20Hz_sig_imx[i]);
        fprintf(output_rex_fptr,"\n%f",Output_rex[i]);
        fprintf(output_imx_fptr,"\n%f",Output_imx[i]);
    }

    fclose(input_rex_fptr);
    fclose(input_imx_fptr);
    fclose(output_rex_fptr);
    fclose(output_imx_fptr);

    return 0;
}


void complex_dft(double *sig_src_time_domain_rex,
                 double *sig_src_time_domain_imx,
                 double *sig_dest_freq_domain_rex,
                 double *sig_dest_freq_domain_imx,
                 int sig_length
                 )
{
     double PI = 3.14159265;
     double SR, SI;
     for(int k =0;k<sig_length-1;k++)
     {
         for(int i=0;i<sig_length-1;i++)
         {
             SR = cos(2*PI*k*i/sig_length);
             SI = -sin(2*PI*k*i/sig_length);

             sig_dest_freq_domain_rex[k]  = sig_dest_freq_domain_rex[k]+ sig_src_time_domain_rex[i]*SR - sig_src_time_domain_imx[i]*SI;
             sig_dest_freq_domain_imx[k]  = sig_dest_freq_domain_imx[k]+ sig_src_time_domain_imx[i]*SI -sig_src_time_domain_imx[i]*SR;
         }
     }


}
