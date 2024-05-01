#include <stdio.h>
#include "MLP.h"
CMLP	MultiLayer;

#define MAX_EPOCH 100000

int main()
{
	int HiddenNode[2] = { 3,2 };
	MultiLayer.Create(2, HiddenNode, 1, 2);
	int input[4][2] = { {0,0},{0,1},{1,0},{1,1} };
	int danswer[4] = { 0,1,1,0 };
	int n;
	int epoch;

	// �Է°� ������ ��°� ���
	for (n = 0; n < 4; n++)
	{
		MultiLayer.pInValue[1] = input[n][0];
		MultiLayer.pInValue[2] = input[n][1];
		MultiLayer.Forward();
		printf("%lf %lf = %lf\n", MultiLayer.pInValue[1], MultiLayer.pInValue[2], MultiLayer.pOutValue[1]);
	}
	printf("\n");
	getchar();
	double MSE;
	printf("******** �н����� ***********\n");
	for (epoch = 0; epoch < MAX_EPOCH; epoch++)
	{
		MSE = 0.0;
		for (n = 0; n < 4; n++)
		{
			MultiLayer.pInValue[1] = input[n][0]; //�Է�����
			MultiLayer.pInValue[2] = input[n][1]; //�Է�����
			MultiLayer.pCorrectOutValue[1] = danswer[n]; //��������

			MultiLayer.Forward();	//��°��
			MultiLayer.BackPopagationLearning();	//�н�-����ġ����

			//�����Ŀ� �������� ���
			MultiLayer.Forward();	//���������� ��� ���
			MSE += (MultiLayer.pCorrectOutValue[1] - MultiLayer.pOutValue[1])*
				(MultiLayer.pCorrectOutValue[1] - MultiLayer.pOutValue[1]);
		}
		MSE /= 4; //��հ� ���
		printf("Epoch%d(MSE) = %lf\n", epoch, MSE);
		if (MSE < 0.0001)
			break;
	}
	printf("********* �н� ���� ***********\n");

	//�Է°� ������ ��°� ���
	for (n = 0; n < 4; n++)
	{
		MultiLayer.pInValue[1] = input[n][0];
		MultiLayer.pInValue[2] = input[n][1];
		MultiLayer.Forward();
		printf("%lf %lf = %lf\n", MultiLayer.pInValue[1], MultiLayer.pInValue[2], MultiLayer.pOutValue[1]);
	}
	printf("\n");
	
}