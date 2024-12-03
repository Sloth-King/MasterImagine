#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <math.h>

#include "Wave.hpp"

double getXk(int k , double w , double T , double amplitude) {
    return amplitude * sin(w * k*T);
}

void createNote(unsigned char * data , int note_freq = 440  , int freq = 44100,  int duration = 6 , double amplitude = 127.5) {
    double T = 1.0/(float)freq;
    double w = 2.0 * M_PI * (float)note_freq;
    int taille_tab = freq * (int)duration;
    double xk;
    for(size_t i = 0; i < taille_tab ; i++){
    xk = getXk(i , w , T , amplitude);
    data[i] = (unsigned char) xk;
    }
}



void createScale(unsigned char * data , int freq = 44100 , int duration = 6 , double amplitude = 127.5) {
    double note_duration = 1;
    int notes[7] = {440, 493, 554, 587, 659, 739, 830};
    int taille_note_tab = freq * note_duration;
    int taille_tab = freq * duration;
    for(size_t i = 0; i < 7; i++){
        unsigned char note_data[taille_note_tab];
        createNote(note_data, notes[i], freq, note_duration, amplitude);
        for(size_t j = 0; j < taille_note_tab; j++){
            data[i * taille_note_tab + j] = note_data[j];
        }
    }
}

void createScaleFourrier(unsigned char * data , int freq = 44100 , int duration = 6 , double amplitude = 127.5) {
    double note_duration = 1;
    int notes[7] = {440, 493, 554, 587, 659, 739, 830};
    int taille_note_tab = freq * note_duration;
    int taille_tab = freq * duration;
    for(size_t i = 0; i < 7; i++){
        unsigned char note_data[taille_note_tab];
        createNote(note_data, notes[i], freq, note_duration, amplitude);
        for(size_t j = 0; j < taille_note_tab; j++){
            data[i * taille_note_tab + j] = note_data[j];
        }
    }
}


void DFT(double *signal , double* partie_reelle , double* partie_imaginaire , int N){
    double alpha = 2 * M_PI / (double)N;
    for(size_t k = 0; k < N; k++){
        double beta = alpha * k;

        partie_reelle[k] = 0;
        partie_imaginaire[k] = 0;

        for(size_t n = 0; n < N; n++){
            partie_reelle[k] += signal[n] * cos(beta * n);
            partie_imaginaire[k] += signal[n] * -sin(beta * n);
        }
    }
}

void IDFT(double *signal , double* partie_reelle , double* partie_imaginaire , int N){
    double alpha = 2 * M_PI / (double)N;
    for(size_t n = 0 ; n < N ; n++){
        signal[n] = 0;
        double beta = alpha * n;
        for(size_t k = 0 ; k < N ; k++){
            signal[n] += partie_reelle[k] * cos(beta*k) - partie_imaginaire[k] * sin(beta * k);
        }
        signal[n] /= (double)N;
    }
}

int FFT(int dir,int m,double *x,double *y)
{
	int n,i,i1,j,k,i2,l,l1,l2;
	double c1,c2,tx,ty,t1,t2,u1,u2,z;
	
	/* Calculate the number of points */
	n = 1;
	for (i=0;i<m;i++) 
		n *= 2;
	
	/* Do the bit reversal */
	i2 = n >> 1;
	j = 0;
	for (i=0;i<n-1;i++) {
		if (i < j) {
			tx = x[i];
			ty = y[i];
			x[i] = x[j];
			y[i] = y[j];
			x[j] = tx;
			y[j] = ty;
		}
		k = i2;
		while (k <= j) {
			j -= k;
			k >>= 1;
		}
		j += k;
	}
	
	/* Compute the FFT */
	c1 = -1.0; 
	c2 = 0.0;
	l2 = 1;
	for (l=0;l<m;l++) {
		l1 = l2;
		l2 <<= 1;
		u1 = 1.0; 
		u2 = 0.0;
		for (j=0;j<l1;j++) {
			for (i=j;i<n;i+=l2) {
				i1 = i + l1;
				t1 = u1 * x[i1] - u2 * y[i1];
				t2 = u1 * y[i1] + u2 * x[i1];
				x[i1] = x[i] - t1; 
				y[i1] = y[i] - t2;
				x[i] += t1;
				y[i] += t2;
			}
			z =  u1 * c1 - u2 * c2;
			u2 = u1 * c2 + u2 * c1;
			u1 = z;
		}
		c2 = sqrt((1.0 - c1) / 2.0);
		if (dir == 1) 
			c2 = -c2;
		c1 = sqrt((1.0 + c1) / 2.0);
	}
	
	/* Scaling for forward transform */
	if (dir == 1) {
		for (i=0;i<n;i++) {
			x[i] /= n;
			y[i] /= n;
		}
	}
	
	return(1);
}


void char_to_double(unsigned char *x , double *res , size_t n){
    for(size_t i = 0 ; i < n ; i++){
        if(x[i] > 255) res[i] = 1.0;
        if(x[i] < 0) res[i] =  0.0;
        res[i] = (double)x[i]/127.5 - 1.0;
    }
}

void double_to_char(double *x , unsigned char * res , size_t n){
    for(size_t i = 0 ; i < n ; i++){
        if(x[i] > 1.0) res[i] = 255;
        if(x[i] < -1.0) res[i] =  0;
        res[i] = (unsigned char)(127.5*(x[i]+1.0));
    }
}

void butterworth(double * signal , double fc , double fe , size_t n){
    double X[n+4] , Y[n+4];
    double *x , *y , A , B , C , D , a , b , c , d , alfa;
    int k;
    alfa = M_PI * (fc/fe);
    A = (1 + 2*alfa + 2*(alfa*alfa) + (alfa * alfa * alfa));
    B = (-3 - 2*alfa + 2*(alfa*alfa) + 3*(alfa * alfa * alfa));
    C = (3 - 2*alfa - 2*(alfa*alfa) + 3*(alfa * alfa * alfa));
    D = (-1 + 2*alfa - 2*(alfa*alfa) + (alfa * alfa * alfa));

    a = alfa*alfa*alfa;
    b = 3*a;
    c = 3*a;
    d = a;   

    for(k = 0 ; k < n+4 ; k++){
        Y[k] = 0.0;
        if(k < 4) X[k] = 0;
        else X[k] = signal[k-4];
    }
    x = X+4 ; y = Y+4;
    for(k = 0 ; k < n ; k++){
        y[k] = a * x[k] + b * x[k+1] + c*x[k-2] + d*x[k-3];
        y[k] -= B*y[k-1] + C*y[k-2] + D*y[k-3];
        y[k] /= A;
        signal[k] = y[k];
    }

}

int main() {
    int freq = 44100;
    double fc = 220; // Cutoff frequency for the Butterworth filter
    int note_freq = 440;
    int duration = 6;
    int taille = freq * duration;
    unsigned char data[taille];
    
    createScale(data, note_freq, freq, duration);
    Wave scale = Wave(data , taille , 1 , freq);
    
    double* partie_reelle = new double[taille];
    double* partie_imaginaire = new double[taille]; 
    double* data2 = new double[taille];

    char_to_double(data, data2, taille);

    butterworth(data2, fc, freq, taille);

    unsigned char* filtered_data = new unsigned char[taille];
    double_to_char(data2, filtered_data, taille);

    Wave filtered_note = Wave(filtered_data, taille, 1, freq);
    filtered_note.write("./src/Sounds/Filtered_Note.wav");

    // Clean up
    delete[] partie_reelle;
    delete[] partie_imaginaire;
    delete[] data2;
    delete[] filtered_data;

    return 0;
}