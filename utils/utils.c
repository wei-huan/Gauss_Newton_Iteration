#include "utils.h"

// 打印变量名
void print_var_name(const char* x_name){
	printf("%s:\n", x_name);
}

// 取绝对值
double abstract(double number){
	if(number < 0)
		number = number * -1;
	
	return number;
}

// 四舍五入
int round_up_round_down(double num){
	if(num > 0)
		return (int)(num + 0.5);
	else if (num == 0.0)
		return (int)num;
	else 
		return (int)(num - 0.5);
}	

// 快速取以2为底的对数
int fast_log2(int num){
	return 0;
}

// 弧度转角度
float radiant2degree(float radiant){
	float degree = 0;
	
	degree = radiant / pi * 180;
	return degree;
}

// 角度转弧度
float degree2radiant(float degree){
	float radiant = 0;
	
	radiant = degree / 180 * pi;
	return radiant;
}
