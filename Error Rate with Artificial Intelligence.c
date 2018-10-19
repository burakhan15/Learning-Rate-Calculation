#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct dataStructure {
	double w0;
	double w1;
	double mu;
	double errorRate;
	double threshold;
} data;

struct xValuesStructure {
	double x0;
	double x1;
};

struct dataStructure calculateWs(struct dataStructure data, struct xValuesStructure xValues, int dt) {
	double yt = (data.w0*xValues.x0)+(data.w1*xValues.x1)-data.threshold;
	int ytValue;
	int error = 0;
	if(yt > 0) {
		ytValue = 1;
		error = dt-ytValue;
		if(error == 0) {
			printf("No weight and no update\n");
		} else {
			data.w0 = data.w0+(data.mu*(dt-ytValue)*xValues.x0);
			data.w1 = data.w1+(data.mu*(dt-ytValue)*xValues.x1);
		}
	} else {
		ytValue = -1;
		error = dt-ytValue;
		data.w0 = data.w0+(data.mu*(dt-ytValue)*xValues.x0);
		data.w1 = data.w1+(data.mu*(dt-ytValue)*xValues.x1);
	}

	if(error != 0) {
		data.errorRate += 25;
	}

	printf("y(t): %.2f\n", yt);
	printf("d(t): %d\n", dt);
	printf("error: %d\n", error);
	printf("w0: %.2f\n", data.w0);
	printf("w1: %.2f\n\n", data.w1);

	return data;
}

struct xValuesStructure getX0X1(int i) {
	int x0 = -1;
	if(i==2 || i==3) {
		x0 = 1;
	}
	int x1 = -1;
	if(i==1 || i==3) {
		x1 = 1;
	}
	struct xValuesStructure xValues;
	xValues.x0 = x0;
	xValues.x1 = x1;

	return xValues;
}
void calculateAndYt(struct dataStructure data) {
	int i;
	for(i=0; i<4;i++) {
		struct xValuesStructure xValues;
		xValues = getX0X1(i);
		int dt = -1;
		if(i == 3) {
			dt = 1;
		}

		printf("AND Gate Run No %d\n", i);
		data = calculateWs(data, xValues, dt+1);
	}
	printf("Error Rate %.2f%%\n", data.errorRate);
}
void calculateOrYt(struct dataStructure data) {
	int i;
	for(i=0; i<4;i++) {
		struct xValuesStructure xValues;
		xValues = getX0X1(i);
		int dt = 1;
		if(i == 0) {
			dt = -1;
		}

		printf("OR Gate Run No %d\n", i+1);
		data = calculateWs(data, xValues, dt);
	}
	printf("Error Rate %.2f%%\n", data.errorRate);
}
void calculateXorYt(struct dataStructure data) {
	int i;
	for(i=0; i<4;i++) {
		struct xValuesStructure xValues;
		xValues = getX0X1(i);
		int dt = 1;
		if(i == 0 || i == 3) {
			dt = -1;
		}

		printf("XOR Gate Run No %d\n", i+1);
		data = calculateWs(data, xValues, dt);
	}
	printf("Error Rate %.2f%%\n", data.errorRate);
}

int main(void) {
	data.threshold = 1;

	data.w0 = 0.1;
	data.w1 = 0.4;
	data.mu = 0.5;
	data.errorRate = 0.0;
	calculateAndYt(data);
	printf("-- Finish -- \n\n");

	data.w0 = 0.1;
	data.w1 = 0.4;
	data.mu = 0.5;
	data.errorRate = 0.0;
	calculateOrYt(data);
	printf("-- Finish -- \n\n");

	data.w0 = 0.1;
	data.w1 = 0.4;
	data.mu = 0.5;
	data.errorRate = 0.0;
	calculateXorYt(data);
	printf("-- Finish --");
}
