#include <stdio.h>
#include <stdlib.h>     
#include "math.h"
#include "time.h"
/*
double scalar(matrix a, matrix b){
    if(a.collumns != 1 || b.collumns != 1){
        printf("Error while calculing the scalar");
        return 0;
    }
    matrix c = transpose(a);
    matrix d = matrix_product(c,b);
    double final = get_value_matrix(d,0,0);
    free_matrix(d);
    free_matrix(c);
    return final;

}
double derivate_loss(double a,double y){
    return -y/a + (1-y)/(1-a);
}
double derivate_z(double a,double y){
    return a - y;
}
double derivate_w(matrix m,double a,double y, int i){
    double dz = derivate_z(a,y);
    double b = get_value_matrix(m,0,i);
    return b*dz;
}

matrix matrix_product(matrix a, matrix b){
    matrix final = init_matrix(b.collumns, a.rows);
    if(b.rows != a.collumns){
        printf("can't multiply thoses matrix");
        return final;
    }
    int temp1;
    int temp2;
    int temp3;
    for(int i = 0; i< b.collumns;i++){
        for(int j = 0; j<a.rows; j++){
            for(int k =0; k<b.rows;k++){
                temp1 = get_value_matrix(final,j,i);
                temp2 = get_value_matrix(a,k,i);
                temp3 = get_value_matrix(b,j,k);
                printf("%d %d %d %d %d\n", i,j,temp2,temp3,temp1);
                set_value_matrix(final,j,i, temp1 + temp2 * temp3);
            }
        }
    }
    printf("\n");
    return final;
}*/
struct tab
{
    double* elements;
    int length;
};typedef struct tab tab;

struct matrix
{
    double* elmt;
    int rows;
    int collumns;
};typedef struct matrix matrix;


tab init_tab(int len){
    double* elm = malloc(len*sizeof(double));
    tab t = {elm,len};
    return t;
}
void free_tab(tab t){
    free(t.elements);
}
double get_value_matrix(matrix m,int collumn, int row){
    if(row >= m.rows || collumn >= m.collumns){
        printf("index out of bounds\n");
        return -1;
    }

    return (m.elmt)[collumn*m.rows + row];
}
void set_value_matrix(matrix m, int collumn, int row, double value){
    if(row >= m.rows || collumn >= m.collumns){
        printf("index out of bounds\n");
    }
    else{
    (m.elmt)[collumn*m.rows + row] = value;}
}
double get_value_tab(tab t, int n){
    if(n >= t.length){
        printf("index out of bounds");
        return -1;
    }
    return (t.elements)[n];
}
matrix init_matrix(int collumns, int rows){
    double* t = malloc(rows * collumns * sizeof(double));
    for(int i =0; i<collumns*rows;i++){
        t[i] = 0;
    }
    return (matrix){t,rows,collumns};
}

tab collumn_from_matrix(matrix m, int collumn){
    return (tab){m.elmt + m.rows*collumn, m.rows};
}

void free_matrix(matrix m){
    free(m.elmt);
}
matrix collum_to_matrix(tab a){
    return (matrix){a.elements,a.length,1};
}
matrix transpose(matrix m){
    matrix transposed = init_matrix(m.rows, m.collumns);
    for(int i = 0; i<m.rows; i++){
        for(int j = 0; j<m.collumns;j++){
            set_value_matrix(transposed,i,j,(get_value_matrix(m,j,i)));
        }
    }
    return transposed;
}
matrix create_x(){
    matrix x = init_matrix(500,10);
    FILE *fp = fopen("breast-cancer-wisconsin.txt","r");
    int buff[11];
    for(int i = 0; i<500; i++){
        fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &buff[0],&buff[1],&buff[2],&buff[3],&buff[4],&buff[5],&buff[6],&buff[7],&buff[8],&buff[9],&buff[10]);
        for(int j = 0; j <10;j++){
            set_value_matrix(x,i,j,(double)buff[j+1]);
        }
    }
    fclose(fp);
    return x;
    }
tab create_y(){
    tab y = init_tab(500);
    FILE *fp = fopen("breast-cancer-wisconsin.txt","r");
    int buff[11];
    for(int i = 0; i<500; i++){
        fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &buff[0],&buff[1],&buff[2],&buff[3],&buff[4],&buff[5],&buff[6],&buff[7],&buff[8],&buff[9],&buff[10]);
        y.elements[i] = (buff[10]/4);
    }
    fclose(fp);
    return y;
    }
double tab_dot(tab a, tab b){
    if(a.length != b.length){
        printf("%d %d   ", a.length, b.length);
        return 0;
    }
    double c = 0;
    for(int i = 0; i<a.length;i++){
        c += a.elements[i]*b.elements[i];
    }
    return c;
}
tab matrix_tab_dot(matrix a, tab b){
    tab f = init_tab(a.rows);
    for(int i = 0; i < a.collumns;i++){
        for(int j = 0; j< a.rows; j++){
            f.elements[j] += get_value_matrix(a, i,j)*get_value_tab(b, i);
        }
    }   
    return f;
}
void print_linear(matrix m){
    for(int i = 0; i < m.collumns + m.rows ; i++){
        printf("%d ", m.elmt[i]);
    }
}
void tab_plus(tab a, double x){
    for(int i = 0; i<a.length;i++){
        a.elements[i] += x;
    }
}
void tab_minus(tab a, double x){
    for(int i = 0; i<a.length;i++){
        a.elements[i] -= x;
    }
}
void tab_multipy(tab a, double x ){
    for(int i = 0; i<a.length;i++){
        a.elements[i] *= x;
    }
}
void tab_divide(tab a, double x ){
    for(int i = 0; i<a.length;i++){
        a.elements[i] /= x;
    }
}
void tab_minus_tab(tab a, tab b, tab final){
    if(a.length != b.length){
        printf("erreur");
        return;
    }
    for(int i = 0; i<a.length;i++){
        final.elements[i] = a.elements[i] - b.elements[i];
    }
}
double tab_sum(tab a){
    double c = 0;
    for(int i = 0;i < a.length;i++){
        c+= a.elements[i];
    }
    return c;
}
tab init_and_get_z(matrix x, tab w, double b){
    tab z = init_tab(x.collumns);
    tab temp;
    for(int i = 0; i <x.collumns; i++){
        temp = collumn_from_matrix(x, i);
        z.elements[i] = tab_dot(w,temp) + b;
    }
    return z;
}

void print_matrix(matrix m){
    for(int i =0; i<m.rows;i++){
        for(int j = 0; j<m.collumns; j++){
            printf("%f ", get_value_matrix(m, j,i));
        }
        printf("\n");
    }
    printf("\n");
}
double sigmoid(double x){
    return (1/(1+exp((double)x * -1) ));
}
double loss(double yHat, double y){
    return -(y*log((double) yHat) + (1-y)*log(1-yHat));
}

void tab_sigmoid(tab x){
    for(int i = 0; i<x.length ;i++){
        (x.elements)[i] = sigmoid(x.elements[i]);
    }
}

void print_tab(tab x){
    for(int i = 0; i < x.length; i++){
        printf("%f\n", x.elements[i]);
    }
}
double cost(matrix x, tab w,tab y, double b){
    tab z = init_and_get_z(x,w,b);
    tab_sigmoid(z);
    double counter = 0;
    for(int i =0;i<z.length;i++){
        counter += loss(z.elements[i], y.elements[i]);
    }
    return counter/x.collumns;
}
double logistic_regression(tab w, double b, matrix x, tab y, double alpha){
    tab dz = init_tab(x.collumns);
    tab z = init_and_get_z(x,w,b);
    tab_sigmoid(z);
    tab_minus_tab(z,y,dz);
    tab dw = matrix_tab_dot(x,dz);  
    tab_divide(dw, x.collumns);
    double db = 1/x.collumns * tab_sum(dz);
    tab_multipy(dw, alpha);
    tab_minus_tab(w, dw, w);
    free_tab(dz);
    free_tab(z);
    free_tab(dw);
    return b - alpha*db;
}
int main(void){
    matrix x = create_x();
    tab y = create_y();
    tab w = init_tab(x.rows);
    for(int i = 0; i <x.rows; i++) w.elements[i] = 1;
    double b = 0;
    for(int i = 0; i<100000; i++){
        b = logistic_regression(w,b,x,y,0.001);
        printf("cost : %lf\n", cost(x,w,y,b));
    }
    printf("cost : %lf", cost(x,w,y,b));

}